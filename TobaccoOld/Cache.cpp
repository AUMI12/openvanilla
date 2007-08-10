#include <algorithm> // for "std::find() used on deque"
#include "Cache.h"

using namespace std;

const size_t Cache::MAX_CACHE_SIZE = 1000;
Cache* Cache::m_instance = 0;

/*
struct DeleteObject {
	template<typename T>
	void operator()(const T* ptr) const
	{
		delete ptr;
	}
};
*/

Cache::Cache()
{
	Cache::m_currentCacheSize = 0;
}

Cache::~Cache()
{
	//Cache::clearTable();
	Cache::m_table.clear();
	Cache::m_recentlyUsedList.clear();
	Cache::m_currentCacheSize = 0;
}

Cache* Cache::getInstance()
{
	if(Cache::m_instance == 0)
	{
		m_instance = new Cache();
	}

	return m_instance;
}

void Cache::releaseInstance()
{
	if(Cache::m_instance != 0)
		Cache::~Cache();
}

/*
void Cache::clearTable()
{
	for(map<wstring, vector<Profile*> >::iterator iter=Cache::table.begin();
		iter != Cache::table.end();
		++iter)
			for_each(iter->second.begin(), iter->second.end(), DeleteObject);

	Cache::m_table.clear();
}
*/

void Cache::rank(const Profile& profile)
{
	string targetID = profile->GetID();
	if(Cache::m_table.count(targetID) > 0) {
		vector<Profile> profileVector = Cache::m_table[targetID];
		for(size_t i = 0; i < profileVector.size(); ++i)
		{
			Profile existedProfile = profileVector[i];
			int currentHitRate = existedProfile->GetHitRate();
			if(existedProfile->GetWord() == profile->GetWord())
				Cache::m_table[targetID][i]->SetHitRate(++currentHitRate);
			else if(currentHitRate > 0)
				Cache::m_table[targetID][i]->SetHitRate(--currentHitRate);
		}
	}
}

void Cache::add(const Profile& profile)
{
	string id = profile->GetID();
	if (Cache::m_table.count(id) == 0)
	{
		//�̷ӥq�k�|���n�D��������MAX_CACHE_SIZE���P�_
		Cache::m_recentlyUsedList.push_back(id);
//		/*
//		cache �٦��Ŷ����ܴN�����\��̫᭱�C
//		�o�̥u�O����ƧǥΪ� deque �@�O���C
//		*/
//		if (currentCacheSize < MAX_CACHE_SIZE || Cache::recentlyUsedList.size() == 0)
//		{
//			// 20060318
//			// Cache::recentlyUsedList.size() == 0 �|�o�ͦb�ϥΪ̤��e�s�ɪ��O�����w�W�L MAX_CACHE_SIZE ��
//
//			Cache::recentlyUsedList.push_back(id);
//		}
//		/*
//		�p�G cache �z�F�A�N�� cache �̳̫�@�Ӥ����������C
//		����ƧǥΪ� deque �h�d�̫�@�W�� ID �X�ӡA�A���� cache �̪������C
//		*/
//		else
//		{
//			wstring leastRecentlyUsedID = Cache::recentlyUsedList.back();
//			wstring nullString(L"");
//			remove(leastRecentlyUsedID, nullString);
//		}

		/*
		�o�̤~�O�u����F���i cache �̡C
		*/
		vector<Profile> currentVector;
		currentVector.push_back(profile);

		Cache::m_table.insert(make_pair(id, currentVector));
	}
	else
	{
		bool foundWord = false;
		vector<Profile> profileVector = Cache::m_table[id];
		for(size_t i = 0; i < profileVector.size(); ++i)
		{
			Profile existedProfile = profileVector[i];
			int currentHitRate = existedProfile->GetHitRate();
			if(existedProfile->GetWord() == profile->GetWord())
			{
				Cache::m_table[id][i]->SetHitRate(++currentHitRate);
				foundWord = true;
				break;
			}
			else if(currentHitRate > 0)
				Cache::m_table[id][i]->SetHitRate(--currentHitRate);
		}

		if(!foundWord)
			Cache::m_table[id].push_back(profile);
	}

	currentCacheSize++;
}

Profile* Cache::fetch(string id)
{
	vector<Profile> profileVector = Cache::fetchAll(id);
	bool hasCustomizedTerm = false;
	bool doUpdate = false;

	if(profileVector.size() != 0)
	{
		///*
		int maxHitRate = 0;
		int bestIndex = profileVector.size() - 1;
		for(size_t i = 0; i < profileVector.size(); i++)
		{
			if(profileVector[i]->GetCustomizeFlag()) {
				if(!hasCustomizedTerm) {
					hasCustomizedTerm = true;
					doUpdate = true;
				} else if (profileVector[i]->GetHitRate() >= maxHitRate) {
					doUpdate = true;
				}
			}

			if(!hasCustomizedTerm && profileVector[i]->GetHitRate() >= maxHitRate)
				doUpdate = true;

			if(doUpdate) {
				maxHitRate = profileVector[i]->GetHitRate();
				bestIndex = i;
				doUpdate = false;
			}
		}

		return &profileVector[bestIndex];
		//*/
		// ��^�u��i���X�v�Ҧ�
		//return profileVector.back();
	}
	else
		return 0;
}

vector<Profile>* Cache::fetchAll(string id)
{
	vector<Profile> currentVector;
	int counter = Cache::count(id);
	if (counter == 0)
		currentVector.clear();
	else
	{
		std::deque<string>::iterator current;
		current = find(Cache::m_recentlyUsedList.begin(), Cache::m_recentlyUsedList.end(), id);
		currentVector = Cache::table[id];
	}

	return &currentVector;
}

size_t Cache::count(string id)
{
	return Cache::m_table.count(id);
}

bool Cache::remove(string id, string word)
{
/*
���� cache �̪��F��n�����H�U�T�ӨB�J�G
�����b�Ƨǥ� deque �̹����� ID�F
���� cache �̪������F
�N�ثe cache �ϥα����Ŷ��� 1�C
*/
	deque<string>::iterator current;
	current = find(Cache::m_recentlyUsedList.begin(), Cache::m_recentlyUsedList.end(), id);
	Cache::m_recentlyUsedList.erase(current);

	int counter = Cache::m_table.count(id);

	bool doEraseFlag = false;
	if(counter > 0)
	{
		for(size_t i = 0; i < Cache::m_table[id].size(); ++i)
		{
			if(Cache::m_table[id][i]->GetWord() == word)
			{
				Cache::m_table[id].erase(Cache::m_table[id].begin() + i);
				currentCacheSize--;
				doEraseFlag = true;
				break;
			}
		}

		if(Cache::m_table[id].size() == 0)
			Cache::m_table.erase(Cache::m_table.find(id));
	}

	return doEraseFlag;
}

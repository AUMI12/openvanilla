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
	m_currentCacheSize = 0;
}

Cache::~Cache()
{
	//clearTable();
	m_table.clear();
	m_recentlyUsedList.clear();
	m_currentCacheSize = 0;
}

Cache* Cache::getInstance()
{
	if(!m_instance)
	{
		m_instance = new Cache();
	}

	return m_instance;
}

void Cache::releaseInstance()
{
	if(m_instance)
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

void Cache::rank(const string& id, const string& word)
{
	if(m_table.count(id) > 0) {
		vector<Profile> profileVector = m_table[id];
		for(size_t i = 0; i < profileVector.size(); ++i)
		{
			Profile existedProfile = profileVector[i];
			size_t currentHitRate = existedProfile.hitRate;
			//@author b6s
			//@todo Refactoring is needed.
			/*
			if(existedProfile.word() == word)
				m_table[id][i].hitRate = ++currentHitRate;
			else if(currentHitRate > 0)
				m_table[id][i].hitRate = --currentHitRate;
			*/
		}
	}
}

void Cache::add(Profile& profile)
{
	string id = profile.id();
	if (m_table.count(id) == 0)
	{
		//������ MAX_CACHE_SIZE ���P�_
		m_recentlyUsedList.push_back(id);
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

		m_table.insert(make_pair(id, currentVector));
	}
	else
	{
		bool foundWord = false;
		vector<Profile> profileVector = m_table[id];
		for(size_t i = 0; i < profileVector.size(); ++i)
		{
			Profile existedProfile = profileVector[i];
			size_t currentHitRate = existedProfile.hitRate;
			//@author b6s
			//@todo Refactoring is needed.
			/*
			if(existedProfile.word() == profile.word())
			{
				m_table[id][i].setHitRate(++currentHitRate);
				foundWord = true;
				break;
			}
			else if(currentHitRate > 0)
				m_table[id][i].setHitRate(--currentHitRate);
			*/
		}

		if(!foundWord)
			m_table[id].push_back(profile);
	}

	m_currentCacheSize++;
}

Profile* Cache::fetch(const string& id)
{
	vector<Profile> profiles;
	size_t amount = fetchAll(id, profiles);
	bool hasCustomTerm = false;
	bool doUpdate = false;
	Profile* profile = 0;
	if(amount > 0)
	{
		///*
		size_t maxHitRate = 0;
		for(size_t i = 0; i < profiles.size(); ++i)
		{
			if(profiles[i].isCustom) {
				if(!hasCustomTerm) {
					hasCustomTerm = true;
					doUpdate = true;
				} else if (profiles[i].hitRate >= maxHitRate) {
					doUpdate = true;
				}
			}

			if(!hasCustomTerm && profiles[i].hitRate >= maxHitRate)
				doUpdate = true;

			if(doUpdate) {
				maxHitRate = profiles[i].hitRate;
				profile = &profile[i];
				doUpdate = false;
			}
		}

		//*/
		// ��^�u��i���X�v�Ҧ�
		//return profileVector.back();
	}

	return profile;
}

size_t Cache::fetchAll(const string& id, vector<Profile>& profiles)
{
	size_t amount = count(id);
	if (amount > 0)
		profiles = m_table[id];

	return amount;
}

size_t Cache::count(const string& id)
{
	return m_table.count(id);
}

bool Cache::remove(const string& id, const string& word)
{
/*
���� cache �̪��F��n�����H�U�T�ӨB�J�G
�����b�Ƨǥ� deque �̹����� ID�F
���� cache �̪������F
�N�ثe cache �ϥα����Ŷ��� 1�C
*/
	deque<string>::iterator current;
	current =
		find(m_recentlyUsedList.begin(), m_recentlyUsedList.end(), id);
	m_recentlyUsedList.erase(current);

	size_t counter = m_table.count(id);

	bool doEraseFlag = false;
	if(counter > 0)
	{
		for(size_t i = 0; i < m_table[id].size(); ++i)
		{
			//@author b6s
			//@todo Refactoring is needed.
			/*
			if(m_table[id][i].word() == word)
			{
				m_table[id].erase(m_table[id].begin() + i);
				m_currentCacheSize--;
				doEraseFlag = true;
				break;
			}
			*/
		}

		if(m_table[id].size() == 0)
			m_table.erase(m_table.find(id));
	}

	return doEraseFlag;
}

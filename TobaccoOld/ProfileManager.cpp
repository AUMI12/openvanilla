#include "ProfileManager.h"

#include "DictionarySingleton.h"

ProfileManager* ProfileManager::_instance = 0;
Profile* ProfileManager::profileWaitingForHit = 0;

ProfileManager::ProfileManager()
{
	cache = Cache::getInstance();
//	LoadCacheFile();  // comment out by Aileen to synchronize with utility program
}

ProfileManager::~ProfileManager()
{
//	SaveCacheFile();  // // comment out by Aileen to synchronize with utility program
	cache->lostInstance();
}

ProfileManager* ProfileManager::getInstance()
{
	if(ProfileManager::_instance == 0)
	{
		_instance = new ProfileManager();
	}

	return _instance;
}

void ProfileManager::lostInstance()
{
	if(ProfileManager::_instance != 0)
		ProfileManager::~ProfileManager();
}

void ProfileManager::clearSession()
{
	ProfileManager::session.clear();
}

Profile* ProfileManager::query(std::wstring id)
{
	Profile* profile = 0;
	profile = cache->fetch(id);		// �� cache �̬ݬݦ��S���ŦX������C
	/*
	if (profile == 0)					// �p�G�S���A�N�s��ݥh��ݭn�������X�ӡC
	{									// ���J�k�ӻ��A��ݰʧ@�]�i�H�����O���X�ǲߨ쪺�r��C
		//profile = server.fetch(id);		// ��@�� cache �t�Ψӻ��A��ݤ��O�Ҧ��������G�A
		//if (profile != 0)				// �����J�k�̪��ǲߨӻ��@�w���A�ҥH�o�̪� if �`�O true�C
		//	cache.add(profile);			// ��e�� server->fetch(id) �̳B�z�n�������i cache�C
		// simulate add Profile for test only ; if not test,mark it
		//else
		//{
		//	vector<Token> tokenVec;
		//  Token token[2];//�t��-�t����	�ݤ�	3
		//  token[0].characterStringVector.push_back ( L"�t��");
		//  token[0].characterStringVector.push_back ( L"�t����");
		//  token[1].word = L"��";
		//  token[1].word = L"��"; 
		//	tokenVec.push_back(token[0]);
		//	tokenVec.push_back(token[1]);
		//	profile = new Profile(id,0,tokenVec);
		//	cache.add(profile);
		}//end of test
	}
	*/

	return profile;
}

Profile* ProfileManager::fetch(std::wstring id, int currentPos)
{
	Profile* profile = query(id);

	if(profile != 0) {
		wstring currentWord = profile->GetWord();
		int count = session.count(currentWord);
		bool doRank = true;
		if(count > 0) {
			multimap<wstring, int>::iterator iter = session.find(currentWord);
			for(int i = 0; i < count; ++i, ++iter)
			{
				if(iter->second == currentPos) {
					doRank = false;
					break;
				}
			}
		}

		if(doRank) {
			session.insert(make_pair(currentWord, currentPos));
			cache->rank(profile);
		}
	}

	return profile;
}

void ProfileManager::LoadCacheFile()
{
	LoadCacheFile(false);
}

void ProfileManager::LoadCacheFile(bool doSync)
{
	DictionarySingleton* dictionary = DictionarySingleton::getInstance();
	wstring cacheFilePath =dictionary->productInstalledPath + L"\\cache.txt";
	cache->LoadFromFile(cacheFilePath, doSync);
}

void ProfileManager::SaveCacheFile()
{
	DictionarySingleton* dictionary = DictionarySingleton::getInstance();
	wstring cacheFilePath =dictionary->productInstalledPath + L"\\cache.txt";
	cache->SaveToFile(cacheFilePath);
}
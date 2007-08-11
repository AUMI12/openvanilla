#include "ProfileManager.h"

#include "DictionarySingleton.h"

ProfileManager* ProfileManager::m_instance = 0;

ProfileManager::ProfileManager()
{
	m_cache = Cache::getInstance();
}

ProfileManager::~ProfileManager()
{
	m_cache->releaseInstance();
}

ProfileManager* ProfileManager::getInstance()
{
	if(ProfileManager::m_instance == 0)
	{
		m_instance = new ProfileManager();
	}

	return m_instance;
}

void ProfileManager::releaseInstance()
{
	if(ProfileManager::m_instance != 0)
		ProfileManager::~ProfileManager();
}

Profile* ProfileManager::query(const string& id)
{
	Profile* profile = 0;
	profile = m_cache->fetch(id);		// �� cache �̬ݬݦ��S���ŦX������C
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

Profile* ProfileManager::fetch(const string& id, size_t position)
{
	Profile* profile = query(id);

	if(profile != 0) {
		//@author b6s
		//@todo Refactoring is needed.
		//string word = profile->word();
		string word("");
		size_t count = m_session.count(word);
		bool doRank = true;
		if(count > 0) {
			multimap<string, size_t>::iterator iter = m_session.find(word);
			for(size_t i = 0; i < count; ++i, ++iter)
			{
				if(iter->second == position) {
					doRank = false;
					break;
				}
			}
		}

		if(doRank) {
			m_session.insert(make_pair(word, position));
			m_cache->rank(id, word);
		}
	}

	return profile;
}

void ProfileManager::writeBack()
{
	//@todo writes cache back to SQLite db here.
}

void ProfileManager::clearSession()
{
	ProfileManager::m_session.clear();
}

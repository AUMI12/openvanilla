#ifndef PROFILEMANAGER_H
#define PROFILEMANAGER_H

#include "Cache.h"
#include "ProfileFetcher.h"
#include "Token.h"

#include <map>

using namespace std;

class ProfileManager {
	public:
		static ProfileManager* getInstance();
		void releaseInstance();
  
		Profile* query(const string& id);
		Profile* fetch(const string& id, size_t position);
		void writeBack();
		
		void clearSession();
		
		ProfileManager();
		~ProfileManager();

	private:
		static ProfileManager* m_instance;

		Cache* m_cache;
		ProfileFetcher m_server;
		/*
		�H�W��� new class object ���ʧ@���ӭn�M singleton pattern �~�n�A
		�Ȯɥ����h�復�̡C
		*/
		
		multimap<string, size_t> m_session;
};

#endif
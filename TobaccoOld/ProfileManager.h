#ifndef PROFILEMANAGER_H
#define PROFILEMANAGER_H

#include "Cache.h"
#include "ProfileFetcher.h"
#include "token.h"

#include <map>

using namespace std;

class ProfileManager {
	public:
		static ProfileManager* getInstance();
		void lostInstance();
  
		Profile* query(std::wstring id);
		Profile* fetch(std::wstring id, int pos);
		void LoadCacheFile();
		void LoadCacheFile(bool doSync);
		void SaveCacheFile();
		
		void clearSession();

		ProfileManager();
		~ProfileManager();
	private:
		static ProfileManager* _instance;
		static Profile* profileWaitingForHit;

		Cache* cache;
		ProfileFetcher server;
		/*
		�H�W��� new class object ���ʧ@���ӭn�M singleton pattern �~�n�A
		�Ȯɥ����h�復�̡C
		*/

		multimap<wstring, int> session;
};

#endif
#pragma once
#include "stdafx.h"
class LogServer {
	wofstream *out;
public:
	queue<wchar_t*>* _Queue;
	HANDLE hThreadRead;
	HANDLE hThreadWriteToFile;
	LogServer();
	void ForceReStartThreadRead();
	void WriteToFile(wchar_t*, bool);
	bool bRunning;
	~LogServer();
};

class LogClient {
public:
	LogClient();
	queue<wchar_t*> * _Queue;
	~LogClient();
	bool bRunnng;
	HANDLE hThreadWrite;
	int Write(wchar_t*);
};
class LocalServer {
	LocalServer();
	bool Init();
	~LocalServer();
};

string  _stdcall  StartSvc(TCHAR*);
string  __stdcall StopSvc(TCHAR *szSvcName);
BOOL __stdcall StopDependentServices(SC_HANDLE schService, SC_HANDLE schSCManager);

string  WINAPI InstallSvc(TCHAR * szSvcName);
string __stdcall DeleteSvc(TCHAR* szSvcName);
bool SignPoint(char * BDUSS);
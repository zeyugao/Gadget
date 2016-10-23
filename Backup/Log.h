#pragma once
#include "stdafx.h"
#ifdef CRYSTALCORE_EXPORTS
#define CRYSTALCORE_API __declspec(dllexport)
#else
#define CRYSTALCORE_API __declspec(dllimport)
#endif
UINT WINAPI ThreadRead(PVOID);
UINT WINAPI ThreadWrite(LPVOID);
UINT WINAPI ThreadWriteToFile(PVOID);
class CRYSTALCORE_API LogServer {
	 wofstream *out;
public:
	queue<wchar_t*> _Queue;
	HANDLE hThreadRead;
	HANDLE hThreadWriteToFile;
	LogServer();
	void ForceReStartThreadRead();
	void WriteToFile(wchar_t*,bool);
	bool bRunning;
	~LogServer();
};

class CRYSTALCORE_API LogClient {
public:
	LogClient();
	queue<wchar_t*>  _Queue;
	~LogClient();
	bool bRunnng;
	HANDLE hThreadWrite;
	int Write(wchar_t*);
};
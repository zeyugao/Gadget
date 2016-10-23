#pragma once
struct _err {
	int err;
	int step;
};
UINT CALLBACK MainThread(PVOID);
UINT CALLBACK WriteThread(PVOID);
class LogServer
{
	wofstream *out;
	HANDLE hMainThread;
	HANDLE hWriteThread;
public:
	queue<wchar_t*>* _Queue;
	LogServer();
	void Log(wchar_t*);
	bool bRun;
	~LogServer();
	_err err;
};


#pragma once
struct _err {
	int err;
	int step;
};
UINT CALLBACK MainThread(PVOID);
class LogClient
{
public:
	LogClient();
	queue<wstring>*_Queue;
	HANDLE hMainThread;
	~LogClient();
	bool bRun;
	_err err;
	int push(wstring);
};


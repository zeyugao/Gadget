#pragma once
UINT WINAPI ThreadRead(PVOID);
UINT WINAPI ThreadWrite(LPVOID);
UINT WINAPI ThreadWriteToFile(PVOID);
class LogServer {
	wofstream out;
public:
	queue<wchar_t*> _Queue;
	HANDLE hThreadRead;
	HANDLE hThreadWriteToFile;
	LogServer();
	void ForceReStartThreadRead();
	void WriteToFile(wchar_t*);
	bool bRunning;
	~LogServer();
};

class LogClient {
public:
	LogClient();
	queue<wchar_t*> _Queue;
	~LogClient();
	bool bRunnng;
	HANDLE hThreadWrite;
	int Write(wchar_t*);
};
#pragma once
#ifdef CRYSTALCORE_EXPORTS
#define CRYSTALCORE_API __declspec(dllexport)
#else
#define CRYSTALCORE_API __declspec(dllimport)
#endif
/***********************************/
//					LogServer
//Purpose:接收LogClient发来的Log，并写入文件
//Version:		0.7 Beta
//The way:	Pipe for windows&queue
//		(C)Copyright @FrozenMac
/***********************************/
//struct _err {
//	int err;
//	int step;
//};
UINT CALLBACK LogServerMainThread(PVOID);
UINT CALLBACK WriteThread(PVOID);
class CRYSTALCORE_API LogServer
{
	wofstream *out;
	HANDLE hMainThread;
	HANDLE hWriteThread;
public:
	queue<wstring>* _Queue;
	LogServer();

	//写入文件
	void Log(const wchar_t*);

	//写入文件&添加时间
	//应该在LogServer 所在程序使用
	void LogWithTime(const wchar_t*);
	bool bRun;
	
	//清理资源
	~LogServer();
	//_err err;
};


#include "stdafx.h"
#include "Log.h"

//Version 0.6.4 Beta
//Bug : 如果客户端输入过快，可能会导致服务器失去反应，要重新启动
//Warning : 错误提示大多数使用了throw，如果没有使用 try { ... } catch(char*) { ... }，会导致程序中断

LogServer::LogServer()
{
	out = new wofstream;
	//_Queue = new queue<wchar_t*>;
	out->open("Log.txt", ios_base::out | ios_base::app);
	bRunning = true;
	hThreadRead = (HANDLE)_beginthreadex(nullptr, 0, ThreadRead, this, 0, nullptr);
	hThreadWriteToFile = (HANDLE)_beginthreadex(nullptr, 0, ThreadWriteToFile, this, 0, nullptr);
	WriteToFile(L"LogServer Start", true);
}

void LogServer::ForceReStartThreadRead()
{

}

void LogServer::WriteToFile(wchar_t *Msg,bool b = false)
{
	if (b) {
		SYSTEMTIME sys;
		GetLocalTime(&sys);
		wchar_t tmp[100];
		wsprintf(tmp, L"%d/%d/%d %d:%d:%d", sys.wMonth, sys.wDay, sys.wYear, sys.wHour, sys.wMinute, sys.wSecond);
		*out << tmp << endl;
	}
	*out << Msg << endl << endl;
}
UINT WINAPI ThreadWriteToFile(PVOID lParam) {
	LogServer*sv = (LogServer*)lParam;
	while (sv->bRunning||(!(sv->_Queue.empty()))) {
		while ((sv->_Queue.empty())) {
			Sleep(100);
		}
		Sleep(150);
		sv->WriteToFile(sv->_Queue.front());
		sv->_Queue.pop();
	}
	return 0;
}
UINT WINAPI ThreadRead(PVOID lParam)
{
	LogServer * sv = (LogServer*)lParam;
	while (sv->bRunning||(sv->_Queue.empty())) {
		HANDLE hPipe = CreateNamedPipe(L"\\\\.\\Pipe\\FrozenPipe", PIPE_ACCESS_DUPLEX,
			PIPE_TYPE_BYTE | PIPE_READMODE_BYTE, 1, 0, 0, 1000, NULL); // 创建命名管道
		if (hPipe == INVALID_HANDLE_VALUE) {
			throw "Can not CreateNamedPipe";
		}
		if (ConnectNamedPipe(hPipe, nullptr) == FALSE) // 等待客户机的连接
		{
			CloseHandle(hPipe); 
			throw "Can not ConnectNamedPipe";
		}
		wchar_t buffer[1024] = { 0 };
		DWORD ReadNum;
		if (ReadFile(hPipe, buffer, sizeof(buffer), &ReadNum, NULL) == FALSE)
		{
			CloseHandle(hPipe);
			throw "Can not ReadFile";
		}
		else {
			
			buffer[ReadNum] = L'\0'; 
			sv->_Queue.push(buffer);
		}
		if (DisconnectNamedPipe(hPipe) == FALSE) {
			CloseHandle(hPipe);
			throw "Can not DisconnectNamedPipe";
		}
		CloseHandle(hPipe);
	}
	return 0;
}

LogServer::~LogServer()
{
	bRunning = false;
	CloseHandle(hThreadRead);
	if (!(_Queue.empty())) {
		WaitForSingleObject(ThreadWriteToFile,INFINITE);
	}
	out->close();
	
	CloseHandle(hThreadWriteToFile);
	//delete _Queue;
	delete out;
}

LogClient::LogClient()
{
	//_Queue = new queue<wchar_t*>;
	bRunnng = true;
	hThreadWrite = (HANDLE)_beginthreadex(nullptr, 0, ThreadWrite, this, 0, nullptr);
}

LogClient::~LogClient()
{
	bRunnng = false;
	if (!(_Queue.empty())) {
		WaitForSingleObject(hThreadWrite, INFINITE);
	}
	CloseHandle(hThreadWrite);
	//delete _Queue;
}

int LogClient::Write(wchar_t *_Msg)
{
	if (lstrlen(_Msg) > 1000)
		return -1;
	if (lstrlen(_Msg) <= 0)
		return -1;
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	wchar_t tmp[100] = { 0 };
	wsprintf(tmp, L"%d/%d/%d %d:%d:%d", sys.wMonth, sys.wDay, sys.wYear, sys.wHour, sys.wMinute, sys.wSecond);
	wchar_t tmp_2[1024] = { 0 };
	wsprintf(tmp_2, L"%s\r\n%s", tmp, _Msg);
	_Queue.push(tmp_2);
	return 0;
}
UINT WINAPI ThreadWrite(LPVOID lParam) {
	LogClient *sv = (LogClient*)lParam;
	while (sv->bRunnng) {
		Sleep(200);
		if (sv->_Queue.empty()) {
			continue;
		}
		HANDLE hPipe = CreateNamedPipe(L"\\\\.\\Pipe\\FrozenPipe", PIPE_ACCESS_DUPLEX,PIPE_TYPE_BYTE | PIPE_READMODE_BYTE, 1, 0, 0, 1000, NULL);
		if (GetLastError() != 231) {
			if (hPipe != nullptr) {
				CloseHandle(hPipe);
				hPipe = nullptr;
			}
			//cout << "Waiting for LogServer"<<endl;
			sv->_Queue.pop();
			continue;
		}
		if (hPipe!= nullptr)
			CloseHandle(hPipe);
		if (WaitNamedPipe(L"\\\\.\\Pipe\\FrozenPipe", NMPWAIT_WAIT_FOREVER) == FALSE)
		{
			throw "Fail in WaitNamedPipe";
		}
		hPipe= CreateFile(L"\\\\.\\Pipe\\FrozenPipe", GENERIC_READ | GENERIC_WRITE,
				0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hPipe == INVALID_HANDLE_VALUE) {
			throw "Fail in CreateFile";
		}
		DWORD WriteNum;
		if (lstrlen(sv->_Queue.front()) == 0) {
			sv->_Queue.pop();
			continue;
		}
		if (WriteFile(hPipe, sv->_Queue.front(),lstrlen(sv->_Queue.front())*2,
			&WriteNum, NULL) == FALSE)
		{
			CloseHandle(hPipe);
			throw "Fail in WriteFile";
		}
		else {
			sv->_Queue.pop();
		}
		CloseHandle(hPipe); // 关闭管道句柄
	}
	return 0;
}
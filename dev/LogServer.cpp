#include "stdafx.h"
#include "LogServer.h"


LogServer::LogServer()
{
	_Queue = new queue<wstring>;
	out = new wofstream;
	out->open("Log.txt", ios_base::out | ios_base::app);
	bRun = true;
	hMainThread = (HANDLE)_beginthreadex(nullptr, 0, LogServerMainThread, this, 0, nullptr);
	hWriteThread = (HANDLE)_beginthreadex(nullptr, 0, WriteThread, this, 0, nullptr);
}
void LogServer::LogWithTime(const wchar_t *Msg)
{
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	wchar_t tmp[100] = { 0 };
	wsprintf(tmp, L"[%d/%d/%d %d:%d:%d:%d]\t", sys.wMonth, sys.wDay, sys.wYear, sys.wHour, sys.wMinute, sys.wSecond, sys.wMilliseconds);
	wstring _push;
	_push += tmp;
	_push += Msg;
	_Queue->push(_push);
}
void LogServer::Log(const wchar_t *Msg)
{
	*out << Msg << endl;
}

UINT CALLBACK WriteThread(PVOID lParam)
{
	LogServer *ls = (LogServer*)lParam;
	while (ls->bRun || ls->_Queue->size() != 0) {
		Sleep(70);
		if (ls->_Queue->size() == 0)continue;
		ls->Log(ls->_Queue->front().c_str());
		wcout << ls->_Queue->front().c_str() << endl;
		ls->_Queue->pop();
	}
	return 0;
}


LogServer::~LogServer()
{
	bRun = false;
	out->close();
	WaitForSingleObject(LogServerMainThread, 1000);
	WaitForSingleObject(WriteThread, INFINITE);
	CloseHandle(hMainThread);
	CloseHandle(hWriteThread);
	delete _Queue;
	delete out;
}
UINT CALLBACK LogServerMainThread(PVOID lParam) {
	LogServer *ls = (LogServer*)lParam;
	while (ls->bRun) {
		HANDLE hPipe = CreateNamedPipe(L"\\\\.\\Pipe\\FrozenPipe", PIPE_ACCESS_DUPLEX, PIPE_TYPE_BYTE | PIPE_READMODE_BYTE, 1, 0, 0, 1000, NULL);
		if (hPipe == INVALID_HANDLE_VALUE) { //ls->err.err = GetLastError(); ls->err.step = 1; 
			break; 
		}
		if (ConnectNamedPipe(hPipe, nullptr) == FALSE) { //ls->err.err = GetLastError(); ls->err.step = 2; 
			CloseHandle(hPipe); 
			break; 
		}
		wchar_t buffer[1024] = { 0 };
		DWORD ReadNum;
		if (ReadFile(hPipe, buffer, sizeof(buffer), &ReadNum, NULL) == FALSE) {
			//ls->err.err = GetLastError();
			//ls->err.step = 3;
			CloseHandle(hPipe);
		}
		else {
			buffer[ReadNum] = L'\0';
			ls->_Queue->push(buffer);
		}
		if (DisconnectNamedPipe(hPipe) == FALSE) {
			//ls->err.err = GetLastError();
			//ls->err.step = 4;
			CloseHandle(hPipe);
			break;
		}
		CloseHandle(hPipe);
	}
	return 0;
}
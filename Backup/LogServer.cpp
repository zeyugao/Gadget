#include "stdafx.h"
#include "LogServer.h"


LogServer::LogServer()
{
	_Queue = new queue<wchar_t*>;
	out = new wofstream;
	out->open("Log.txt", ios_base::out | ios_base::app);
	bRun = true;
	hMainThread = (HANDLE)_beginthreadex(nullptr, 0, MainThread, this, 0, nullptr);
	hWriteThread = (HANDLE)_beginthreadex(nullptr, 0, WriteThread, this, 0, nullptr);
}

void LogServer::Log(wchar_t *Msg)
{
	*out << Msg << endl;
}

UINT CALLBACK WriteThread(PVOID lParam)
{
	LogServer *ls = (LogServer*)lParam;
	while (ls->bRun || ls->_Queue->size() != 0) {
		Sleep(200);
		if (ls->_Queue->size() == 0)continue;
		ls->Log(ls->_Queue->front());
		ls->_Queue->pop();
	}
	return 0;
}


LogServer::~LogServer()
{
	bRun = false;
	out->close();
	WaitForSingleObject(MainThread, 1000);
	WaitForSingleObject(WriteThread, INFINITE);
	CloseHandle(hMainThread);
	CloseHandle(hWriteThread);
	delete _Queue;
	delete out;
}
UINT CALLBACK MainThread(PVOID lParam) {
	LogServer *ls = (LogServer*)lParam;
	while (ls->bRun) {
		HANDLE hPipe = CreateNamedPipe(L"\\\\.\\Pipe\\FrozenPipe", PIPE_ACCESS_DUPLEX, PIPE_TYPE_BYTE | PIPE_READMODE_BYTE, 1, 0, 0, 1000, NULL);
		if (hPipe == INVALID_HANDLE_VALUE) { ls->err.err = GetLastError(); ls->err.step = 1; break; }
		if (ConnectNamedPipe(hPipe, nullptr) == FALSE) { ls->err.err = GetLastError(); ls->err.step = 2; CloseHandle(hPipe); break; }
		wchar_t buffer[1024] = { 0 };
		DWORD ReadNum;
		if (ReadFile(hPipe, buffer, sizeof(buffer), &ReadNum, NULL) == FALSE) {
			ls->err.err = GetLastError();
			ls->err.step = 3;
			CloseHandle(hPipe);
		}
		else {
			buffer[ReadNum] = L'\0';
			ls->_Queue->push(buffer);
			wprintf_s(L"%s\r\n", buffer);
			int i = GetLastError();
		}
		if (DisconnectNamedPipe(hPipe) == FALSE) {
			ls->err.err = GetLastError();
			ls->err.step = 4;
			CloseHandle(hPipe);
			break;
		}
		CloseHandle(hPipe);
	}
	return 0;
}
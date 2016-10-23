#include "stdafx.h"
#include "LogClient.h"


LogClient::LogClient()
{
	bRun = true;
	_Queue = new 	queue<wstring>;
	wchar_t a[10] = { 0 };
	wsprintf(a, L"aa");
	_Queue->push(a);
	hMainThread = (HANDLE)_beginthreadex(nullptr, 0, MainThread, this, 0, nullptr);
}


LogClient::~LogClient()
{
	bRun = false;
	WaitForSingleObject(hMainThread, INFINITE);
	CloseHandle(hMainThread);
}

int LogClient::push(wstring Msg)
{
	if (Msg.length()> 1000)
		return -1;
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	wchar_t tmp[1000] = { 0 };
	wsprintf(tmp, L"[%d/%d/%d %d:%d:%d:%d]\t", sys.wMonth, sys.wDay, sys.wYear, sys.wHour, sys.wMinute, sys.wSecond,sys.wMilliseconds);
	wstring _push;
	_push += tmp;
	_push += Msg;
	_Queue->push(_push);
	return 0;
}

UINT CALLBACK MainThread(PVOID lParam)
{
	LogClient *lc = (LogClient*)lParam;
	lc->_Queue->pop();
	while (lc->bRun){
		Sleep(100);
		if (lc->_Queue->size() == 0)continue;
		if (WaitNamedPipe(L"\\\\.\\Pipe\\FrozenPipe", NMPWAIT_WAIT_FOREVER) == FALSE){
			lc->_Queue->pop();
			continue;
		}
		HANDLE hPipe = CreateFile(L"\\\\.\\Pipe\\FrozenPipe", GENERIC_READ | GENERIC_WRITE,0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hPipe == INVALID_HANDLE_VALUE) {
			lc->err.err = GetLastError();
			lc->err.step = 1;
			continue;
		}
		DWORD WriteNum;
		if (WriteFile(hPipe, lc->_Queue->front().c_str(), lc->_Queue->front().length() * 2,&WriteNum, NULL) == FALSE)
		{
			CloseHandle(hPipe);
			lc->err.err = GetLastError();
			lc->err.step = 1;
			break;
		}
		else {
			lc->_Queue->pop();
		}
	}
	return 0;
}

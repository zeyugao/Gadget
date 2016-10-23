#pragma once

#include "stdafx.h"

string CORE_API  _stdcall  StartSvc(TCHAR*);
string r(string err, int err_code = 0);
string CORE_API  __stdcall StopSvc(TCHAR *szSvcName);
BOOL CORE_API __stdcall StopDependentServices(SC_HANDLE schService, SC_HANDLE schSCManager);

string CORE_API  WINAPI InstallSvc(TCHAR * szSvcName);
string CORE_API __stdcall DeleteSvc(TCHAR* szSvcName);
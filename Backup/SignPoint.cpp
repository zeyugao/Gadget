#include "stdafx.h"
#include "SignPoint.h"
bool  SendMsg(char * szHost, int port, const char* szMsg) {
	bool bRet = false;
	SOCKET ServerSocket = INVALID_SOCKET;
	WSADATA wsaData;
	HOSTENT *pHost;
	SOCKADDR_IN stAddr;
	do {
		if (szHost == nullptr)	break;
		if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)break;
		ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (ServerSocket < 0)	break;
		pHost = gethostbyname(szHost);
		if (pHost == nullptr)	break;
		stAddr.sin_family = AF_INET;
		stAddr.sin_addr.S_un.S_addr = *(ULONG*)pHost->h_addr;
		stAddr.sin_port = htons(port);
		if (connect(ServerSocket, (SOCKADDR*)&stAddr, sizeof(stAddr)) != 0)break;
		send(ServerSocket, szMsg, strlen(szMsg), 0);
		char Buffer[1024] = { 0 };
		int len;
		ofstream out;

		out.open("Tmp.long", ios_base::out | ios_base::app);
		if (!out)break;
		SYSTEMTIME sys;
		GetSystemTime(&sys);
		char szSystemTime[100] = { 0 };
		sprintf_s(szSystemTime, "[%d %d %d || %d:%d:%d]", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond);
		out << szSystemTime << endl;
		while (len = recv(ServerSocket, Buffer, 1024, 0)>0) {
			out << Buffer;
		}
		out << endl;
		out.close();
		bRet = true;
	} while (false);
	WSACleanup();
	if (ServerSocket != INVALID_SOCKET)
		closesocket(ServerSocket);
	return bRet;
}
bool SignPoint(char * BDUSS)
{
	bool bRet = false;
	string Msg;
	Msg += "GET /napi/user/signingetpoint?token=1_pfmxQ3TBYyd1MxJ1IBLiJdlSx2wudeoe HTTP/1.1\r\n";
	Msg += "X-Wap-Proxy-Cookie: none\r\n";
	Msg += "Content-Type: application/x-www-form-urlencoded\r\n";
	Msg += "User-Agent: Dalvik/1.6.0 (Linux; U; Android 4.4.2; HONOR H30-L01 Build/HonorH30-L01)\r\n";
	Msg += "Host: www.zybang.com\r\n";
	Msg += "Cookie: BDUSS=\\";
	Msg += BDUSS;
	Msg += "\r\n";
	Msg += "Connection: Keep-Alive\r\n";
	Msg += "X-Requested-With: com.baidu.homework\r\n";
	Msg += "\r\n";
	Msg += "cuid=&token=1_pfmxQ3TBYyd1MxJ1IBLiJdlSx2wudeoe";
	//SendMsg("www.zybang.com", 80, Msg.c_str());
	Msg.clear();

	Msg += "GET /napi/ajax/signinaddpoint HTTP/1.1\r\n";
	Msg += "X-Wap-Proxy-Cookie: none\r\n";
	Msg += "Content-Type: application/x-www-form-urlencoded\r\n";
	Msg += "User-Agent: Dalvik/1.6.0 (Linux; U; Android 4.4.2; HONOR H30-L01 Build/HonorH30-L01)\r\n";
	Msg += "Host: www.zybang.com\r\n";
	Msg += "Cookie: BDUSS=\\";
	Msg += BDUSS;
	Msg += "\r\n";
	Msg += "Connection: Keep-Alive\r\n";
	Msg += "X-Requested-With: com.baidu.homework\r\n";
	Msg += "\r\n";
	Msg += "cuid=&token=1_pfmxQ3TBYyd1MxJ1IBLiJdlSx2wudeoe";
	SendMsg("www.zybang.com", 80, Msg.c_str());
	return  bRet;
}
#include <iostream>
#include <cstdlib>
#include <memory>
#include <string>
#include <cmath>
#include <fstream>
#include <cmath>
#include <Windows.h>
#include <process.h>
#include<wininet.h>
#pragma comment(lib,"wininet.lib")
bool GetChapterList();
bool GetChaper(std::wstring Chapter_Url, int);
void Trim(int count);
std::wstring GetSingleChapter(std::wstring & wChapterList, int & b);
std::wstring & ReplaceAll(std::wstring & str, const std::wstring & old_value, const std::wstring & new_value);
std::wifstream fsChapterReader;
int main()
{
	if (!GetChapterList())
		return 0;
	fsChapterReader.open("e:\\chapter_list.txt", std::ios_base::in);
	if (!fsChapterReader.good()) {
		std::cout << "无法打开chapter_list.txt" << std::endl; return 0;
	}
	std::wcout.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
	fsChapterReader.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
	std::wstring wChapterList((std::istreambuf_iterator<wchar_t>(fsChapterReader)), std::istreambuf_iterator<wchar_t>());
	std::wstring SingleChapter;
	int b = 0, count = 1;
	while ((SingleChapter = GetSingleChapter(wChapterList, b)) != L"") {
		GetChaper(SingleChapter, count);
		Trim(count++);
		Sleep(100);
	}
	fsChapterReader.close();
}
bool GetChapterList() {
	DWORD byteread = 0;
	char buffer[100];
	memset(buffer, 0, 100);
	HINTERNET internetopen;
	HANDLE createfile;
	HINTERNET internetopenurl;
	bool bRet = false;
	do {
		internetopen = InternetOpen(L"Testing", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
		if (internetopen == NULL)
		{
			std::cout << "Internet open failed!" << std::endl;
			break;
		}
		internetopenurl = InternetOpenUrl(internetopen, L"http://3g.nuoha.net/book/chapter_list/175924.html", NULL, 0, INTERNET_FLAG_RELOAD, 0);
		if (internetopenurl == NULL)
		{
			std::cout << "Internet open url failed!" << std::endl;
			break;
		}
		BOOL hwrite;
		DWORD written;
		createfile = CreateFile(L"e:\\chapter_list.txt", GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
		if (createfile == INVALID_HANDLE_VALUE)
		{
			std::cout << "Create File failed!" << std::endl;
			break;
		}
		BOOL internetreadfile;
		bool Flag = true;
		while (1)
		{
			internetreadfile = InternetReadFile(internetopenurl, buffer, sizeof(buffer), &byteread);
			if (byteread == 0)
				break;
			hwrite = WriteFile(createfile, buffer, sizeof(buffer), &written, NULL);
			if (hwrite == 0)
			{
				std::cout << "Write to file failed!" << std::endl;
				Flag = false;
				break;
			}
		}
		if (!Flag)
			break;
		std::cout << "Finished downloading!" << std::endl;
		bRet = true;
	} while (0);
	if (createfile != INVALID_HANDLE_VALUE)
		CloseHandle(createfile);
	if (internetopenurl != INVALID_HANDLE_VALUE)
		InternetCloseHandle(internetopenurl);
	if (internetopen != INVALID_HANDLE_VALUE)
		InternetCloseHandle(internetopen);
	return bRet;
}
bool GetChaper(std::wstring Chapter_Url, int count)
{
	DWORD byteread = 0;
	char buffer[100];
	memset(buffer, 0, 100);
	HINTERNET internetopen;
	HANDLE createfile;
	HINTERNET internetopenurl;
	bool bRet = false;
	do {
		std::wcout << L"Start downloading:" << Chapter_Url << std::endl;
		internetopen = InternetOpen(L"Testing", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
		if (internetopen == NULL)
		{
			std::cout << "Internet open failed!" << std::endl;
			break;
		}
		internetopenurl = InternetOpenUrl(internetopen, Chapter_Url.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);
		if (internetopenurl == NULL)
		{
			std::cout << "Internet open url failed!" << std::endl;
			break;
		}
		BOOL hwrite;
		DWORD written;
		wchar_t temp_file[256] = { 0 };
		wsprintf(temp_file, L"e:\\Temp\\Chapter_%d.txt", count);
		createfile = CreateFile(temp_file, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
		if (createfile == INVALID_HANDLE_VALUE)
		{
			std::cout << "Create File failed!" << std::endl;
			break;
		}
		BOOL internetreadfile;
		bool Flag = true;
		while (1)
		{
			internetreadfile = InternetReadFile(internetopenurl, buffer, sizeof(buffer), &byteread);
			if (byteread == 0)
				break;
			hwrite = WriteFile(createfile, buffer, sizeof(buffer), &written, NULL);
			if (hwrite == 0)
			{
				std::cout << "Write to file failed!" << std::endl;
				Flag = false;
				break;
			}
		}
		if (!Flag)
			break;
		std::wcout << L"Finished downloading!" << std::endl;
		bRet = true;
	} while (0);
	if (createfile != INVALID_HANDLE_VALUE)
		CloseHandle(createfile);
	if (internetopenurl != INVALID_HANDLE_VALUE)
		InternetCloseHandle(internetopenurl);
	if (internetopen != INVALID_HANDLE_VALUE)
		InternetCloseHandle(internetopen);
	return bRet;
}
void Trim(int count)
{
	std::wifstream fsChapterReaderTrimer;
	wchar_t temp_file[256] = { 0 };
	wsprintf(temp_file, L"e:\\Temp\\Chapter_%d.txt", count);
	fsChapterReaderTrimer.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
	fsChapterReaderTrimer.open(temp_file, std::ios_base::in);
	std::wstring wChapterTrimer((std::istreambuf_iterator<wchar_t>(fsChapterReaderTrimer)), std::istreambuf_iterator<wchar_t>());

	int delete_find = wChapterTrimer.find(L"<div class=\"row02\">");
	int b = wChapterTrimer.find(L"<div class=\"row02\">", delete_find + 10) + lstrlen(L"<div class=\"row02\">");
	int e = wChapterTrimer.find(L"</div>", b);
	std::wstring Content(wChapterTrimer.c_str() + b + 1, wChapterTrimer.c_str() + e);
	ReplaceAll(Content, L"    ", L"");
	ReplaceAll(Content, L"<br/>", L"");
	wchar_t Content_file[256] = { 0 };
	wsprintf(Content_file, L"e:\\Book\\Chapter_%d.txt", count);
	std::wofstream fsChapterWriterTrimer;
	fsChapterWriterTrimer.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
	fsChapterWriterTrimer.open(Content_file, std::ios_base::out | std::ios_base::app);
	fsChapterWriterTrimer << Content;

	fsChapterReaderTrimer.close();
	fsChapterWriterTrimer.close();
}
std::wstring GetSingleChapter(std::wstring & wChapterList, int & b)
{
	int b_ = wChapterList.find(L"<td><a href=\"", b);
	if (b_ != std::string::npos) {
		b_ += lstrlen(L"<td><a href=\"");
		int e_ = wChapterList.find(L"\">", b_);
		std::wstring prep_url(wChapterList.c_str() + b_, wChapterList.c_str() + e_);
		std::wstring url = L"http://3g.nuoha.net" + prep_url;
		b = e_ + 1;
		return url;
	}
	return L"";
}

std::wstring & ReplaceAll(std::wstring&   str, const   std::wstring&   old_value, const   std::wstring&   new_value)
{
	for (std::wstring::size_type pos(0); pos != std::wstring::npos; pos += new_value.length()) {
		if ((pos = str.find(old_value, pos)) != std::wstring::npos)
			str.replace(pos, old_value.length(), new_value);
		else   break;
	}
	return   str;
}
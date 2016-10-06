
#ifndef _DEBUG
#pragma GCC optimize(2)
#include <codecvt>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <memory>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <queue>
#include <cstring>
#include <fstream>
#include <cmath>
#include <Windows.h>
#include <iterator>
#include <set>
#include <process.h>
#include <ctime>
#include <utility>
#include <cctype>
#include <bitset>
using namespace std;
#endif // _DEBUG

//不会用正则
vector<wstring> match[2];
vector<wstring> Name;
int main() {
	wifstream fsFileListReader, fsWholeFileReader, fsKeywordReader;
	wofstream fsFileOutputer, fsLogOutputer;
	wstringstream ssLog;
	fsFileListReader.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
	fsWholeFileReader.imbue(std::locale("chs"));
	fsLogOutputer.imbue(locale("chs"));
	fsFileOutputer.imbue(locale("chs"));
	fsKeywordReader.imbue(locale("chs"));
	wcout.imbue(locale("chs"));
	fsKeywordReader.open("keyword.txt");
	int n;
	//初始化
	fsKeywordReader>>n;
	wchar_t wszKeyWord[256] = { 0 };
	for (int i=0;i<n&& fsKeywordReader.getline(wszKeyWord, 256);i++)
		Name.push_back(wszKeyWord);
	for (int i = 0;i<n*2 fsKeywordReader.getline(wszKeyWord, 256) && lstrcmp(wszKeyWord, L""); i++)
		match[i & 1].push_back(wszKeyWord);
	if (match[0].size() != match[1].size()) {
		wcout << L"有未定义的结束标志" << endl;
		goto exit_;
	}
	//输出的csv
	fsFileOutputer.open("output.csv", ios_base::out | ios_base::app);
	//all.txt记录了需要读取的文件
	//用cd ***
	//dir /b /a:-d > all.txt 获取
	fsFileListReader.open("all.txt", ios_base::in);
	fsLogOutputer.open("log.txt", ios_base::out | ios_base::app);
	wchar_t wszSingleFile[256] = { 0 };
	//标题栏
	for (auto tmp : Name)
		fsFileOutputer << tmp << ",";
	fsFileOutputer << endl;
	fsFileListReader.getline(wszSingleFile, 256);
	while (lstrcmp(wszSingleFile, L"")) {
		wchar_t szSingleFileFullPath[256] = { 0 };
		wsprintf(szSingleFileFullPath, L"temp\\%s", wszSingleFile);
		fsWholeFileReader.open(szSingleFileFullPath, ios_base::in);
		if (fsWholeFileReader.good()) {
			wstring str((std::istreambuf_iterator<wchar_t>(fsWholeFileReader)), std::istreambuf_iterator<wchar_t>());
			//文件长度过短
			if (str.size() <= 4) {
				wcout << "The file -" << wszSingleFile << " is empty" << endl,
					ssLog << "The file -" << wszSingleFile << " is empty" << endl;
				continue;
			}
			int nTb, nTe;
			fsFileOutputer << wszSingleFile << ",";
			for (int i = 0; i < match[0].size(); i++) {
				nTb = str.find(match[0][i]);
				if (nTb != string::npos) {
					nTe = str.find(match[1][i], nTb);
					wstring newstr(str.c_str() + nTb + match[0][i].size(), str.c_str() + nTe);
					fsFileOutputer << newstr << ",";
				}
				else
					wcout << L"Something wrong with " << match[0][i] << L" at " << wszSingleFile << endl,
					ssLog << L"Something wrong with " << match[0][i] << L" at " << wszSingleFile << endl,
					fsFileOutputer << ",";
			}
			fsFileOutputer << endl;
		}
		fsWholeFileReader.close();
		fsFileListReader.getline(wszSingleFile, 256);
	}
	fsLogOutputer << ssLog.str() << endl;
exit_:
	fsFileListReader.close();
	fsFileOutputer.close();
	fsWholeFileReader.close();
	fsLogOutputer.close();
	system("pause");
	return 0;
}
//GB2312:
std::ifstream oo;
oo.imbue(std::locale("chs"));
//UTF-8 :
std::wifstream t;
t.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>)); 
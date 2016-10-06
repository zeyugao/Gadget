//GB2312:
//for ifstream
std::ifstream oo;
oo.imbue(std::locale("chs"));

//for cin/cout
cin.imbue(std::locale("chs"));
cout.imbue(std::locale("chs"));
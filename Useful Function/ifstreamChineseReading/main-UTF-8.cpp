//UTF-8
std::wifstream oo;
oo.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>)); 

//for cin/cout
cin.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>)); 
cout.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>)); 
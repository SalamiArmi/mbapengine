#include "String.h"

int main()
{
	Argon::String s = "aa";
	s = s + "A "; 

	Argon::String t = "bb";

	bool aaaaaa = t != s;

	t = "AAAA";

	wchar_t* NarrowToWide = t.cwide_str();

	int i = 0;

	Argon::wString tt = L"TTT";
	Argon::wString qq = L"TTT";

	aaaaaa = qq != tt;

	const char* WideToCharPtr = tt.c_str();

	i = 0;
		
	return 0;
}
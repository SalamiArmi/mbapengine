#include "ArgonQString.h"
#include "ArgonPlatform.h"


int main()
{
	Argon::QString pp("Here");

	Argon::QString tt("HTere");

	int a = tt.Length();

	bool ttttt = pp != tt;

	ttttt = pp == "Here";

	const char* aaa = pp.c_str();

	return 0;
}
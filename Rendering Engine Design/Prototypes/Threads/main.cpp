#include "ArgonThread.h"

#include "stdio.h"

class lol : public Argon::ThreadTarget
{
public:
	void Method()
	{
		for (int i = 0; i < 10000000; ++i)
		{
			printf("%X", rand());
		}
	}
};

int main()
{
	lol rofl;
	Argon::Thread a;
	a.Start(&rofl);

	for (int i = 0; i < 10; ++i)
	{
		Sleep(500);
		a.Pause();
		Sleep(500);
		a.Resume();
	}

	return 0;
}

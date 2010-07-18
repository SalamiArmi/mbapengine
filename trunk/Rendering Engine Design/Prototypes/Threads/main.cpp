#include "ArgonThread.h"

#include "stdio.h"

class lol : public Argon::ThreadTarget
{
public:
	int i;
	void Method()
	{
		for (int i = 0; i < 10000000; ++i)
		{
			printf("@#124\n");
		}
	}
};

int main()
{
	lol rofl;
	Argon::Thread a;
	a.SetTarget(&rofl);
	a.Start();

	Sleep(100);

	return 0;
}

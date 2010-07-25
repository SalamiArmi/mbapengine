#include "ArgonThread.h"
#include "ArgonMutex.h"
#include "ArgonEvent.h"

#include "stdio.h"
#include "math.h"
#include "time.h"

Argon::Mutex GlobalMutex;
Argon::Event GlobalEvent;

void printSomething(unsigned long input)
{
	GlobalMutex.Lock();
	printf("%c", input);
	GlobalMutex.Unlock();
}

class testThread : public Argon::ThreadTarget
{
public:
	void Method()
	{
		for (int i = 0; i < 10000; ++i)
		{
			GlobalEvent.Wait(rand()%50);
			printSomething(rand());
		}
	}
};

static const unsigned int number = 16;

int main()
{
	testThread threadObjects[number];
	Argon::Thread threads[number];

	for (int i = 0; i < number; ++i)
	{
		threads[i].Start(&threadObjects[i]);
	}

	while (threads[0].Running())
	{
		GlobalEvent.Set();
		Sleep(1);
		GlobalEvent.Reset();
	}

	for (int i = 0; i < number; ++i)
	{
		threads[i].Stop();
	}

	return 0;
}

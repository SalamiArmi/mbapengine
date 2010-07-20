#include "ArgonThread.h"
#include "ArgonMutex.h"

#include "stdio.h"

Argon::Mutex GlobalMutex;

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
			printSomething(rand());
		}
	}
};

int main()
{
	testThread
		thread1,
		thread2;

	Argon::Thread
		a,
		b;

	a.Start(&thread1);
	b.Start(&thread2);

	while (a.Running() || b.Running())
	{
		Argon::Thread::Yield();
		printSomething('\n');
	}

	a.Stop();
	b.Stop();

	return 0;
}

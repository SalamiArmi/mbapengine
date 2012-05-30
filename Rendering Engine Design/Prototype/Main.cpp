#include "ArgonQString.h"
#include "ArgonPlatform.h"

#include "ArgonThread.h"
#include "ArgonMutex.h"
#include "ArgonEvent.h"

#include "ArgonPair.h"

#include "stdio.h"
#include "math.h"
#include "time.h"

#include <string>
#include <iostream>
#include <map>

#include "C:\Users\Mitchel\Desktop\Rendering Engine\trunk\Rendering Engine Design\Prototype\AgronPrototypes\Platform Dependencies\ArgonMemoryPool.h"

Argon::MemoryPool* Pool2;

Argon::Event GlobalEvent;

class StdThread : public Argon::ThreadTarget
{
public:
	void Method()
	{
		GlobalEvent.Wait();
		for (int i = 0; i < 10000; ++i)
		{
			char *ptrArray = new char[1000];
		}

		std::cout << "New Done" << std::endl;
	}
};

class ArgonStringThread : public Argon::ThreadTarget
{
public:
	void Method()
	{
		GlobalEvent.Wait();
		Argon::Vector< char* > pppp;
		for (int i = 0; i < 10000; ++i)
		{
			char *ptrArray = (char *)Pool2->GetDataBlock(1000) ;
			pppp.Push_Back( ptrArray );
		}

		std::cout << "Argon MemoryPool Done" << std::endl;
	}
};

int main()
{
	StdThread TargetA;
	ArgonStringThread TargetB;

	Argon::Thread threads[2];

	Pool2 = new Argon::MemoryPool(128);

	threads[0].Start(&TargetA);
	threads[1].Start(&TargetB);
	Argon::Thread::Yield(1000);
	std::cout << "Starting!" << std::endl;
	GlobalEvent.Set();
	while (threads[0].Running() || threads[1].Running())
	{
		Sleep(1);
	}

	threads[0].Stop();
	threads[1].Stop();

	return 0;
}
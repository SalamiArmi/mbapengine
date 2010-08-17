#include "ArgonQString.h"
#include "ArgonPlatform.h"

#include "ArgonThread.h"
#include "ArgonMutex.h"
#include "ArgonEvent.h"

#include "stdio.h"
#include "math.h"
#include "time.h"

#include <string>
#include <iostream>

#include <ArgonMemory.h>

Argon::Event GlobalEvent;

class StdThread : public Argon::ThreadTarget
{
public:
	void Method()
	{
		Argon::AutoPtr< Argon::CharAllocator > pp;

		char* AllocatedStr = pp->Allocate(5);
	}
};

class ArgonStringThread : public Argon::ThreadTarget
{
public:
	void Method()
	{
		GlobalEvent.Wait();
		for (int i = 0; i < 100000; ++i)
		{
			Argon::String aaaa;	
			aaaa = "TESTING STRING";
			char a = aaaa.At(0);
			aaaa += "AAA";
			bool t = aaaa == "TESTING STRING";
			t = aaaa != "TESTING STRING";
			aaaa += aaaa;
			//short ab = 25;
			//aaaa = Argon::String(ab);

			//std::cout << aaaa.c_str() << std::endl;

			//t = aaaa.FindString( Argon::String("TESTING") );

			for(Argon::String::Iterator it = aaaa.Begin(); it != aaaa.End(); ++it)
			{
				int i = 0;
			}
		}


		std::cout << "Argon String Done" << std::endl;
	}
};

int main()
{
	StdThread TargetA;
	ArgonStringThread TargetB;

	Argon::Thread threads[2];

	threads[0].Start(&TargetA);
	threads[1].Start(&TargetB);
	Argon::Thread::Yield(1000);
	std::cout << "Starting!" << std::endl;
	GlobalEvent.Set();
	while (threads[0].Running() || threads[1].Running())
	{
		Sleep(0);
	}

	threads[0].Stop();
	threads[1].Stop();
	return 0;
}
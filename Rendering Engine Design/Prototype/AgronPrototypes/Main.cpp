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

Argon::Event GlobalEvent;

class StdThread : public Argon::ThreadTarget
{
public:
	void Method()
	{
		GlobalEvent.Wait();
		for (int i = 0; i < 100000; ++i)
		{
			std::string aaaa;	
			aaaa = "TESTING STRING";
			char a = aaaa.at(0);
			
			for(std::string::iterator it = aaaa.begin(); it != aaaa.end(); ++it)
			{
				int i = 0;
			}
		}
		std::cout << "Std String Done" << std::endl;
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
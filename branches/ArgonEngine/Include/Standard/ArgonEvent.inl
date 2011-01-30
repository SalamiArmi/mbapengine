#include "ArgonEvent.h"

namespace Argon
{

	Event::Event()
	{
	}

	Event::~Event()
	{
	}

	void Event::Wait()
	{
		WaitImpl(0);
	}

	bool Event::Wait(unsigned long Milliseconds)
	{
		return WaitImpl(Milliseconds);
	}

	void Event::Set()
	{
		SetImpl();
	}

	void Event::Reset()
	{
		ResetImpl();
	}

}
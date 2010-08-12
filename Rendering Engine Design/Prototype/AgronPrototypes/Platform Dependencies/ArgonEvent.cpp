#include "ArgonEvent.h"

Argon::Event::Event()
{
}

Argon::Event::~Event()
{
}

void Argon::Event::Wait()
{
	WaitImpl(0);
}

bool Argon::Event::Wait(unsigned long Milliseconds)
{
	return WaitImpl(Milliseconds);
}

void Argon::Event::Set()
{
	SetImpl();
}

void Argon::Event::Reset()
{
	ResetImpl();
}
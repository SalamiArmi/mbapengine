#include "ArgonThread.h"

Argon::Thread::Thread()
{
}

Argon::Thread::~Thread()
{
}

void Argon::Thread::Start()
{
	StartImpl();
}

void Argon::Thread::Start(ThreadTarget *NewTarget)
{
	m_RunnableObject = NewTarget;
	StartImpl();
}

void Argon::Thread::Stop()
{
	StopImpl();
}

void Argon::Thread::Pause()
{
	PauseImpl();
}

void Argon::Thread::Resume()
{
	ResumeImpl();
}

void Argon::Thread::Yield()
{
}

void Argon::Thread::Yield(unsigned long Milliseconds)
{
}

bool Argon::Thread::Running()
{
	return false;
}

void Argon::Thread::Join()
{
}

bool Argon::Thread::Join(unsigned long Milliseconds)
{
	return false;
}
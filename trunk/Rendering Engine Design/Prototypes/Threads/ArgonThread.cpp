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

bool Argon::Thread::Running()
{
	return RunningImpl();
}

void Argon::Thread::Join()
{
	JoinImpl(0);
}

bool Argon::Thread::Join(unsigned long Milliseconds)
{
	return JoinImpl(Milliseconds);
}
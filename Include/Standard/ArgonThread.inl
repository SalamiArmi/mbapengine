#include "ArgonThread.h"

namespace Argon
{

	Thread::Thread()
	{
	}

	Thread::~Thread()
	{
	}

	void Thread::Start()
	{
		StartImpl();
	}

	void Thread::Start(ThreadTarget *NewTarget)
	{
		m_RunnableObject = NewTarget;
		StartImpl();
	}

	void Thread::Stop()
	{
		StopImpl();
	}

	void Thread::Pause()
	{
		PauseImpl();
	}

	void Thread::Resume()
	{
		ResumeImpl();
	}

	bool Thread::Running()
	{
		return RunningImpl();
	}

	void Thread::Join()
	{
		JoinImpl(0);
	}

	bool Thread::Join(unsigned long Milliseconds)
	{
		return JoinImpl(Milliseconds);
	}

}
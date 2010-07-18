#pragma once

#include <windows.h>
#include <process.h>

// Disable legacy windows thing
#ifdef Yield
#undef Yield
#endif

namespace Argon
{
	class ThreadImpl
	{
		typedef HANDLE usableThread;

	protected:
		void StartImpl();
		void StopImpl();

		void PauseImpl();
		void ResumeImpl();

		usableThread m_handleToThread;

		unsigned int m_ThreadID;
	};
}

void Argon::ThreadImpl::StartImpl()
{
	_beginthreadex(0, 0, &entryPoint, this, 0, &m_ThreadID);
}

void Argon::ThreadImpl::StopImpl()
{
	CloseHandle(m_handleToThread);
	_endthreadex(m_ThreadID);
}

inline void Argon::ThreadImpl::PauseImpl()
{
	if (SuspendThread(m_handleToThread) == -1)
	{
		// Make sure we aren't causing any leaks
		if (m_handleToThread != 0)
		{
			CloseHandle(m_handleToThread);
		}

		// Fetch a handle that can be used to resume and suspend, and suspend the thread (with error checking this time)
		SuspendThread(m_handleToThread = OpenThread(THREAD_SUSPEND_RESUME, false, m_ThreadID));
	}
}

inline void Argon::ThreadImpl::ResumeImpl()
{
	if (ResumeThread(m_handleToThread) == -1)
	{
		// Make sure we aren't causing any leaks
		if (m_handleToThread != 0)
		{
			CloseHandle(m_handleToThread);
		}

		// Fetch a handle that can be used to resume and suspend, and resume the thread (with error checking this time)
		ResumeThread(m_handleToThread = OpenThread(THREAD_SUSPEND_RESUME, false, m_ThreadID));
	}
}
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
	protected:
		ThreadImpl();
		virtual ~ThreadImpl();

		void StartImpl();
		void StopImpl();

		void PauseImpl();
		void ResumeImpl();

		static unsigned __stdcall EntryPoint(void* pThread);
		void AquireThreadFromID();

		HANDLE m_handleToThread;
		unsigned int m_ThreadID;
		ThreadTarget *m_RunnableObject;
	};

	inline ThreadImpl::ThreadImpl()
	:
	m_ThreadID(0),
	m_RunnableObject(0),
	m_handleToThread(0)
	{
	}

	inline ThreadImpl::~ThreadImpl()
	{
	}

	inline unsigned __stdcall ThreadImpl::EntryPoint(void* pThread)
	{
		reinterpret_cast<ThreadTarget *>(pThread)->Method();
		return 0;
	}

	inline void ThreadImpl::AquireThreadFromID()
	{
		m_handleToThread = OpenThread(THREAD_SUSPEND_RESUME, false, m_ThreadID);
	}

	inline void ThreadImpl::StartImpl()
	{
		_beginthreadex(0, 0, EntryPoint, (void *)m_RunnableObject, 0, &m_ThreadID);
		AquireThreadFromID();
	}

	inline void ThreadImpl::StopImpl()
	{
		CloseHandle(m_handleToThread);
		_endthreadex(m_ThreadID);
	}

	inline void ThreadImpl::PauseImpl()
	{
		if (m_handleToThread == 0)
		{
			AquireThreadFromID();
		}

		SuspendThread(m_handleToThread);
	}

	inline void ThreadImpl::ResumeImpl()
	{
		if (m_handleToThread == 0)
		{
			AquireThreadFromID();
		}

		ResumeThread(m_handleToThread);
	}
}

#pragma once

#include <windows.h>
#include <process.h>

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

		bool RunningImpl();
		static void YieldImpl(unsigned long Milliseconds);

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
		m_handleToThread = OpenThread(STANDARD_RIGHTS_ALL, false, m_ThreadID);
	}

	inline void ThreadImpl::StartImpl()
	{
		_beginthreadex(0, 0, EntryPoint, (void *)m_RunnableObject, 0, &m_ThreadID);
		AquireThreadFromID();
	}

	inline void ThreadImpl::StopImpl()
	{
		if (RunningImpl())
		{
			_endthreadex(m_ThreadID);
		}
		CloseHandle(m_handleToThread);
	}

	inline void ThreadImpl::PauseImpl()
	{
		if (RunningImpl())
		{
			SuspendThread(m_handleToThread);
		}
	}

	inline void ThreadImpl::ResumeImpl()
	{
		if (RunningImpl())
		{
			ResumeThread(m_handleToThread);
		}
	}

	inline bool ThreadImpl::RunningImpl()
	{
		return (WAIT_OBJECT_0 != WaitForSingleObject(m_handleToThread, 0));
	}

	inline void ThreadImpl::YieldImpl(unsigned long Milliseconds)
	{
		Sleep(Milliseconds);
	}
}

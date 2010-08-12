#pragma once

#include <windows.h>

namespace Argon
{
	class EventImpl
	{
	protected:
		EventImpl();
		virtual ~EventImpl();

		bool WaitImpl(unsigned long Milliseconds);
		void SetImpl();
		void ResetImpl();

		HANDLE m_EventObject;
	};

	inline EventImpl::EventImpl()
	{
		m_EventObject = CreateEvent(0, false, false, 0);
	}

	inline EventImpl::~EventImpl()
	{
		CloseHandle(m_EventObject);
	}

	inline bool EventImpl::WaitImpl(unsigned long Milliseconds)
	{
		if (Milliseconds == 0)
		{
			--Milliseconds;
		}
		return WaitForSingleObject(m_EventObject, Milliseconds) != WAIT_TIMEOUT;
	}

	inline void EventImpl::SetImpl()
	{
		SetEvent(m_EventObject);
	}

	inline void EventImpl::ResetImpl()
	{
		ResetEvent(m_EventObject);
	}
}

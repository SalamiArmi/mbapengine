#pragma once

#include <windows.h>

namespace Argon
{
	class MutexImpl
	{
	protected:
		MutexImpl();
		virtual ~MutexImpl();

		void LockImpl();
		void UnlockImpl();

		CRITICAL_SECTION m_CriticalSection;
	};

	inline MutexImpl::MutexImpl()
	{
		InitializeCriticalSection(&m_CriticalSection);
	}

	inline MutexImpl::~MutexImpl()
	{
		DeleteCriticalSection(&m_CriticalSection);
	}

	inline void MutexImpl::LockImpl()
	{
		EnterCriticalSection(&m_CriticalSection);
	}
	
	inline void MutexImpl::UnlockImpl()
	{
		LeaveCriticalSection(&m_CriticalSection);
	}
}
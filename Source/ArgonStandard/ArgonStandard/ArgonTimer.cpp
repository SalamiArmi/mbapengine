#include <Standard/ArgonTimer.h>
#include "Windows.h"
#include <algorithm>

namespace Argon
{
	ArgonStandard Timer::Timer()
		: m_TimerMask(0)
	{
		Reset();
	}

	ArgonStandard Timer::~Timer()
	{
	}

	ArgonStandard void Timer::Reset()
	{
		__w64 unsigned long ProcMask, SysMask;

		GetProcessAffinityMask(GetCurrentProcess(), &ProcMask, &SysMask);

		//If ProcMask 0 only 1 core available
		if(ProcMask == 0)
			ProcMask = 1;

		if(m_TimerMask == 0)
		{
			m_TimerMask = 1;
			while((m_TimerMask & ProcMask) == 0)
				m_TimerMask <<= 1;
		}

		HANDLE Thread = GetCurrentThread();

		// Set affinity to the first core
		__w64 unsigned long OldMask = SetThreadAffinityMask(Thread, m_TimerMask);

		// Get the constant frequency
		QueryPerformanceFrequency(&m_Frequency);

		// Query the timer
		QueryPerformanceCounter(&m_StartTime);
		m_StartTick = GetTickCount();

		// Reset affinity
		SetThreadAffinityMask(Thread, OldMask);

		m_LastTime = 0;
		m_ZeroClock = clock();
	}

	ArgonStandard unsigned long Timer::GetMilliseconds()
	{
		LARGE_INTEGER CurrentTime;

		HANDLE Thread = GetCurrentThread();

		// Set affinity to the first core
		ulong OldMask = SetThreadAffinityMask(Thread, m_TimerMask);

		// Query the timer
		QueryPerformanceCounter(&CurrentTime);

		// Reset affinity
		SetThreadAffinityMask(Thread, OldMask);

		LONGLONG NewTime = CurrentTime.QuadPart - m_StartTime.QuadPart;

		// scale by 1000 for milliseconds
		unsigned long NewTicks = (unsigned long) (1000 * NewTime / m_Frequency.QuadPart);

		unsigned long Check = GetTickCount() - m_StartTick;
		signed long MilliSecOff = (signed long)(NewTicks - Check);
		if (MilliSecOff < -100 || MilliSecOff > 100)
		{
			// We must keep the timer running forward :)
			LONGLONG Adjust = (std::min)(MilliSecOff * m_Frequency.QuadPart / 1000, NewTime - m_LastTime);
			m_StartTime.QuadPart += Adjust;
			NewTime -= Adjust;

			// Re-calculate milliseconds
			NewTicks = (unsigned long) (1000 * NewTime / m_Frequency.QuadPart);
		}

		// Record last time for adjust
		m_LastTime = NewTime;
		return NewTicks;
	}

	ArgonStandard unsigned long Timer::GetMicroseconds()
	{
		LARGE_INTEGER CurrentTime;

		HANDLE Thread = GetCurrentThread();

		// Set affinity to the first core
		DWORD OldMask = SetThreadAffinityMask(Thread, m_TimerMask);

		// Query the timer
		QueryPerformanceCounter(&CurrentTime);

		// Reset affinity
		SetThreadAffinityMask(Thread, OldMask);

		LONGLONG NewTime = CurrentTime.QuadPart - m_StartTime.QuadPart;

		// get milliseconds to check against GetTickCount
		unsigned long NewTicks = (unsigned long) (1000 * NewTime / m_Frequency.QuadPart);

		unsigned long Check = GetTickCount() - m_StartTick;
		signed long MicroSecOff = (signed long)(NewTicks - Check);
		if (MicroSecOff < -100 || MicroSecOff > 100)
		{
			// We must keep the timer running forward :)
			LONGLONG Adjust = (std::min)(MicroSecOff * m_Frequency.QuadPart / 1000, NewTime - m_LastTime);
			m_StartTime.QuadPart += Adjust;
			NewTime -= Adjust;
		}

		// Record last time for adjust
		m_LastTime = NewTime;

		// scale by 1000000 for microseconds
		unsigned long NewMicro = (unsigned long) (1000000 * NewTime / m_Frequency.QuadPart);

		return NewMicro;
	}

	ArgonStandard unsigned long Timer::GetMillisecondsCPU()
	{
		clock_t NewClock = clock();
		return (unsigned long)( (float)( NewClock - m_ZeroClock ) / ( (float)CLOCKS_PER_SEC / 1000.0 ) ) ;
	}

	ArgonStandard unsigned long Timer::GetMicrosecondsCPU()
	{
		clock_t NewClock = clock();
		return (unsigned long)( (float)( NewClock - m_ZeroClock ) / ( (float)CLOCKS_PER_SEC / 1000000.0 ) ) ;
	}

} //Namespace
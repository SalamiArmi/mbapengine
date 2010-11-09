#ifndef _ARGONTIMER_HEADER_
#define _ARGONTIMER_HEADER_

#include <ctime>
#include "Windows.h"
#include "ArgonStandard.h"

namespace Argon
{
#if defined _WIN32
	class ArgonStandard Timer
	{
	public:
		Timer();
		~Timer();

		///RESET(VOID)
		///
		///Resets timer
		///
		///No Params:
		void Reset();

		///GETMILLISECONDS(UNSIGNEDLONG)
		///
		///Returns milliseconds since initialisation or last reset
		///
		///No Params:
		unsigned long GetMilliseconds();

		///GETTMICROSECONDS(UNSIGNEDLONG)
		///
		///Returns microseconds since initialisation or last reset
		///
		///No Params:
		unsigned long GetMicroseconds();

		///GETMILLISECONDSCPU(UNSIGNEDLONG)
		///
		///Returns milliseconds since initialisation or last reset, only CPU time measured
		///
		///No Params:
		unsigned long GetMillisecondsCPU();

		///GETTMICROSECONDSCPU(UNSIGNEDLONG)
		///
		///Returns microseconds since initialisation or last reset, only CPU time measured
		///
		///No Params:
		unsigned long GetMicrosecondsCPU();

	protected:
		struct timeval	m_Start;
		clock_t			m_ZeroClock;
		__int64			m_LastTime;
		ulong			m_StartTick;
		ulong			m_TimerMask;
		LARGE_INTEGER	m_StartTime;
		LARGE_INTEGER	m_Frequency;
	};

#endif //Must be Win32 for this timer to work

} //Namespace

#endif //_ARGONTIMER_HEADER_
////////////////////////////////////////////////////////////////
//
//	ArgonEvent.h : Argon Threading Event
//
//	Copyright ©2010 Argon. All rights reserved.
//	Removal of this copyright notice is not permitted.
//
///////////////////////////////////////////////////////////////


#pragma once

#if defined (_WIN32)
#include "ArgonEventWin32.h"
#else
// You're screwed lol
#endif

namespace Argon
{
	class Event : private EventImpl
	{
	public:
		Event();
		~Event();

		void Wait();
		bool Wait(unsigned long Milliseconds);
		void Set();

		void Reset();
	};
}
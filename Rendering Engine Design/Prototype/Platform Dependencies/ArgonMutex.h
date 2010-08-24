////////////////////////////////////////////////////////////////
//
//	ArgonMutex.h :
//
//	Copyright ©2010 Argon. All rights reserved.
//	Removal of this copyright notice is not permitted.
//
///////////////////////////////////////////////////////////////

#pragma once

#if defined (_WIN32)
#include "ArgonMutexWin32.h"
#else
// You're screwed lol
#endif

namespace Argon
{
	class Mutex : private MutexImpl
	{
	public:
		Mutex();
		~Mutex();

		void Lock();
		void Unlock();
	};
}
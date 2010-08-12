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
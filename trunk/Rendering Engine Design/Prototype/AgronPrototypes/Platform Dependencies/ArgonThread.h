////////////////////////////////////////////////////////////////
//
//	ArgonThread.h :
//
//	Copyright ©2010 Argon. All rights reserved.
//	Removal of this copyright notice is not permitted.
//
///////////////////////////////////////////////////////////////

#pragma once

#include "ArgonThreadTarget.h"

#if defined (_WIN32)
#include "ArgonThreadWin32.h"
#else
// You're screwed lol
#endif

// Disable legacy windows thing
#ifdef Yield
#undef Yield
#endif

namespace Argon
{
	class Thread : private ThreadImpl
	{
	public:
		Thread();
		~Thread();

		// Allows the user to set an object to begin the new thread with prior to execution
		void SetTarget(ThreadTarget *NewTarget);

		// Begins thread execution
		void Start();

		void Start(ThreadTarget *NewTarget);

		// Stops thread execution
		void Stop();

		// Pauses the thread
		void Pause();

		// Resumes the thread
		void Resume();

		// Stops working on this thread for a moment
		static void Yield();
		// Stops working on this thread for a user defined amount of time
		static void Yield(unsigned long Milliseconds);

		// Returns true if the thread is running, otherwise false
		bool Running();

		// The function will end when the thread has finished execution
		void Join();

		// The function will end when the thread has finished execution or a user defined amount of time has passed
		// Returns true if thread is finished, false on timeout
		bool Join(unsigned long Milliseconds);
	};

	inline void Argon::Thread::SetTarget(ThreadTarget *NewTarget)
	{
		m_RunnableObject = NewTarget;
	}

	inline void Argon::Thread::Yield()
	{
		YieldImpl(0);
	}

	inline void Argon::Thread::Yield(unsigned long Milliseconds)
	{
		YieldImpl(Milliseconds);
	}
}
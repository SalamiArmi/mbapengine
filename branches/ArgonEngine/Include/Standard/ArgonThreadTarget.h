////////////////////////////////////////////////////////////////
//
//	ArgonThreadTarget.h :
//
//	Copyright ©2010 Argon. All rights reserved.
//	Removal of this copyright notice is not permitted.
//
///////////////////////////////////////////////////////////////

#pragma once

namespace Argon
{
	class ThreadTarget
	{
	public:
		ThreadTarget();
		virtual ~ThreadTarget();

		virtual void Method() = 0;
	};

#include "ArgonThreadTarget.inl"
}
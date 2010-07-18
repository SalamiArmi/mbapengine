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
}
#pragma once

#include "math.h"

namespace Argon
{
	template <typename T>
	class Vector2
	{
	public:
		Vector2()
		{
		}

		Vector2(const T _x, const T _y)
		: x(_x), y(_y)
		{
		}

		~Vector2()
		{
		}

		const T Dot(const Vector2 &rhs) const
		{
			return (x * rhs.x + y * rhs.y);
		}

		const T LengthSquared() const
		{
			return x * x + y * y;
		}

		const T Length() const
		{
			return sqrt(x * x + y * y);
		}

		const Vector2<T> Normalise() const
		{
			T LengthResult = 1 / Length();
			return Vector2(x * LengthResult, y * LengthResult);
		}

		T
			x,
			y;
	};
}

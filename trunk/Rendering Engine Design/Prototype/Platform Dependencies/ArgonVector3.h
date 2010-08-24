#pragma once

#include "math.h"

namespace Argon
{
	template <typename T>
	class Vector3
	{
	public:
		Vector3()
		{
		}

		Vector3(const T _x, const T _y, const T _z)
		: x(_x), y(_y), z(_z)
		{
		}

		~Vector3()
		{
		}

		const T Dot(const Vector3 &rhs) const
		{
			return (x * rhs.x + y * rhs.y + z * rhs.z);
		}

		const Vector3<T> Cross(const Vector3 &rhs)
		{
			return Vector3(
				y * rhs.z - z * rhs.y,
				z * rhs.x - x * rhs.z,
				x * rhs.y - y * rhs.x);
		}

		const T LengthSquared() const
		{
			return x * x + y * y + z * z;
		}

		const T Length() const
		{
			return sqrt(x * x + y * y + z * z);
		}

		const Vector3<T> Normalise() const
		{
			T LengthResult = 1 / Length();
			return Vector3(x * LengthResult, y * LengthResult, z * LengthResult);
		}

		T
			x,
			y,
			z;
	};
}

#pragma once

#include "math.h"
#include <Standard/ArgonStandard.h>

namespace Argon
{
	template<typename T>class Vector2T
	{
	public:
		///Vector2T(VOID)
		///
		///All default members to 0
		///
		///No Params:
		Vector2T( ) 
			: x(0.0f),
			y(0.0f)
		{
		}

		///Vector2T(VOID)
		///
		///Create a Vector2
		///
		///Param x: The X component to the vector3
		///Param y: The Y component to the vector3
		Vector2T(T x, T y)
			: x(x),
			y(y)
		{
		}

		bool operator< (const Vector2T& RHS) const
		{
			if (x == RHS.x)
			{
				return y == RHS.y
			}
			else
				return x < RHS.x;
		}

		bool operator==(const Vector2T& RHS) const
		{
			return (x == RHS.x && y == RHS.y);
		}

		bool operator!=(const Vector2T& RHS) const
		{
			return (x != RHS.x || y != RHS.y); 
		}

		Vector2T operator- (const Vector2T& RHS) const
		{
			return Vector2T(x - RHS.x, y - RHS.y);
		}

		Vector2T operator+ (const Vector2T& RHS) const
		{
			return Vector2T(x + RHS.x, y + RHS.y);
		}

		Vector2T        operator+=(const Vector2T& RHS)
		{
			x += RHS.x;
			y += RHS.y;
			z += RHS.z;

			return *this;
		}

		Vector2T operator* (const Vector2T& RHS) const
		{
			return Vector2T(x * RHS.x, y * RHS.y);
		}

		Vector2T operator*=(const Vector2T& RHS)
		{
			x *= RHS.x;
			y *= RHS.y;

			return *this;
		}

		Vector2T operator* (T Scale) const
		{
			return Vector2T(x * Scale, y * Scale);
		}

		Vector2T operator*=(T Scale)
		{
			x *= Scale;
			y *= Scale;

			return *this;
		}

		Vector2T operator- () const
		{
			return Vector2T(-x, -y);
		}

		Vector2T operator-=(const Vector2T& RHS)
		{
			x -= RHS.x;
			y -= RHS.y;

			return *this;
		}

		Vector2T operator/ (T Scalar) const
		{
			return Vector2T(x / Scalar, y / Scalar, z / Scalar);
		}

		Vector2T& operator/=(T scalar)
		{
			x /= Scalar;
			y /= Scalar;

			return *this;
		}
	
		T Distance(const Vector2T& RHS) const
		{
			return ((*this - RHS).Magnitude( ));    
		}

		T DistanceSquared(const Vector2T& RHS) const
		{
			return ((*this - RHS).MagnitudeSquared( )); 
		}

		T Dot(const Vector2T& RHS) const
		{
			return (x * RHS.x + y * RHS.y); 
		}

		T Magnitude() const
		{
			return T(sqrt(MagnitudeSquared()));
		}

		T MagnitudeSquared() const
		{
			return (x * x + y * y); 
		}

		void Normalize()
		{

		}
		void Scale(T Scale)
		{
			x *= Scale;
			y *= Scale;
		}

		T Angle(Vector2T& Compare)
		{
			T dotproduct = Dot(Compare);
			T lengtha = MagnitudeSquared();
			T lengthb = Compare.MagnitudeSquared();
			T result = acos(dotproduct / (lengtha * lengthb));

			if(dotproduct < 0.0f)
			{
				if(result > 0.0f)
					result += ArgonPI;
				else
					result -= ArgonPI;
			}
			return result;
		}

		T				x, y;
	};

#	if defined ArgonX64
		typedef Vector2T<double> Vector2;
#	else 
		typedef Vector2T<float> Vector2;
#	endif

}

#ifndef _ARGONVECTOR3_HEADER_
#define _ARGONVECTOR3_HEADER_

#include "Math.h"
#include <Standard/ArgonStandard.h>

namespace Argon
{
	template<typename T>class Vector3T
	{
	public:
		///VECTOR3T(VOID)
		///
		///All default members to 0
		///
		///No Params:
		Vector3T() 
			: x(0.0f),
			y(0.0f),
			z(0.0f)
		{
		}

		///VECTOR3T(VOID)
		///
		///Create a Vector3
		///
		///Param x: The X component to the vector3
		///Param y: The Y component to the vector3
		///Param z: The Z component to the vector3
		Vector3T(T x, T y, T z) 
			: x(x),
			y(y),
			z(z)
		{
		}

		bool operator< (const Vector3T& In) const
		{
			if (x == In.x)
			{
				if (y == In.y)
					return z < In.z;
				else 
					return y < In.y;
			}
			else
				return x < In.x;
		}

		bool operator==(const Vector3T& In) const
		{
			return (x == In.x && y == In.y && z == In.z);
		}

		bool operator!=(const Vector3T& In) const
		{
			return (x != In.x || y != In.y || z != In.z);    
		}

		Vector3T operator- (const Vector3T& In) const
		{
			return Vector3T(x - In.x, y - In.y, z - In.z);
		}

		Vector3T operator+ (const Vector3T& In) const
		{
			return Vector3T(x + In.x, y + In.y, z + In.z);
		}

		Vector3T operator+=(const Vector3T& In)
		{
			x += In.x;
			y += In.y;
			z += In.z;

			return *this;
		}

		Vector3T operator* (const Vector3T& In) const
		{
			return Vector3T(x * In.x, y * In.y, z * In.z);
		}

		Vector3T operator*=(const Vector3T& In)
		{
			x *= In.x;
			y *= In.y;
			z *= In.z;

			return *this;
		}

		Vector3T operator* (T Scale) const
		{
			return Vector3T(x * Scale, y * Scale, z * Scale);
		}

		Vector3T operator*=(T Scale)
		{
			x *= Scale;
			y *= Scale;
			z *= Scale;

			return *this;
		}

		Vector3T operator- () const
		{
			return Vector3T(-x, -y, -z);
		}

		Vector3T operator-=(const Vector3T& In)
		{
			// subtraction
			x -= In.x;
			y -= In.y;
			z -= In.z;

			return *this;
		}

		Vector3T operator/ (T Scalar) const
		{
			return Vector3T(x / Scalar, y / Scalar, z / Scalar);
		}

		Vector3T& operator/=(T scalar)
		{
			x /= Scalar;
			y /= Scalar;
			z /= Scalar;
			return *this;
		}

		void LinCombVector3(const Vector3T& Pos, const Vector3T& Dir, const double t)
		{
			for(int i = 0; i < 3; i++) 
				this->operator[](i) = Pos[i]+(T)(t)*Dir[i];
		}

		Vector3T Cross(const Vector3T& In) const
		{
			return Vector3T(y * In.z - z * In.y, z * In.x - x * In.z, x * In.y - y * In.x);
		}

		T Distance(const Vector3T& In) const
		{
			return ((*this - In).Magnitude( ));    
		}

		T DistanceSquared(const Vector3T& In) const
		{
			return ((*this - In).MagnitudeSquared( )); 
		}

		T Dot(const Vector3T& In) const
		{
			return (x * In.x + y * In.y + z * In.z); 
		}

		T Magnitude() const
		{
			return T(sqrt(MagnitudeSquared( )));
		}

		T MagnitudeSquared() const
		{
			return (x * x + y * y + z * z); 
		}

		void Normalize()
		{
			T fMagnitude = Magnitude();
			if (fMagnitude > FLT_EPSILON)
				Scale(1.0f / fMagnitude);
		}

		void Scale(T Scale)
		{
			x *= Scale;
			y *= Scale;
			z *= Scale;
		}


		T Angle(Vector3T& Compare)
		{
			T DotProduct = Dot(Compare);
			T Lengtha = MagnitudeSquared();
			T Lengthb = Compare.MagnitudeSquared();
			T Result = acos( Dotproduct / (Lengtha * Lengthb) );

			if( DotProduct < 0.0f )
			{
				if( Result > 0.0f )
					Result += ArgonPI;
				else
					Result -= ArgonPI;
			}
			return Result;
		}


		T x, y, z;
	};

	typedef Vector3T<float> Vector3;

}

#endif //_ARGONVECTOR3_HEADER_
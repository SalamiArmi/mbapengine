#ifndef _ARGONVECTOR4_HEADER_
#define _ARGONVECTOR4_HEADER_

#include "ArgonMatrix4.h"

namespace Argon
{
	template<typename T> class Vector4T
	{
	public:
		Vector4T()
			: w(0.0f),
			x(0.0f),
			y(0.0f),
			z(0.0f)
		{
		}

		Vector4T(T _w, T _x, T _y, T _z)
			: w(_w),
			x(_x),
			y(_y),
			z(_z)
		{
		}

		Vector4T(const float Array[4])
			: w(Array[0]),
			x(Array[1]),
			y(Array[2]),
			z(Array[3])
		{
		}
		
		float& operator[](int Index)
		{
			return *(&x + Index);
		}

		bool operator ==(const Vector4T& RHS)
		{
			return (w == RHS.w && x == RHS.x && y == RHS.y && z == RHS.z);
		}

		bool operator !=(const Vector4T& RHS)
		{
			return (w != RHS.w && x != RHS.x && y != RHS.y && z != RHS.z);
		}

		Vector4T operator *(const Vector4T RHS) const
		{
			return Vector4T(w * RHS.w, x * RHS.x, y * RHS.y, z * RHS.z)
		}

		Vector4T operator *(float RHS) const
		{
			return Vector4T(w * RHS, x * RHS, y * RHS, z * RHS)
		}

		Vector4T operator *=(const Matrix4& RHS)
		{
			const float _x = x * RHS[0] + y * RHS[4] + z * RHS[8]  + z * RHS[12];
			const float _y = x * RHS[1] + y * RHS[5] + z * RHS[9]  + z * RHS[13];
			const float _z = x * RHS[2] + y * RHS[6] + z * RHS[10] + z * RHS[14];
			const float _w = x * RHS[3] + y * RHS[7] + z * RHS[11] + z * RHS[15];

			w = _w;
			x = _x;
			y = _y;
			z = _z;
			return *this;
		}

		T	w;
		T	x;
		T	y;
		T	z;
	};

	typedef Vector4T<float> Vector4;

} //Namespace

#endif //_ARGONVECTOR4_HEADER_
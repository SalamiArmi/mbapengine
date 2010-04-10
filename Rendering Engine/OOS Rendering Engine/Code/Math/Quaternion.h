#ifndef _QUATERNION_HEADER
#define _QUATERNION_HEADER

#include <iostream>
#include <cmath>

#include "Vector3.h"
#include "Matrix4.h"

namespace OOS
{

	template<typename T>class QuaternionT
	{
	public:
		T x;
		T y;
		T z;
		T w;

		QuaternionT(const T &NewW, const T &NewX, const T &NewY, const T &NewZ)
		{    
			w = NewW;
			x = NewX;
			y = NewY;
			z = NewZ;
		}

		int IsIdentity() const
		{
			return (x == 0.0f && y == 0.0f && z == 0.0f && w==1.0f);
		}


		// Set Quat from axis-angle
		void SetAxis(T degrees, T NewX, T NewY, T NewZ)
		{
			T HalfAngle = degrees * TO_HALF_RAD; // Get half angle in radians from angle in degrees
			T sinA = (T)sin( HalfAngle ) ;
			w = (T)cos(HalfAngle);
			x = NewX * sinA;
			y = NewY * sinA;
			z = NewZ * sinA;
		}


		QuaternionT operator*(const QuaternionT &NewQuaternion)
		{
			return QuaternionT(
				w * NewQuaternion.w - x * NewQuaternion.x - y * NewQuaternion.y - z * NewQuaternion.z,
				w * NewQuaternion.x + x * NewQuaternion.w + y * NewQuaternion.z - z * NewQuaternion.y,
				w * NewQuaternion.y + y * NewQuaternion.w + z * NewQuaternion.x - x * NewQuaternion.z,
				w * NewQuaternion.z + z * NewQuaternion.w + x * NewQuaternion.y - y * NewQuaternion.x);      
		}

		QuaternionT operator+(const QuaternionT &NewQuaternion) const
		{
			return QuaternionT(
				w + NewQuaternion.w, 
				x + NewQuaternion.x,
				y + NewQuaternion.y, 
				z + NewQuaternion.z);
		}

		QuaternionT operator-(const QuaternionT &NewQuaternion) const
		{
			return QuaternionT(w - NewQuaternion.w,
				x - NewQuaternion.x, 
				y - NewQuaternion.y, 
				z - NewQuaternion.z);
		}

		T Magnitude() const
		{
			return sqrt(w * w + x * x + y * y + z * z);
		}

		void Normalise()
		{
			T NewMagnitude = Magnitude();
			w /= NewMagnitude;
			x /= NewMagnitude;
			y /= NewMagnitude;
			z /= NewMagnitude;
		}

		T Dot(const QuaternionT &NewQuaternion)const //Made a dot and a magnitude for the Slerp
		{
			return x * NewQuaternion.x + y * NewQuaternion.y + z * NewQuaternion.z + w * NewQuaternion.w;
		}

		// ------------------------------------------------------------------------//
		// Creates a value for this QuaternionT from spherical linear interpolation //
		// K is the interpolation value from 0 to 1								   //
		// ------------------------------------------------------------------------//

		inline void Slerp(const QuaternionT &NewQuaternion1, const QuaternionT &NewQuaternion2, T K)
		{
			T w1, w2;

			T cosTheta = NewQuaternion1.Dot(NewQuaternion2);
			T theta    = (T)acos(cosTheta);
			T sinTheta = (T)sin(theta);

			if(sinTheta > 0.001f)
			{
				w1 = T( sin( (1.0f-K)*theta ) / sinTheta);
				w2 = T( sin(K*theta) / sinTheta);
			}
			else 
			{
				w1 = 1.0f - K;
				w2 = K;
			}

			//*this = NewQuaternion1*w1 + NewQuaternion2*w2;
		}

		inline Matrix4 ImportingQuaternionTOMatrix4x4(const QuaternionT &NewQuaternion)
		{
			T xx = NewQuaternion.x * NewQuaternion.x;
			T xy = NewQuaternion.x * NewQuaternion.y;
			T xz = NewQuaternion.x * NewQuaternion.z;
			T xw = NewQuaternion.x * NewQuaternion.w;
			T yy = NewQuaternion.y * NewQuaternion.y;
			T yz = NewQuaternion.y * NewQuaternion.z;
			T yw = NewQuaternion.y * NewQuaternion.w;
			T zz = NewQuaternion.z * NewQuaternion.z;
			T zw = NewQuaternion.z * NewQuaternion.w;

			return Matrix4(
				1 - 2 * ( yy + zz ), 2 * ( xy - zw ),
				2 * ( xz + yw ), 0, 2 * ( xy + zw ),
				1 - 2 * ( xx + zz ), 2 * ( yz - xw ),
				0,  2 * ( xz - yw ), 2 * ( yz + xw ),
				1 - 2 * ( xx + yy ), 0, 0, 0, 0, 1);
		}

		inline Matrix3 ConvertQuaternionToMatrix3(const QuaternionT &NewQuaternion)
		{
			T Qxx = NewQuaternion.x * NewQuaternion.x;
			T Qxy = NewQuaternion.x * NewQuaternion.y;
			T Qxz = NewQuaternion.x * NewQuaternion.z;
			T Qxw = NewQuaternion.x * NewQuaternion.w; //Make the values Q == QuaternionT
			T Qyy = NewQuaternion.y * NewQuaternion.y; //   Next 2 Letters == The X, Y, Z, W      
			T Qyz = NewQuaternion.y * NewQuaternion.z;
			T Qyw = NewQuaternion.y * NewQuaternion.w;
			T Qzz = NewQuaternion.z * NewQuaternion.z;
			T Qzw = NewQuaternion.z * NewQuaternion.w;

			return Matrix3(1 - 2 * ( Qyy + Qzz ),     2 * ( Qxy - Qzw ),     2 * ( Qxz + Qyw ),
				2 * ( Qxy + Qzw ), 1 - 2 * ( Qxx + Qzz ),     2 * ( Qyz - Qxw ),
				2 * ( Qxz - Qyw ),      2 * ( Qyz + Qxw ), 1 - 2 * ( Qxx + Qyy ));
		}
	};

	typedef QuaternionT<float> Quaternion;
}

#endif //_QUATERNION_HEADER
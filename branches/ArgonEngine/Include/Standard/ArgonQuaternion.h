#ifndef ZARANTAS_QUATERNION_HEADER
#define ZARANTAS_QUATERNION_HEADER

#include <iostream>
#include <cmath>

#include <Standard/ArgonMatrix3.h>
#include <Standard/ArgonVector3.h>
#include <Standard/ArgonMatrix4.h>

const float TO_HALF_RAD = 3.14159265f / 360.0f;

namespace Argon
{
	class Quaternion
	{
	public:
		float x;
		float y;
		float z;
		float w;

		Quaternion(const float &W, const float &X, const float &Y, const float &Z)
		{    
			w = W;
			x = X;
			y = Y;
			z = Z;
		}

		int IsIdentity() const
		{
			return (x == 0.0f && y == 0.0f && z == 0.0f && w == 1.0f);
		}


	// Set Quat from axis-angle
	void SetAxis(float degrees, float X, float Y, float Z)
	{
		float HalfAngle = degrees * TO_HALF_RAD; // Get half angle in radians from angle in degrees
		float sinA = (float)sin(HalfAngle) ;
		w = (float)cos(HalfAngle);
		x = X * sinA;
		y = Y * sinA;
		z = Z * sinA;
	}


		Quaternion operator*(const Quaternion &Q)
		{
			return Quaternion(
				w * Q.w - x * Q.x - y * Q.y - z * Q.z,
				w * Q.x + x * Q.w + y * Q.z - z * Q.y,
				w * Q.y + y * Q.w + z * Q.x - x * Q.z,
				w * Q.z + z * Q.w + x * Q.y - y * Q.x);      
		}

		Quaternion operator+(const Quaternion &Q) const
		{
			return Quaternion(w + Q.w, x + Q.x,	y + Q.y, z + Q.z);
		}

		Quaternion operator-(const Quaternion &Q) const
		{
			return Quaternion(w - Q.w,	x - Q.x, y - Q.y, z - Q.z);
		}

		float Magnitude() const
		{
			return sqrt(w * w + x * x + y * y + z * z);
		}

		void Normalise()
		{
			float Mag = Magnitude();
			w /= Mag;
			x /= Mag;
			y /= Mag;
			z /= Mag;
		}

		float Dot(const Quaternion &Q)const //Made a dot and a magnitude for the Slerp
		{
			return x * Q.x + y * Q.y + z * Q.z + w * Q.w;
		}

		Matrix4 ImportingQuaternionMatrix4(const Quaternion &q)
		{
			float xx = q.x * q.x;
			float xy = q.x * q.y;
			float xz = q.x * q.z;
			float xw = q.x * q.w;
			float yy = q.y * q.y;
			float yz = q.y * q.z;
			float yw = q.y * q.w;
			float zz = q.z * q.z;
			float zw = q.z * q.w;

			return Matrix4(1 - 2 * (yy + zz), 2 * (xy - zw),
				2 * (xz + yw), 0, 2 * (xy + zw),
				1 - 2 * (xx + zz), 2 * (yz - xw),
				0,  2 * (xz - yw), 2 * (yz + xw),
				1 - 2 * (xx + yy), 0, 0, 0, 0, 1);
		}

		Matrix3 ConvertQuaternionMatrix3(const Quaternion &q)
		{
			float Qxx = q.x * q.x;
			float Qxy = q.x * q.y;
			float Qxz = q.x * q.z;
			float Qxw = q.x * q.w; //Make the values Q == Quaternion
			float Qyy = q.y * q.y; //   Next 2 Letters == The X, Y, Z, W      
			float Qyz = q.y * q.z;
			float Qyw = q.y * q.w;
			float Qzz = q.z * q.z;
			float Qzw = q.z * q.w;

			return Matrix3(1 - 2 * ( Qyy + Qzz ),     2 * ( Qxy - Qzw ),     2 * ( Qxz + Qyw ),
				2 * ( Qxy + Qzw ), 1 - 2 * ( Qxx + Qzz ),     2 * ( Qyz - Qxw ),
				2 * ( Qxz - Qyw ),      2 * ( Qyz + Qxw ), 1 - 2 * ( Qxx + Qyy ));
		}
	};
}

#endif 
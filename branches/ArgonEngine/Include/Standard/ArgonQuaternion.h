#ifndef _ARGONQUATERNION_HEADER
#define _ARGONQUATERNION_HEADER

#include <Standard/ArgonBase.h>
#include <Standard/ArgonVector3.h>
#include <Standard/ArgonMatrix3.h>
#include <Standard/ArgonMatrix4.h>

namespace Argon
{
	template<typename T> class QuaternionT
	{
	public:
		float	x;
		float	y;
		float	z;
		float	w;

		QuaternionT() 
		{
		}

		explicit QuaternionT(const Vector3& v)
		{
			x = v.x;
			y = v.y;
			z = v.z;
			w = 0.0F;
		}

		QuaternionT(const Vector3& v, T s)
		{
			x = v.x;
			y = v.y;
			z = v.z;
			w = s;
		}

		explicit QuaternionT(T s)
		{
			w = s;
			x = y = z = 0.0F;
		}

		QuaternionT(T a, T b, T c, T s)
		{
			x = a;
			y = b;
			z = c;
			w = s;
		}

		QuaternionT& Set(const Vector3& v, T s)
		{
			x = v.x;
			y = v.y;
			z = v.z;
			w = s;
			return (*this);
		}

		QuaternionT& Set(T a, T b, T c, T s)
		{
			x = a;
			y = b;
			z = c;
			w = s;
			return (*this);
		}

		float& operator [](long k)
		{
			return ((&x)[k]);
		}

		const float& operator [](long k) const
		{
			return ((&x)[k]);
		}

		Vector3& GetVector3()
		{
			return (*reinterpret_cast<Vector3 *>(this));
		}

		const Vector3& GetVector3() const
		{
			return (*reinterpret_cast<const Vector3 *>(this));
		}

		QuaternionT& operator =(const Vector3& v)
		{
			x = v.x;
			y = v.y;
			z = v.z;
			w = 0.0F;
			return (*this);
		}

		QuaternionT& operator =(T s)
		{
			w = s;
			x = y = z = 0.0F;
			return (*this);
		}

		QuaternionT& operator +=(const QuaternionT& q)
		{
			x += q.x;
			y += q.y;
			z += q.z;
			w += q.w;
			return (*this);
		}

		QuaternionT& operator +=(const Vector3& v)
		{
			x += v.x;
			y += v.y;
			z += v.z;
			return (*this);
		}

		QuaternionT& operator +=(float s)
		{
			w += s;
			return (*this);
		}

		QuaternionT& operator -=(const QuaternionT& q)
		{
			x -= q.x;
			y -= q.y;
			z -= q.z;
			w -= q.w;
			return (*this);
		}

		QuaternionT& operator -=(const Vector3& v)
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;
			return (*this);
		}

		QuaternionT& operator -=(T s)
		{
			w -= s;
			return (*this);
		}

		QuaternionT& operator *=(const QuaternionT& q)
		{
			float a = w * q.x + x * q.w + y * q.z - z * q.y;
			float b = w * q.y - x * q.z + y * q.w + z * q.x;
			float c = w * q.z + x * q.y - y * q.x + z * q.w;

			w = w * q.w - x * q.x - y * q.y - z * q.z;
			x = a;
			y = b;
			z = c;

			return (*this);
		}

		QuaternionT& operator *=(const Vector3& v)
		{
			float a = w * v.x + y * v.z - z * v.y;
			float b = w * v.y - x * v.z + z * v.x;
			float c = w * v.z + x * v.y - y * v.x;

			w = -x * v.x - y * v.y - z * v.z;
			x = a;
			y = b;
			z = c;

			return (*this);
		}

		QuaternionT& operator *=(T s)
		{
			x *= s;
			y *= s;
			z *= s;
			w *= s;
			return (*this);
		}

		QuaternionT& operator /=(const QuaternionT& q)
		{
			return (*this *= Inverse(q));
		}

		QuaternionT& operator /=(const Vector3& v)
		{
			return (*this *= -v / SquaredMag(v));
		}

		QuaternionT& operator /=(T s)
		{
			float f = 1.0F / s;
			x *= f;
			y *= f;
			z *= f;
			w *= f;
			return (*this);
		}

		QuaternionT& Normalize()
		{
			return (*this *= InverseSqrt(x * x + y * y + z * z + w * w));
		}

		Vector3 GetDirectionX() const
		{
			return (Vector3(1.0F - 2.0F * (y * y + z * z), 2.0F * (x * y + w * z), 2.0F * (x * z - w * y)));
		}

		Vector3 GetDirectionY() const
		{
			return (Vector3(2.0F * (x * y - w * z), 1.0F - 2.0F * (x * x + z * z), 2.0F * (y * z + w * x)));
		}

		Vector3 GetDirectionZ() const
		{
			return (Vector3(2.0F * (x * z + w * y), 2.0F * (y * z - w * x), 1.0F - 2.0F * (x * x + y * y)));
		}

		QuaternionT& SetRotationAboutX(T angle)
		{
			angle *= 0.5F;
			w = (float) Cos(angle);
			x = (float) Sin(angle);
			y = z = 0.0F;
			return (*this);
		}

		QuaternionT& SetRotationAboutY(T angle)
		{
			angle *= 0.5F;
			w = (float) Cos(angle);
			y = (float) Sin(angle);
			x = z = 0.0F;
			return (*this);
		}

		QuaternionT& SetRotationAboutZ(T angle)
		{
			angle *= 0.5F;
			w = (float) Cos(angle);
			z = (float) Sin(angle);
			x = y = 0.0F;
			return (*this);
		}

		QuaternionT& SetRotationAboutAxis(T angle, const Vector3& axis)
		{
			angle *= 0.5F;
			float s = Sin(angle) * InverseMag(axis);

			w = Cos(angle);
			x = s * axis.x;
			y = s * axis.y;
			z = s * axis.z;

			return (*this);
		}

		Matrix3 GetRotationMatrix() const
		{
			return (Matrix3(1.0F - 2.0F * (y * y + z * z), 2.0F * (x * y - w * z), 2.0F * (x * z + w * y),
				2.0F * (x * y + w * z), 1.0F - 2.0F * (x * x + z * z), 2.0F * (y * z - w * x),
				2.0F * (x * z - w * y), 2.0F * (y * z + w * x), 1.0F - 2.0F * (x * x + y * y)));
		}

		Matrix3 GetRotationScaleMatrix() const
		{
			float s2 = SquaredMag(*this);
			float r = InverseSqrt(s2);
			float s = s2 * r;
			float t = s * 2.0F;

			float a = w * r;
			float b = x * r;
			float c = y * r;
			float d = z * r;

			return (Matrix3(s - t * (c * c + d * d), t * (b * c - a * d), t * (b * d + a * c),
				t * (b * c + a * d), s - t * (b * b + d * d), t * (c * d - a * b),
				t * (b * d - a * c), t * (c * d + a * b), s - t * (b * b + c * c)));
		}

		QuaternionT& SetRotationMatrix(Matrix3& m)
		{
			float m00 = m(0,0);
			float m11 = m(1,1);
			float m22 = m(2,2);
			float trace = m00 + m11 + m22;

			if (trace > 0.0F)
			{
				w = 0.5F * Sqrt(trace + 1.0F);
				float f = 0.25F / w;

				x = (m(2,1) - m(1,2)) * f;
				y = (m(0,2) - m(2,0)) * f;
				z = (m(1,0) - m(0,1)) * f;
			}
			else if ((m00 > m11) && (m00 > m22))
			{
				x = 0.5F * Sqrt(m00 - m11 - m22 + 1.0F);
				float f = 0.25F / x;

				y = (m(0,1) + m(1,0)) * f;
				z = (m(0,2) + m(2,0)) * f;
				w = (m(2,1) - m(1,2)) * f;
			}
			else if (m11 > m22)
			{
				y = 0.5F * Sqrt(m11 - m00 - m22 + 1.0F);
				float f = 0.25F / y;

				x = (m(0,1) + m(1,0)) * f;
				z = (m(1,2) + m(2,1)) * f; 
				w = (m(0,2) - m(2,0)) * f;
			} 
			else 
			{ 
				z = 0.5F * Sqrt(m22 - m00 - m11 + 1.0F);
				float f = 0.25F / z; 

				x = (m(0,2) + m(2,0)) * f;
				y = (m(1,2) + m(2,1)) * f; 
				w = (m(1,0) - m(0,1)) * f; 
			} 

			return (*this);
		}

		QuaternionT& SetRotationMatrix(Transform4& m)
		{
			float m00 = m(0,0);
			float m11 = m(1,1);
			float m22 = m(2,2);
			float trace = m00 + m11 + m22;

			if (trace > 0.0F)
			{
				w = 0.5F * Sqrt(trace + 1.0F);
				float f = 0.25F / w;

				x = (m(2,1) - m(1,2)) * f;
				y = (m(0,2) - m(2,0)) * f;
				z = (m(1,0) - m(0,1)) * f;
			}
			else if ((m00 > m11) && (m00 > m22))
			{
				x = 0.5F * Sqrt(m00 - m11 - m22 + 1.0F);
				float f = 0.25F / x;

				y = (m(0,1) + m(1,0)) * f;
				z = (m(0,2) + m(2,0)) * f;
				w = (m(2,1) - m(1,2)) * f;
			}
			else if (m11 > m22)
			{
				y = 0.5F * Sqrt(m11 - m00 - m22 + 1.0F);
				float f = 0.25F / y;

				x = (m(0,1) + m(1,0)) * f;
				z = (m(1,2) + m(2,1)) * f;
				w = (m(0,2) - m(2,0)) * f;
			}
			else
			{
				z = 0.5F * Sqrt(m22 - m00 - m11 + 1.0F);
				float f = 0.25F / z;

				x = (m(0,2) + m(2,0)) * f;
				y = (m(1,2) + m(2,1)) * f;
				w = (m(1,0) - m(0,1)) * f;
			}

			return (*this);
		}

		T Dot(const QuaternionT& q1, const QuaternionT& q2)
		{
			return (q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w);
		}

		T Magnitude(const QuaternionT& q)
		{
			return (Sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w));
		}

		T SquaredMag(const QuaternionT& q)
		{
			return (q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
		}

		T Conjugate(const QuaternionT& q)
		{
			return (Quaternion(-q.x, -q.y, -q.z, q.w));
		}

		T Inverse(const QuaternionT& q)
		{
			return (Conjugate(q) / SquaredMag(q));
		}

	}; //Class

	typedef QuaternionT<float> Quaternion;

	inline Quaternion operator -(const Quaternion& q)
	{
		return (Quaternion(-q.x, -q.y, -q.z, -q.w));
	}
	
	inline Quaternion operator +(const Quaternion& q1, const Quaternion& q2)
	{
		return (Quaternion(q1.x + q2.x, q1.y + q2.y, q1.z + q2.z, q1.w + q2.w));
	}
	
	inline Quaternion operator +(const Quaternion& q, const Vector3& v)
	{
		return (Quaternion(q.x + v.x, q.y + v.y, q.z + v.z, q.w));
	}
	
	inline Quaternion operator +(const Vector3& v, const Quaternion& q)
	{
		return (Quaternion(v.x + q.x, v.y + q.y, v.z + q.z, q.w));
	}
	
	inline Quaternion operator +(const Quaternion& q, float s)
	{
		return (Quaternion(q.x, q.y, q.z, q.w + s));
	}
	
	inline Quaternion operator +(float s, const Quaternion& q)
	{
		return (Quaternion(q.x, q.y, q.z, s + q.w));
	}
	
	inline Quaternion operator -(const Quaternion& q1, const Quaternion& q2)
	{
		return (Quaternion(q1.x - q2.x, q1.y - q2.y, q1.z - q2.z, q1.w - q2.w));
	}
	
	inline Quaternion operator -(const Quaternion& q, const Vector3& v)
	{
		return (Quaternion(q.x - v.x, q.y - v.y, q.z - v.z, q.w));
	}
	
	inline Quaternion operator -(const Vector3& v, const Quaternion& q)
	{
		return (Quaternion(v.x - q.x, v.y - q.y, v.z - q.z, -q.w));
	}
	
	inline Quaternion operator -(const Quaternion& q, float s)
	{
		return (Quaternion(q.x, q.y, q.z, q.w - s));
	}
	
	inline Quaternion operator -(float s, const Quaternion& q)
	{
		return (Quaternion(-q.x, -q.y, -q.z, s - q.w));
	}
	
	inline Quaternion operator *(const Quaternion& q, float s)
	{
		return (Quaternion(q.x * s, q.y * s, q.z * s, q.w * s));
	}
	
	inline Quaternion operator *(float s, const Quaternion& q)
	{
		return (Quaternion(s * q.x, s * q.y, s * q.z, s * q.w));
	}
	
	inline Quaternion operator /(const Quaternion& q, float s)
	{
		float f = 1.0F / s;
		return (Quaternion(q.x * f, q.y * f, q.z * f, q.w * f));
	}
	
	inline bool operator ==(const Quaternion& q1, const Quaternion& q2)
	{
		return ((q1.x == q2.x) && (q1.y == q2.y) && (q1.z == q2.z) && (q1.w == q2.w));
	}
	
	inline bool operator ==(const Quaternion& q, const Vector3& v)
	{
		return ((q.x == v.x) && (q.y == v.y) && (q.z == v.z) && (q.w == 0.0F));
	}
	
	inline bool operator ==(const Vector3& v, const Quaternion& q)
	{
		return ((q.x == v.x) && (q.y == v.y) && (q.z == v.z) && (q.w == 0.0F));
	}
	
	inline bool operator ==(const Quaternion& q, float s)
	{
		return ((q.w == s) && (q.x == 0.0F) && (q.y == 0.0F) && (q.z == 0.0F));
	}
	
	inline bool operator ==(float s, const Quaternion& q)
	{
		return ((q.w == s) && (q.x == 0.0F) && (q.y == 0.0F) && (q.z == 0.0F));
	}
	
	inline bool operator !=(const Quaternion& q1, const Quaternion& q2)
	{
		return ((q1.x != q2.x) || (q1.y != q2.y) || (q1.z != q2.z) || (q1.w != q2.w));
	}
	
	inline bool operator !=(const Quaternion& q, const Vector3& v)
	{
		return ((q.x != v.x) || (q.y != v.y) || (q.z != v.z) || (q.w != 0.0F));
	}
	
	inline bool operator !=(const Vector3& v, const Quaternion& q)
	{
		return ((q.x != v.x) || (q.y != v.y) || (q.z != v.z) || (q.w != 0.0F));
	}
	
	inline bool operator !=(const Quaternion& q, float s)
	{
		return ((q.w != s) || (q.x != 0.0F) || (q.y != 0.0F) || (q.z != 0.0F));
	}
	
	inline bool operator !=(float s, const Quaternion& q)
	{
		return ((q.w != s) || (q.x != 0.0F) || (q.y != 0.0F) || (q.z != 0.0F));
	}

} //Namespace

#endif //_ARGONQUATERNION_HEADER
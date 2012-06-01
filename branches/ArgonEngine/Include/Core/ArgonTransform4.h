#ifndef _ARGONTRANSFORM4_HEADER_
#define _ARGONTRANSFORM4_HEADER_

#include <Standard/ArgonBase.h>
#include <Standard/ArgonVector2.h>
#include <Standard/ArgonVector3.h>
#include <Standard/ArgonVector4.h>
#include <Standard/ArgonMatrix4.h>
#include <Standard/ArgonMatrix3.h>

namespace Argon
{
	class Transform4 : public Matrix4
	{
	public:
		Transform4()
		{
		}

		Transform4(const Matrix3& m)
		{
			m_RowCol[0][0] = m.m_RowCol[0][0];
			m_RowCol[0][1] = m.m_RowCol[0][1];
			m_RowCol[0][2] = m.m_RowCol[0][2];
			m_RowCol[1][0] = m.m_RowCol[1][0];
			m_RowCol[1][1] = m.m_RowCol[1][1];
			m_RowCol[1][2] = m.m_RowCol[1][2];
			m_RowCol[2][0] = m.m_RowCol[2][0];
			m_RowCol[2][1] = m.m_RowCol[2][1];
			m_RowCol[2][2] = m.m_RowCol[2][2];

			m_RowCol[0][3] = m_RowCol[1][3] = m_RowCol[2][3] = m_RowCol[3][0] = m_RowCol[3][1] = m_RowCol[3][2] = 0.0F;
			m_RowCol[3][3] = 1.0F;
		}

		Transform4(const Matrix3& m, const Vector3& v)
		{
			m_RowCol[0][0] = m.m_RowCol[0][0];
			m_RowCol[0][1] = m.m_RowCol[0][1];
			m_RowCol[0][2] = m.m_RowCol[0][2];
			m_RowCol[1][0] = m.m_RowCol[1][0];
			m_RowCol[1][1] = m.m_RowCol[1][1];
			m_RowCol[1][2] = m.m_RowCol[1][2];
			m_RowCol[2][0] = m.m_RowCol[2][0];
			m_RowCol[2][1] = m.m_RowCol[2][1];
			m_RowCol[2][2] = m.m_RowCol[2][2];
			m_RowCol[3][0] = v.x;
			m_RowCol[3][1] = v.y;
			m_RowCol[3][2] = v.z;

			m_RowCol[0][3] = m_RowCol[1][3] = m_RowCol[2][3] = 0.0F;
			m_RowCol[3][3] = 1.0F;
		}

		Transform4(const Vector3& c1, const Vector3& c2, const Vector3& c3, const Vector3& c4)
		{
			m_RowCol[0][0] = c1.x;
			m_RowCol[0][1] = c1.y;
			m_RowCol[0][2] = c1.z;
			m_RowCol[1][0] = c2.x;
			m_RowCol[1][1] = c2.y;
			m_RowCol[1][2] = c2.z;
			m_RowCol[2][0] = c3.x;
			m_RowCol[2][1] = c3.y;
			m_RowCol[2][2] = c3.z;
			m_RowCol[3][0] = c4.x;
			m_RowCol[3][1] = c4.y;
			m_RowCol[3][2] = c4.z;

			m_RowCol[0][3] = m_RowCol[1][3] = m_RowCol[2][3] = 0.0F;
			m_RowCol[3][3] = 1.0F;
		}

		Transform4(float n00, float n01, float n02, float n03, float n10, float n11, float n12, float n13, float n20, float n21, float n22, float n23)
		{
			m_RowCol[0][0] = n00;
			m_RowCol[1][0] = n01;
			m_RowCol[2][0] = n02;
			m_RowCol[3][0] = n03;
			m_RowCol[0][1] = n10;
			m_RowCol[1][1] = n11;
			m_RowCol[2][1] = n12;
			m_RowCol[3][1] = n13;
			m_RowCol[0][2] = n20;
			m_RowCol[1][2] = n21;
			m_RowCol[2][2] = n22;
			m_RowCol[3][2] = n23;

			m_RowCol[0][3] = m_RowCol[1][3] = m_RowCol[2][3] = 0.0F;
			m_RowCol[3][3] = 1.0F;
		}

		Transform4& Set(const Matrix4& m, const Vector3& v)
		{
			m_RowCol[0][0] = m.m_RowCol[0][0];
			m_RowCol[0][1] = m.m_RowCol[0][1];
			m_RowCol[0][2] = m.m_RowCol[0][2];
			m_RowCol[1][0] = m.m_RowCol[1][0];
			m_RowCol[1][1] = m.m_RowCol[1][1];
			m_RowCol[1][2] = m.m_RowCol[1][2];
			m_RowCol[2][0] = m.m_RowCol[2][0];
			m_RowCol[2][1] = m.m_RowCol[2][1];
			m_RowCol[2][2] = m.m_RowCol[2][2];
			m_RowCol[3][0] = v.x;
			m_RowCol[3][1] = v.y;
			m_RowCol[3][2] = v.z;

			m_RowCol[0][3] = m_RowCol[1][3] = m_RowCol[2][3] = 0.0F;
			m_RowCol[3][3] = 1.0F;

			return (*this);
		}

		Transform4& Set(const Vector3& c1, const Vector3& c2, const Vector3& c3, const Vector3& c4)
		{
			m_RowCol[0][0] = c1.x;
			m_RowCol[0][1] = c1.y;
			m_RowCol[0][2] = c1.z;
			m_RowCol[1][0] = c2.x;
			m_RowCol[1][1] = c2.y;
			m_RowCol[1][2] = c2.z;
			m_RowCol[2][0] = c3.x;
			m_RowCol[2][1] = c3.y;
			m_RowCol[2][2] = c3.z;
			m_RowCol[3][0] = c4.x;
			m_RowCol[3][1] = c4.y;
			m_RowCol[3][2] = c4.z;

			m_RowCol[0][3] = m_RowCol[1][3] = m_RowCol[2][3] = 0.0F;
			m_RowCol[3][3] = 1.0F;

			return (*this);
		}


		Transform4& Set(float n00, float n01, float n02, float n03, float n10, float n11, float n12, float n13, float n20, float n21, float n22, float n23)
		{
			m_RowCol[0][0] = n00;
			m_RowCol[1][0] = n01;
			m_RowCol[2][0] = n02;
			m_RowCol[3][0] = n03;
			m_RowCol[0][1] = n10;
			m_RowCol[1][1] = n11;
			m_RowCol[2][1] = n12;
			m_RowCol[3][1] = n13;
			m_RowCol[0][2] = n20;
			m_RowCol[1][2] = n21;
			m_RowCol[2][2] = n22;
			m_RowCol[3][2] = n23;

			m_RowCol[0][3] = m_RowCol[1][3] = m_RowCol[2][3] = 0.0F;
			m_RowCol[3][3] = 1.0F;

			return (*this);
		}

		const Vector3& GetTranslation() const
		{
			return (*reinterpret_cast<const Vector3 *>(&m_RowCol[3][0]));
		}

		Transform4& SetTranslation(const Vector3& p)
		{
			m_RowCol[3][0] = p.x;
			m_RowCol[3][1] = p.y;
			m_RowCol[3][2] = p.z;
			return (*this);
		}

		void Pitch(float Radians)
		{
			float Cosine = cosf(Radians);
			float Sine = sinf(Radians);

			Transform4 Temp;
			Temp.m_RowCol[1][1] = Cosine;
			Temp.m_RowCol[1][2] = Sine;
			Temp.m_RowCol[2][1] = -Sine;
			Temp.m_RowCol[2][2] = Cosine;

			(*this) = Temp * (*this);
		}

		void Yaw(float Radians)
		{
			float Cosine = cosf(Radians);
			float Sine = sinf(Radians);

			Transform4 Temp;
			Temp.m_RowCol[0][0] = Cosine;
			Temp.m_RowCol[0][2] = -Sine;
			Temp.m_RowCol[2][0] = Sine;
			Temp.m_RowCol[2][2] = Cosine;

			(*this) = Temp * (*this);
		}

		void Roll(float Radians)
		{
			float Cosine = cosf(Radians);
			float Sine = sinf(Radians);

			Transform4 Temp;
			Temp.m_RowCol[0][0] = Cosine;
			Temp.m_RowCol[1][0] = -Sine;
			Temp.m_RowCol[0][1] = Sine;
			Temp.m_RowCol[1][1] = Cosine;

			*this = Temp * *this;
		}

		void RotateArbitrary(const Vector3& Axis, float Radians)
		{
			float s = sinf(Radians);
			float c = cosf(Radians);
			float t = 1.0f - c;

			Vector3 NormalizedAxis(Axis);
			NormalizedAxis.Normalize( );
			const float& x = NormalizedAxis.x;
			const float& y = NormalizedAxis.y;
			const float& z = NormalizedAxis.z;

			Transform4 Temp;
			Temp.m_RowCol[0][0] = t * x * x + c;
			Temp.m_RowCol[0][1] = t * x * y + s * z;
			Temp.m_RowCol[0][2] = t * x * z - s * y;
			Temp.m_RowCol[1][0] = t * x * y - s * z;
			Temp.m_RowCol[1][1] = t * y * y + c;
			Temp.m_RowCol[1][2] = t * y * z + s * x;
			Temp.m_RowCol[2][0] = t * x * z + s * y;
			Temp.m_RowCol[2][1] = t * y * z - s * x;
			Temp.m_RowCol[2][2] = t * z * z + c;

			(*this) = Temp * (*this);
		}

		Transform4& operator *=(const Transform4& m)
		{
			float x = m_RowCol[0][0];
			float y = m_RowCol[1][0];
			float z = m_RowCol[2][0];
			m_RowCol[0][0] = x * m.m_RowCol[0][0] + y * m.m_RowCol[0][1] + z * m.m_RowCol[0][2];
			m_RowCol[1][0] = x * m.m_RowCol[1][0] + y * m.m_RowCol[1][1] + z * m.m_RowCol[1][2];
			m_RowCol[2][0] = x * m.m_RowCol[2][0] + y * m.m_RowCol[2][1] + z * m.m_RowCol[2][2];
			m_RowCol[3][0] = x * m.m_RowCol[3][0] + y * m.m_RowCol[3][1] + z * m.m_RowCol[3][2] + m_RowCol[3][0];

			x = m_RowCol[0][1];
			y = m_RowCol[1][1];
			z = m_RowCol[2][1];
			m_RowCol[0][1] = x * m.m_RowCol[0][0] + y * m.m_RowCol[0][1] + z * m.m_RowCol[0][2];
			m_RowCol[1][1] = x * m.m_RowCol[1][0] + y * m.m_RowCol[1][1] + z * m.m_RowCol[1][2];
			m_RowCol[2][1] = x * m.m_RowCol[2][0] + y * m.m_RowCol[2][1] + z * m.m_RowCol[2][2];
			m_RowCol[3][1] = x * m.m_RowCol[3][0] + y * m.m_RowCol[3][1] + z * m.m_RowCol[3][2] + m_RowCol[3][1];

			x = m_RowCol[0][2];
			y = m_RowCol[1][2];
			z = m_RowCol[2][2];
			m_RowCol[0][2] = x * m.m_RowCol[0][0] + y * m.m_RowCol[0][1] + z * m.m_RowCol[0][2];
			m_RowCol[1][2] = x * m.m_RowCol[1][0] + y * m.m_RowCol[1][1] + z * m.m_RowCol[1][2];
			m_RowCol[2][2] = x * m.m_RowCol[2][0] + y * m.m_RowCol[2][1] + z * m.m_RowCol[2][2];
			m_RowCol[3][2] = x * m.m_RowCol[3][0] + y * m.m_RowCol[3][1] + z * m.m_RowCol[3][2] + m_RowCol[3][2];

			return (*this);
		}

		Transform4& operator *=(const Matrix3& m)
		{
			float x = m_RowCol[0][0];
			float y = m_RowCol[1][0];
			float z = m_RowCol[2][0];
			m_RowCol[0][0] = x * m.m_RowCol[0][0] + y * m.m_RowCol[0][1] + z * m.m_RowCol[0][2];
			m_RowCol[1][0] = x * m.m_RowCol[1][0] + y * m.m_RowCol[1][1] + z * m.m_RowCol[1][2];
			m_RowCol[2][0] = x * m.m_RowCol[2][0] + y * m.m_RowCol[2][1] + z * m.m_RowCol[2][2];

			x = m_RowCol[0][1];
			y = m_RowCol[1][1];
			z = m_RowCol[2][1];
			m_RowCol[0][1] = x * m.m_RowCol[0][0] + y * m.m_RowCol[0][1] + z * m.m_RowCol[0][2];
			m_RowCol[1][1] = x * m.m_RowCol[1][0] + y * m.m_RowCol[1][1] + z * m.m_RowCol[1][2];
			m_RowCol[2][1] = x * m.m_RowCol[2][0] + y * m.m_RowCol[2][1] + z * m.m_RowCol[2][2];

			x = m_RowCol[0][2];
			y = m_RowCol[1][2];
			z = m_RowCol[2][2];
			m_RowCol[0][2] = x * m.m_RowCol[0][0] + y * m.m_RowCol[0][1] + z * m.m_RowCol[0][2];
			m_RowCol[1][2] = x * m.m_RowCol[1][0] + y * m.m_RowCol[1][1] + z * m.m_RowCol[1][2];
			m_RowCol[2][2] = x * m.m_RowCol[2][0] + y * m.m_RowCol[2][1] + z * m.m_RowCol[2][2];

			return (*this);
		}

		void GetEulerAngles(float *x, float *y, float *z) const
		{
			float sy = m_RowCol[2][0];
			if (sy < 1.0F)
			{
				if (sy > -1.0F)
				{
					*x = -Atan(m_RowCol[2][1], m_RowCol[2][2]);
					*y = Asin(sy);
					*z = -Atan(m_RowCol[1][0], m_RowCol[0][0]);
				}
				else
				{
					*x = 0.0F;
					*y = -pi_over_2;
					*z = Atan(m_RowCol[0][1], m_RowCol[1][1]);
				}
			}
			else
			{
				*x = 0.0F;
				*y = pi_over_2;
				*z = Atan(m_RowCol[0][1], m_RowCol[1][1]);
			}
		}

		Transform4& SetEulerAngles(float x, float y, float z)
		{
			float cx = Cos(x);
			float cy = Cos(y);
			float cz = Cos(z);
			float sx = Sin(x);
			float sy = Sin(y);
			float sz = Sin(z);

			m_RowCol[0][0] = cy * cz;
			m_RowCol[0][1] = cx * sz + sx * sy * cz;
			m_RowCol[0][2] = sx * sz - cx * sy * cz;
			m_RowCol[1][0] = -cy * sz;
			m_RowCol[1][1] = cx * cz - sx * sy * sz;
			m_RowCol[1][2] = sx * cz + cx * sy * sz;
			m_RowCol[2][0] = sy;
			m_RowCol[2][1] = -sx * cy;
			m_RowCol[2][2] = cx * cy;

			return (*this);
		}


		Transform4& SetScale(float t)
		{
			m_RowCol[0][0] = m_RowCol[1][1] = m_RowCol[2][2] = t;
			m_RowCol[3][3] = 1.0F;

			return (*this);
		}

		Transform4& SetScale(float r, float s, float t)
		{
			m_RowCol[0][0] = r;
			m_RowCol[1][1] = s;
			m_RowCol[2][2] = t;
			m_RowCol[3][3] = 1.0F;

			return (*this);
		}

		Transform4& SetScale(const Vector3& Scale)
		{
			m_RowCol[0][0] = Scale.x;
			m_RowCol[1][1] = Scale.y;
			m_RowCol[2][2] = Scale.z;
			m_RowCol[3][3] = 1.0F;

			return (*this);
		}

		Vector3 GetScale()
		{
			return Vector3(m_RowCol[0][0], m_RowCol[1][1], m_RowCol[2][2]);
		}

		Transform4& SetDisplacement(const Vector3& dv)
		{
			m_RowCol[3][0] = dv.x;
			m_RowCol[3][1] = dv.y;
			m_RowCol[3][2] = dv.z;
			m_RowCol[0][0] = m_RowCol[1][1] = m_RowCol[2][2] = m_RowCol[3][3] = 1.0F;
			m_RowCol[1][0] = m_RowCol[2][0] = m_RowCol[0][1] = m_RowCol[2][1] = m_RowCol[0][2] = m_RowCol[1][2] = m_RowCol[0][3] = m_RowCol[1][3] = m_RowCol[2][3] = 0.0F;
			return (*this);
		}

		friend Transform4 operator *(const Transform4& m1, const Transform4& m2);
		friend Matrix4 operator *(const Transform4& m1, const Matrix4& m2);
		friend Transform4 operator *(const Transform4& m1, const Matrix3& m2);
		friend Transform4 operator *(const Matrix3& m1, const Transform4& m2);
		friend Vector4 operator *(const Transform4& m, const Vector4& v);
		friend Vector4 operator *(const Vector4& v, const Transform4& m);
		friend Vector3 operator *(const Transform4& m, const Vector3& v);
		friend Vector3 operator *(const Vector3& v, const Transform4& m);
		friend Vector3 operator *(const Transform4& m, const Vector3& p);
		friend Vector3 operator *(const Vector3& p, const Transform4& m);
		friend Vector2 operator *(const Transform4& m, const Vector2& v);
		friend Vector2 operator *(const Vector2& v, const Transform4& m);
		friend Vector2 operator *(const Transform4& m, const Vector2& p);
		friend Vector2 operator *(const Vector2& p, const Transform4& m);

		friend Matrix3 Transform(const Matrix3& m2, const Transform4& m1);
	}; //Class

	inline Transform4 operator *(const Transform4& m1, const Transform4& m2)
	{

		return (Transform4(m1.m_RowCol[0][0] * m2.m_RowCol[0][0] + m1.m_RowCol[1][0] * m2.m_RowCol[0][1] + m1.m_RowCol[2][0] * m2.m_RowCol[0][2],
			m1.m_RowCol[0][0] * m2.m_RowCol[1][0] + m1.m_RowCol[1][0] * m2.m_RowCol[1][1] + m1.m_RowCol[2][0] * m2.m_RowCol[1][2],
			m1.m_RowCol[0][0] * m2.m_RowCol[2][0] + m1.m_RowCol[1][0] * m2.m_RowCol[2][1] + m1.m_RowCol[2][0] * m2.m_RowCol[2][2],
			m1.m_RowCol[0][0] * m2.m_RowCol[3][0] + m1.m_RowCol[1][0] * m2.m_RowCol[3][1] + m1.m_RowCol[2][0] * m2.m_RowCol[3][2] + m1.m_RowCol[3][0],
			m1.m_RowCol[0][1] * m2.m_RowCol[0][0] + m1.m_RowCol[1][1] * m2.m_RowCol[0][1] + m1.m_RowCol[2][1] * m2.m_RowCol[0][2],
			m1.m_RowCol[0][1] * m2.m_RowCol[1][0] + m1.m_RowCol[1][1] * m2.m_RowCol[1][1] + m1.m_RowCol[2][1] * m2.m_RowCol[1][2],
			m1.m_RowCol[0][1] * m2.m_RowCol[2][0] + m1.m_RowCol[1][1] * m2.m_RowCol[2][1] + m1.m_RowCol[2][1] * m2.m_RowCol[2][2],
			m1.m_RowCol[0][1] * m2.m_RowCol[3][0] + m1.m_RowCol[1][1] * m2.m_RowCol[3][1] + m1.m_RowCol[2][1] * m2.m_RowCol[3][2] + m1.m_RowCol[3][1],
			m1.m_RowCol[0][2] * m2.m_RowCol[0][0] + m1.m_RowCol[1][2] * m2.m_RowCol[0][1] + m1.m_RowCol[2][2] * m2.m_RowCol[0][2],
			m1.m_RowCol[0][2] * m2.m_RowCol[1][0] + m1.m_RowCol[1][2] * m2.m_RowCol[1][1] + m1.m_RowCol[2][2] * m2.m_RowCol[1][2],
			m1.m_RowCol[0][2] * m2.m_RowCol[2][0] + m1.m_RowCol[1][2] * m2.m_RowCol[2][1] + m1.m_RowCol[2][2] * m2.m_RowCol[2][2],
			m1.m_RowCol[0][2] * m2.m_RowCol[3][0] + m1.m_RowCol[1][2] * m2.m_RowCol[3][1] + m1.m_RowCol[2][2] * m2.m_RowCol[3][2] + m1.m_RowCol[3][2]));

	}

	inline Matrix4 operator *(const Transform4& m1, const Matrix4& m2)
	{
		return (Matrix4(m1.m_RowCol[0][0] * m2.m_RowCol[0][0] + m1.m_RowCol[1][0] * m2.m_RowCol[0][1] + m1.m_RowCol[2][0] * m2.m_RowCol[0][2] + m1.m_RowCol[3][0] * m2.m_RowCol[0][3],
			m1.m_RowCol[0][0] * m2.m_RowCol[1][0] + m1.m_RowCol[1][0] * m2.m_RowCol[1][1] + m1.m_RowCol[2][0] * m2.m_RowCol[1][2] + m1.m_RowCol[3][0] * m2.m_RowCol[1][3],
			m1.m_RowCol[0][0] * m2.m_RowCol[2][0] + m1.m_RowCol[1][0] * m2.m_RowCol[2][1] + m1.m_RowCol[2][0] * m2.m_RowCol[2][2] + m1.m_RowCol[3][0] * m2.m_RowCol[2][3],
			m1.m_RowCol[0][0] * m2.m_RowCol[3][0] + m1.m_RowCol[1][0] * m2.m_RowCol[3][1] + m1.m_RowCol[2][0] * m2.m_RowCol[3][2] + m1.m_RowCol[3][0] * m2.m_RowCol[3][3],
			m1.m_RowCol[0][1] * m2.m_RowCol[0][0] + m1.m_RowCol[1][1] * m2.m_RowCol[0][1] + m1.m_RowCol[2][1] * m2.m_RowCol[0][2] + m1.m_RowCol[3][1] * m2.m_RowCol[0][3],
			m1.m_RowCol[0][1] * m2.m_RowCol[1][0] + m1.m_RowCol[1][1] * m2.m_RowCol[1][1] + m1.m_RowCol[2][1] * m2.m_RowCol[1][2] + m1.m_RowCol[3][1] * m2.m_RowCol[1][3],
			m1.m_RowCol[0][1] * m2.m_RowCol[2][0] + m1.m_RowCol[1][1] * m2.m_RowCol[2][1] + m1.m_RowCol[2][1] * m2.m_RowCol[2][2] + m1.m_RowCol[3][1] * m2.m_RowCol[2][3],
			m1.m_RowCol[0][1] * m2.m_RowCol[3][0] + m1.m_RowCol[1][1] * m2.m_RowCol[3][1] + m1.m_RowCol[2][1] * m2.m_RowCol[3][2] + m1.m_RowCol[3][1] * m2.m_RowCol[3][3],
			m1.m_RowCol[0][2] * m2.m_RowCol[0][0] + m1.m_RowCol[1][2] * m2.m_RowCol[0][1] + m1.m_RowCol[2][2] * m2.m_RowCol[0][2] + m1.m_RowCol[3][2] * m2.m_RowCol[0][3],
			m1.m_RowCol[0][2] * m2.m_RowCol[1][0] + m1.m_RowCol[1][2] * m2.m_RowCol[1][1] + m1.m_RowCol[2][2] * m2.m_RowCol[1][2] + m1.m_RowCol[3][2] * m2.m_RowCol[1][3],
			m1.m_RowCol[0][2] * m2.m_RowCol[2][0] + m1.m_RowCol[1][2] * m2.m_RowCol[2][1] + m1.m_RowCol[2][2] * m2.m_RowCol[2][2] + m1.m_RowCol[3][2] * m2.m_RowCol[2][3],
			m1.m_RowCol[0][2] * m2.m_RowCol[3][0] + m1.m_RowCol[1][2] * m2.m_RowCol[3][1] + m1.m_RowCol[2][2] * m2.m_RowCol[3][2] + m1.m_RowCol[3][2] * m2.m_RowCol[3][3],
			m2.m_RowCol[0][3], m2.m_RowCol[1][3], m2.m_RowCol[2][3], m2.m_RowCol[3][3]));
	}

	inline Transform4 operator *(const Transform4& m1, const Matrix3& m2)
	{
		return (Transform4(m1.m_RowCol[0][0] * m2.m_RowCol[0][0] + m1.m_RowCol[1][0] * m2.m_RowCol[0][1] + m1.m_RowCol[2][0] * m2.m_RowCol[0][2],
			m1.m_RowCol[0][0] * m2.m_RowCol[1][0] + m1.m_RowCol[1][0] * m2.m_RowCol[1][1] + m1.m_RowCol[2][0] * m2.m_RowCol[1][2],
			m1.m_RowCol[0][0] * m2.m_RowCol[2][0] + m1.m_RowCol[1][0] * m2.m_RowCol[2][1] + m1.m_RowCol[2][0] * m2.m_RowCol[2][2],
			m1.m_RowCol[3][0],
			m1.m_RowCol[0][1] * m2.m_RowCol[0][0] + m1.m_RowCol[1][1] * m2.m_RowCol[0][1] + m1.m_RowCol[2][1] * m2.m_RowCol[0][2],
			m1.m_RowCol[0][1] * m2.m_RowCol[1][0] + m1.m_RowCol[1][1] * m2.m_RowCol[1][1] + m1.m_RowCol[2][1] * m2.m_RowCol[1][2],
			m1.m_RowCol[0][1] * m2.m_RowCol[2][0] + m1.m_RowCol[1][1] * m2.m_RowCol[2][1] + m1.m_RowCol[2][1] * m2.m_RowCol[2][2],
			m1.m_RowCol[3][1],
			m1.m_RowCol[0][2] * m2.m_RowCol[0][0] + m1.m_RowCol[1][2] * m2.m_RowCol[0][1] + m1.m_RowCol[2][2] * m2.m_RowCol[0][2],
			m1.m_RowCol[0][2] * m2.m_RowCol[1][0] + m1.m_RowCol[1][2] * m2.m_RowCol[1][1] + m1.m_RowCol[2][2] * m2.m_RowCol[1][2],
			m1.m_RowCol[0][2] * m2.m_RowCol[2][0] + m1.m_RowCol[1][2] * m2.m_RowCol[2][1] + m1.m_RowCol[2][2] * m2.m_RowCol[2][2],
			m1.m_RowCol[3][2]));
	}

	inline Transform4 operator *(const Matrix3& m1, const Transform4& m2)
	{
		return (Transform4(m1.m_RowCol[0][0] * m2.m_RowCol[0][0] + m1.m_RowCol[1][0] * m2.m_RowCol[0][1] + m1.m_RowCol[2][0] * m2.m_RowCol[0][2],
			m1.m_RowCol[0][0] * m2.m_RowCol[1][0] + m1.m_RowCol[1][0] * m2.m_RowCol[1][1] + m1.m_RowCol[2][0] * m2.m_RowCol[1][2],
			m1.m_RowCol[0][0] * m2.m_RowCol[2][0] + m1.m_RowCol[1][0] * m2.m_RowCol[2][1] + m1.m_RowCol[2][0] * m2.m_RowCol[2][2],
			m1.m_RowCol[0][0] * m2.m_RowCol[3][0] + m1.m_RowCol[1][0] * m2.m_RowCol[3][1] + m1.m_RowCol[2][0] * m2.m_RowCol[3][2],
			m1.m_RowCol[0][1] * m2.m_RowCol[0][0] + m1.m_RowCol[1][1] * m2.m_RowCol[0][1] + m1.m_RowCol[2][1] * m2.m_RowCol[0][2],
			m1.m_RowCol[0][1] * m2.m_RowCol[1][0] + m1.m_RowCol[1][1] * m2.m_RowCol[1][1] + m1.m_RowCol[2][1] * m2.m_RowCol[1][2],
			m1.m_RowCol[0][1] * m2.m_RowCol[2][0] + m1.m_RowCol[1][1] * m2.m_RowCol[2][1] + m1.m_RowCol[2][1] * m2.m_RowCol[2][2],
			m1.m_RowCol[0][1] * m2.m_RowCol[3][0] + m1.m_RowCol[1][1] * m2.m_RowCol[3][1] + m1.m_RowCol[2][1] * m2.m_RowCol[3][2],
			m1.m_RowCol[0][2] * m2.m_RowCol[0][0] + m1.m_RowCol[1][2] * m2.m_RowCol[0][1] + m1.m_RowCol[2][2] * m2.m_RowCol[0][2],
			m1.m_RowCol[0][2] * m2.m_RowCol[1][0] + m1.m_RowCol[1][2] * m2.m_RowCol[1][1] + m1.m_RowCol[2][2] * m2.m_RowCol[1][2],
			m1.m_RowCol[0][2] * m2.m_RowCol[2][0] + m1.m_RowCol[1][2] * m2.m_RowCol[2][1] + m1.m_RowCol[2][2] * m2.m_RowCol[2][2],
			m1.m_RowCol[0][2] * m2.m_RowCol[3][0] + m1.m_RowCol[1][2] * m2.m_RowCol[3][1] + m1.m_RowCol[2][2] * m2.m_RowCol[3][2]));
	}

	inline Vector4 operator *(const Transform4& m, const Vector4& v)
	{
		return (Vector4(m.m_RowCol[0][0] * v.x + m.m_RowCol[1][0] * v.y + m.m_RowCol[2][0] * v.z + m.m_RowCol[3][0] * v.w,
			m.m_RowCol[0][1] * v.x + m.m_RowCol[1][1] * v.y + m.m_RowCol[2][1] * v.z + m.m_RowCol[3][1] * v.w,
			m.m_RowCol[0][2] * v.x + m.m_RowCol[1][2] * v.y + m.m_RowCol[2][2] * v.z + m.m_RowCol[3][2] * v.w,
			v.w));
	}

	inline Vector4 operator *(const Vector4& v, const Transform4& m)
	{
		return (Vector4(m.m_RowCol[0][0] * v.x + m.m_RowCol[0][1] * v.y + m.m_RowCol[0][2] * v.z,
			m.m_RowCol[1][0] * v.x + m.m_RowCol[1][1] * v.y + m.m_RowCol[1][2] * v.z,
			m.m_RowCol[2][0] * v.x + m.m_RowCol[2][1] * v.y + m.m_RowCol[2][2] * v.z,
			m.m_RowCol[3][0] * v.x + m.m_RowCol[3][1] * v.y + m.m_RowCol[3][2] * v.z + v.w));
	}

	inline Vector3 operator *(const Transform4& m, const Vector3& v)
	{
		return (Vector3(m.m_RowCol[0][0] * v.x + m.m_RowCol[1][0] * v.y + m.m_RowCol[2][0] * v.z,
			m.m_RowCol[0][1] * v.x + m.m_RowCol[1][1] * v.y + m.m_RowCol[2][1] * v.z,
			m.m_RowCol[0][2] * v.x + m.m_RowCol[1][2] * v.y + m.m_RowCol[2][2] * v.z));
	}

	inline Vector3 operator *(const Vector3& v, const Transform4& m)
	{
		return (Vector3(m.m_RowCol[0][0] * v.x + m.m_RowCol[0][1] * v.y + m.m_RowCol[0][2] * v.z,
			m.m_RowCol[1][0] * v.x + m.m_RowCol[1][1] * v.y + m.m_RowCol[1][2] * v.z,
			m.m_RowCol[2][0] * v.x + m.m_RowCol[2][1] * v.y + m.m_RowCol[2][2] * v.z));
	}

	inline Vector2 operator *(const Transform4& m, const Vector2& v)
	{
		return (Vector2(m.m_RowCol[0][0] * v.x + m.m_RowCol[1][0] * v.y,
			m.m_RowCol[0][1] * v.x + m.m_RowCol[1][1] * v.y));
	}

	inline Vector2 operator *(const Vector2& v, const Transform4& m)
	{
		return (Vector2(m.m_RowCol[0][0] * v.x + m.m_RowCol[0][1] * v.y,
			m.m_RowCol[1][0] * v.x + m.m_RowCol[1][1] * v.y));
	}

	inline Matrix3 Transform(const Matrix3& m2, const Transform4& m1)
	{
		return (Matrix3(m1.m_RowCol[0][0] * m2.m_RowCol[0][0] + m1.m_RowCol[1][0] * m2.m_RowCol[0][1] + m1.m_RowCol[2][0] * m2.m_RowCol[0][2],
			m1.m_RowCol[0][0] * m2.m_RowCol[1][0] + m1.m_RowCol[1][0] * m2.m_RowCol[1][1] + m1.m_RowCol[2][0] * m2.m_RowCol[1][2],
			m1.m_RowCol[0][0] * m2.m_RowCol[2][0] + m1.m_RowCol[1][0] * m2.m_RowCol[2][1] + m1.m_RowCol[2][0] * m2.m_RowCol[2][2],
			m1.m_RowCol[0][1] * m2.m_RowCol[0][0] + m1.m_RowCol[1][1] * m2.m_RowCol[0][1] + m1.m_RowCol[2][1] * m2.m_RowCol[0][2],
			m1.m_RowCol[0][1] * m2.m_RowCol[1][0] + m1.m_RowCol[1][1] * m2.m_RowCol[1][1] + m1.m_RowCol[2][1] * m2.m_RowCol[1][2],
			m1.m_RowCol[0][1] * m2.m_RowCol[2][0] + m1.m_RowCol[1][1] * m2.m_RowCol[2][1] + m1.m_RowCol[2][1] * m2.m_RowCol[2][2],
			m1.m_RowCol[0][2] * m2.m_RowCol[0][0] + m1.m_RowCol[1][2] * m2.m_RowCol[0][1] + m1.m_RowCol[2][2] * m2.m_RowCol[0][2],
			m1.m_RowCol[0][2] * m2.m_RowCol[1][0] + m1.m_RowCol[1][2] * m2.m_RowCol[1][1] + m1.m_RowCol[2][2] * m2.m_RowCol[1][2],
			m1.m_RowCol[0][2] * m2.m_RowCol[2][0] + m1.m_RowCol[1][2] * m2.m_RowCol[2][1] + m1.m_RowCol[2][2] * m2.m_RowCol[2][2]));
	}

}//namespace

#endif //_ARGONTRANSFORM4_HEADER_
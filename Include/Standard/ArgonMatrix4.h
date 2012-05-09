#ifndef _ARGONMATRIX4_HEADER_
#define	_ARGONMATRIX4_HEADER_

#include <cstring>
#include <Standard/ArgonVector3.h>

namespace Argon
{
	template<typename T>class Matrix4T
	{
		friend class Transform4;
	public:

		Matrix4T(bool SetToIdentity = true)
		{
			if(SetToIdentity)
			{
				SetIdentity();
			}
		}

		Matrix4T(const T Init[16])
		{
			m_Single[0] = Init[0];
			m_Single[1] = Init[1];
			m_Single[2] = Init[2];
			m_Single[3] = Init[3];
			m_Single[4] = Init[4];
			m_Single[5] = Init[5];
			m_Single[6] = Init[6];
			m_Single[7] = Init[7];
			m_Single[8] = Init[8];
			m_Single[9] = Init[9];
			m_Single[10] = Init[10];
			m_Single[11] = Init[11];
			m_Single[12] = Init[12];
			m_Single[13] = Init[13];
			m_Single[14] = Init[14];
			m_Single[15] = Init[15];
		}

		Matrix4T(T m00, T m01, T m02, T m03, T m10, T m11, T m12, T m13, T m20, T m21, T m22, T m23, T m30, T m31, T m32, T m33)
		{
			m_Single[0] = m00;
			m_Single[1] = m01;
			m_Single[2] = m02;
			m_Single[3] = m03;
			m_Single[4] = m10;
			m_Single[5] = m11;
			m_Single[6] = m12;
			m_Single[7] = m13;
			m_Single[8] = m20;
			m_Single[9] = m21;
			m_Single[10] = m22;
			m_Single[11] = m23;
			m_Single[12] = m30;
			m_Single[13] = m31;
			m_Single[14] = m32;
			m_Single[15] = m33;
		}

		// operators
		Matrix4T operator*(const Matrix4T& RHS) const
		{
			Matrix4T Return;

			for (int i = 0; i < 4; ++i)
			{
				Return.m_RowCol[i][0] = 
					m_RowCol[i][0] * RHS.m_RowCol[0][0] +
					m_RowCol[i][1] * RHS.m_RowCol[1][0] +
					m_RowCol[i][2] * RHS.m_RowCol[2][0] +
					m_RowCol[i][3] * RHS.m_RowCol[3][0];
				Return.m_RowCol[i][1] = 
					m_RowCol[i][0] * RHS.m_RowCol[0][1] +
					m_RowCol[i][1] * RHS.m_RowCol[1][1] +
					m_RowCol[i][2] * RHS.m_RowCol[2][1] +
					m_RowCol[i][3] * RHS.m_RowCol[3][1];
				Return.m_RowCol[i][2] = 
					m_RowCol[i][0] * RHS.m_RowCol[0][2] +
					m_RowCol[i][1] * RHS.m_RowCol[1][2] +
					m_RowCol[i][2] * RHS.m_RowCol[2][2] +
					m_RowCol[i][3] * RHS.m_RowCol[3][2];
				Return.m_RowCol[i][3] = 
					m_RowCol[i][0] * RHS.m_RowCol[0][3] +
					m_RowCol[i][1] * RHS.m_RowCol[1][3] +
					m_RowCol[i][2] * RHS.m_RowCol[2][3] +
					m_RowCol[i][3] * RHS.m_RowCol[3][3];
			}

			return Return;
		}

		Vector3 operator*(const Vector3& RHS) const
		{
			return Vector3(
				m_Single[0] * RHS.x + m_Single[4] * RHS.y + m_Single[8] * RHS.z + m_Single[12],
				m_Single[1] * RHS.x + m_Single[5] * RHS.y + m_Single[9] * RHS.z + m_Single[13],
				m_Single[2] * RHS.x + m_Single[6] * RHS.y + m_Single[10] * RHS.z + m_Single[14]);
		}

		bool operator==(const Matrix4T& RHS) const
		{
			return (memcmp(m_Single, RHS.m_Single, 16 * sizeof(T)) == 0);
		}

		bool operator!=(const Matrix4T& RHS) const
		{
			return (memcmp(m_Single, RHS.m_Single, 16 * sizeof(T)) != 0);
		}

		T& operator () (int Row, int Coloumn)
		{ 
			return m_Single[Coloumn * 4 + Row];	
		}

		const T& operator () (int Row, int Coloumn) const
		{ 
			return m_Single[Coloumn * 4 + Row];
		}

		T& operator [](int Index)	
		{
			return m_Single[Index];	
		}

		void SetIdentity()
		{
			memset(m_Single, 0, 16 * sizeof(T));
			m_Single[0] = m_Single[5] = m_Single[10] = m_Single[15] = 1.0f;
		}

		void GetVectorComponents(Vector3& Up, Vector3& Out, Vector3& Right)
		{
			Right.x = m_Single[0];
			Right.y = m_Single[4];
			Right.z = m_Single[8];

			Up.x = m_Single[1];
			Up.y = m_Single[5];
			Up.z = m_Single[9];

			Out.x = m_Single[2];
			Out.y = m_Single[6];
			Out.z = m_Single[10];
		}

		bool Invert(Matrix4T& Result) const
		{
			const T Tiny = 1.0e-20f;

			T A0 = m_Single[ 0] * m_Single[ 5] - m_Single[ 1] * m_Single[ 4];
			T A1 = m_Single[ 0] * m_Single[ 6] - m_Single[ 2] * m_Single[ 4];
			T A2 = m_Single[ 0] * m_Single[ 7] - m_Single[ 3] * m_Single[ 4];
			T A3 = m_Single[ 1] * m_Single[ 6] - m_Single[ 2] * m_Single[ 5];
			T A4 = m_Single[ 1] * m_Single[ 7] - m_Single[ 3] * m_Single[ 5];
			T A5 = m_Single[ 2] * m_Single[ 7] - m_Single[ 3] * m_Single[ 6];
			T B0 = m_Single[ 8] * m_Single[13] - m_Single[ 9] * m_Single[12];
			T B1 = m_Single[ 8] * m_Single[14] - m_Single[10] * m_Single[12];
			T B2 = m_Single[ 8] * m_Single[15] - m_Single[11] * m_Single[12];
			T B3 = m_Single[ 9] * m_Single[14] - m_Single[10] * m_Single[13];
			T B4 = m_Single[ 9] * m_Single[15] - m_Single[11] * m_Single[13];
			T B5 = m_Single[10] * m_Single[15] - m_Single[11] * m_Single[14];

			T Det = A0 * B5 - A1 * B4 + A2 * B3 + A3 * B2 - A4 * B1 + A5 * B0;
			if (fabs(Det) <= Tiny)
				return false;

			Result.SetIdentity( );
			Result.m_Single[0] =  m_Single[5] * B5 - m_Single[ 6] * B4 + m_Single[ 7] * B3;
			Result.m_Single[4] = -m_Single[4] * B5 + m_Single[ 6] * B2 - m_Single[ 7] * B1;
			Result.m_Single[8] =  m_Single[4] * B4 - m_Single[ 5] * B2 + m_Single[ 7] * B0;
			Result.m_Single[12] = -m_Single[4] * B3 + m_Single[ 5] * B1 - m_Single[ 6] * B0;
			Result.m_Single[1] = -m_Single[1] * B5 + m_Single[ 2] * B4 - m_Single[ 3] * B3;
			Result.m_Single[5] =  m_Single[0] * B5 - m_Single[ 2] * B2 + m_Single[ 3] * B1;
			Result.m_Single[9] = -m_Single[0] * B4 + m_Single[ 1] * B2 - m_Single[ 3] * B0;
			Result.m_Single[13] =  m_Single[0] * B3 - m_Single[ 1] * B1 + m_Single[ 2] * B0;
			Result.m_Single[2] =  m_Single[13] * A5 - m_Single[14] * A4 + m_Single[15] * A3;
			Result.m_Single[6] = -m_Single[12] * A5 + m_Single[14] * A2 - m_Single[15] * A1;
			Result.m_Single[10] =  m_Single[12] * A4 - m_Single[13] * A2 + m_Single[15] * A0;
			Result.m_Single[14] = -m_Single[12] * A3 + m_Single[13] * A1 - m_Single[14] * A0;
			Result.m_Single[3] = -m_Single[9] * A5 + m_Single[10] * A4 - m_Single[11] * A3;
			Result.m_Single[7] =  m_Single[8] * A5 - m_Single[10] * A2 + m_Single[11] * A1;
			Result.m_Single[11] = -m_Single[8] * A4 + m_Single[ 9] * A2 - m_Single[11] * A0;
			Result.m_Single[15] =  m_Single[8] * A3 - m_Single[ 9] * A1 + m_Single[10] * A0;

			T InvDet = 1.0f / Det;
			Result.m_Single[ 0] *= InvDet;
			Result.m_Single[ 1] *= InvDet;
			Result.m_Single[ 2] *= InvDet;
			Result.m_Single[ 3] *= InvDet;
			Result.m_Single[ 4] *= InvDet;
			Result.m_Single[ 5] *= InvDet;
			Result.m_Single[ 6] *= InvDet;
			Result.m_Single[ 7] *= InvDet;
			Result.m_Single[ 8] *= InvDet;
			Result.m_Single[ 9] *= InvDet;
			Result.m_Single[10] *= InvDet;
			Result.m_Single[11] *= InvDet;
			Result.m_Single[12] *= InvDet;
			Result.m_Single[13] *= InvDet;
			Result.m_Single[14] *= InvDet;
			Result.m_Single[15] *= InvDet;

			return true;
		}

		void LookAt(const Vector3& Eye, const Vector3& Center, const Vector3& Up)
		{
			Vector3 F(Center - Eye);
			F.Normalize( );

			Vector3 UpPrime(Up);
			UpPrime.Normalize();

			Vector3 S = F.Cross(UpPrime);
			Vector3 U = S.Cross(F);

			Matrix4T Temp;
			Temp.m_RowCol[0][0] = S[0];
			Temp.m_RowCol[1][0] = S[1];
			Temp.m_RowCol[2][0] = S[2];

			Temp.m_RowCol[0][1] = U[0];
			Temp.m_RowCol[1][1] = U[1];
			Temp.m_RowCol[2][1] = U[2];

			Temp.m_RowCol[0][2] = -F[0];
			Temp.m_RowCol[1][2] = -F[1];
			Temp.m_RowCol[2][2] = -F[2];

			*this = *this * Temp;

			Translate(-Eye);
		}

		void Ortho(T Left, T Right, T Bottom, T Top, T Near, T Far, bool OpenGL = false)
		{
			Matrix4T Temp;
			if (OpenGL)
			{
				Temp.m_Single[0] = 2.0f / (Right - Left);
				Temp.m_Single[5] = 2.0f / (Top - Bottom);
				Temp.m_Single[10] = -2.0f / (Far - Near);
				Temp.m_Single[12] = -(Right + Left) / (Right - Left);
				Temp.m_Single[13] = -(Top + Bottom) / (Top - Bottom);
				Temp.m_Single[14] = -(Far + Near) / (Far - Near);
				Temp.m_Single[15] = 1.0f;
			}
			else
			{
				Temp.m_Single[0] = 2.0f / (Right - Left);
				Temp.m_Single[5] = 2.0f / (Top - Bottom);
				Temp.m_Single[10] = 1.0f / (Near - Far);
				Temp.m_Single[12] = (Left + Right) / (Left - Right);
				Temp.m_Single[13] = (Top + Bottom) / (Bottom - Top);
				Temp.m_Single[14] = Near / (Near - Far);
				Temp.m_Single[15] = 1.0f;
			}

			*this = *this * Temp;
		}

		void Frustum(T Left, T Right, T Bottom, T Top, T Near, T Far)
		{
			Matrix4T Temp;

			T a = (fRight + Left) / (Right - Left);
			T b = (Top + Bottom) / (Top - Bottom);
			T c = -(Far + Near) / (Far - Near);
			T d = -(2.0f * (Far * Near)) / (Far - Near);

			Temp.m_Single[0] = 2.0f * Near / (Right - Left);
			Temp.m_Single[5] = 2.0f * Near / (Top - Bottom);
			Temp.m_Single[8] = a;
			Temp.m_Single[9] = b;
			Temp.m_Single[10] = c;
			Temp.m_Single[11] = -1.0f;
			Temp.m_Single[14] = d;
			Temp.m_Single[15] = 0.0f;

			*this = *this * Temp;
		}

		void Perspective(T FieldOfView, T AspectRatio, T Near, T Far)
		{
			Matrix4T Temp;

			T f = 1.0f / tan(0.5f * FieldOfView);

			Temp.m_Single[0] = f / AspectRatio;
			Temp.m_Single[5] = f;
			Temp.m_Single[10] = (Far + Near) / (Near - Far);
			Temp.m_Single[11] = -1.0f;
			Temp.m_Single[14] = 2.0f * Far * Near / (Near - Far);
			Temp.m_Single[15] = 0.0f;

			*this = *this * Temp;
		}

		union
		{
			T  m_Single[16];
			T  m_RowCol[4][4];
		};
	};

#	if defined ArgonX64
	typedef Matrix4T<double> Matrix4;
#	else 
	typedef Matrix4T<float> Matrix4;
#	endif

	inline float Determinant(const Matrix4& m)
	{
		float n00 = m(0,0);
		float n01 = m(0,1);
		float n02 = m(0,2);

		float n10 = m(1,0);
		float n11 = m(1,1);
		float n12 = m(1,2);

		float n20 = m(2,0);
		float n21 = m(2,1);
		float n22 = m(2,2);

		return (n00 * (n11 * n22 - n12 * n21) + n01 * (n12 * n20 - n10 * n22) + n02 * (n10 * n21 - n11 * n20));
	}

	inline Vector3 InverseTransform(const Matrix4& m, const Vector3& p)
	{
		float n00 = m(0,0);
		float n01 = m(0,1);
		float n02 = m(0,2);
		float n03 = m(0,3);

		float n10 = m(1,0);
		float n11 = m(1,1);
		float n12 = m(1,2);
		float n13 = m(1,3);

		float n20 = m(2,0);
		float n21 = m(2,1);
		float n22 = m(2,2);
		float n23 = m(2,3);

		float p00 = n11 * n22 - n12 * n21;
		float p10 = n12 * n20 - n10 * n22;
		float p20 = n10 * n21 - n11 * n20;

		float t = 1.0F / (n00 * p00 + n01 * p10 + n02 * p20);

		return (Vector3((p00 * p.x + (n02 * n21 - n01 * n22) * p.y + (n01 * n12 - n02 * n11) * p.z + (n01 * (n13 * n22 - n12 * n23) + n02 * (n11 * n23 - n13 * n21) + n03 * (n12 * n21 - n11 * n22))) * t,
			(p10 * p.x + (n00 * n22 - n02 * n20) * p.y + (n02 * n10 - n00 * n12) * p.z + (n00 * (n12 * n23 - n13 * n22) + n02 * (n13 * n20 - n10 * n23) + n03 * (n10 * n22 - n12 * n20))) * t,
			(p20 * p.x + (n01 * n20 - n00 * n21) * p.y + (n00 * n11 - n01 * n10) * p.z + (n00 * (n13 * n21 - n11 * n23) + n01 * (n10 * n23 - n13 * n20) + n03 * (n11 * n20 - n10 * n21))) * t));
	}

	inline Vector3 AdjugateTransform(const Matrix4& m, const Vector3& v)
	{
		float n00 = m(0,0);
		float n01 = m(0,1);
		float n02 = m(0,2);

		float n10 = m(1,0);
		float n11 = m(1,1);
		float n12 = m(1,2);

		float n20 = m(2,0);
		float n21 = m(2,1);
		float n22 = m(2,2);

		return (Vector3((n11 * n22 - n12 * n21) * v.x + (n02 * n21 - n01 * n22) * v.y + (n01 * n12 - n02 * n11) * v.z,
			(n12 * n20 - n10 * n22) * v.x + (n00 * n22 - n02 * n20) * v.y + (n02 * n10 - n00 * n12) * v.z,
			(n10 * n21 - n11 * n20) * v.x + (n01 * n20 - n00 * n21) * v.y + (n00 * n11 - n01 * n10) * v.z));
	}

} //Namespace

#endif //_ARGONMATRIX4_HEADER_

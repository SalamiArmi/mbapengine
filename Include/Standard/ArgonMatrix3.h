#ifndef _ARGONMATRIX3_HEADER_
#define _ARGONMATRIX3_HEADER_

namespace Argon
{
	template<typename T>class Matrix3T
	{
	public:
		Matrix3T(bool bSetToIdentity = true)
		{
			if (SetToIdentity)
				SetIdentity( );
		}

		Matrix3T(T m11, T m12, T m13, T m21, T m22, T m23, T m31, T m32, T m33)
		{
			m_RowCol[0][0] = m11;
			m_RowCol[0][1] = m12;
			m_RowCol[0][2] = m13;

			m_RowCol[1][0] = m21;
			m_RowCol[1][1] = m22;
			m_RowCol[1][2] = m23;

			m_RowCol[2][0] = m31;
			m_RowCol[2][1] = m32;
			m_RowCol[2][2] = m33;
		}

		Matrix3T operator*(const Matrix3T& In) const
		{
			Matrix3T cTmp;

			for (int i = 0; i < 3; ++i)
			{
				cTmp.m_RowCol[i][0] = m_RowCol[i][0] * In.m_RowCol[0][0] +
					m_RowCol[i][1] * In.m_RowCol[1][0] +
					m_RowCol[i][2] * In.m_RowCol[2][0];
				cTmp.m_RowCol[i][1] = m_RowCol[i][0] * In.m_RowCol[0][1] +
					m_RowCol[i][1] * In.m_RowCol[1][1] +
					m_RowCol[i][2] * In.m_RowCol[2][1];
				cTmp.m_RowCol[i][2] = m_RowCol[i][0] * In.m_RowCol[0][2] +
					m_RowCol[i][1] * In.m_RowCol[1][2] +
					m_RowCol[i][2] * In.m_RowCol[2][2];
			}

			return cTmp;
		}

		Vector3 operator*(const Vector3& In) const
		{
			return Vector3(m_RowCol[0][0] * In.x + m_RowCol[0][1] * In.y + m_RowCol[0][2] * In.z,
				m_RowCol[1][0] * In.x + m_RowCol[1][1] * In.y + m_RowCol[1][2] * In.z,
				m_RowCol[2][0] * In.x + m_RowCol[2][1] * In.y + m_RowCol[2][2] * In.z);
		}

		bool operator==(const Matrix3T& In) const
		{
			return (memcmp(m_Single, In.m_Single, 9 * sizeof(T)) == 0);
		}

		bool operator!=(const Matrix3T& In) const
		{
			return (memcmp(m_Single, In.m_Single, 9 * sizeof(T)) != 0);
		}

		T& operator () (int r,int c)	
		{ 
			return m_Single[c*3+r];
		}

		const T& operator () (int r,int c) const		
		{
			return m_Single[c*3+r];
		}

		T& operator [](int index)	
		{ 
			return m_Single[index];	
		}

		void SetIdentity(void)
		{
			memset(m_Single, 0, 9 * sizeof(T));
			m_Single[0] = m_Single[4] = m_Single[8] = 1.0f;                   
		}

		// mathematical operations
		void RotateX(T Radians)
		{
			Matrix3T mRotate;

			T Cosine = cosf(Radians);
			T Sine = sinf(Radians);

			mRotate.m_RowCol[1][1] = Cosine;
			mRotate.m_RowCol[1][2] = Sine;
			mRotate.m_RowCol[2][1] = -Sine;
			mRotate.m_RowCol[2][2] = Cosine;

			// this function can be further optimized by hardcoding
			// the multiplication here and removing terms with 0.0 multipliers
			*this = mRotate * *this;
		}

		void RotateY(T Radians)
		{
			Matrix3T mRotate;

			T Cosine = cosf(Radians);
			T Sine = sinf(Radians);

			mRotate.m_RowCol[0][0] = Cosine;
			mRotate.m_RowCol[0][2] = -Sine;
			mRotate.m_RowCol[2][0] = Sine;
			mRotate.m_RowCol[2][2] = Cosine;

			// this function can be further optimized by hardcoding
			// the multiplication here and removing terms with 0.0 multipliers
			*this = mRotate * *this;
		}

		void RotateZ(T Radians)
		{
			Matrix3T mRotate;

			T Cosine = cosf(Radians);
			T Sine = sinf(Radians);

			mRotate.m_RowCol[0][0] = Cosine;
			mRotate.m_RowCol[1][0] = -Sine;
			mRotate.m_RowCol[0][1] = Sine;
			mRotate.m_RowCol[1][1] = Cosine;

			// this function can be further optimized by hardcoding
			// the multiplication here and removing terms with 0.0 multipliers
			*this = mRotate * *this;
		}

		void RotateArbitrary(const Vector3& Axis, T Radius)
		{
			T s = sinf(Radians);
			T c = cosf(Radians);
			T t = 1.0f - c;

			Vector3 vNormalizedAxis(vAxis);
			vNormalizedAxis.Normalize( );
			const T& x = vNormalizedAxis.x;
			const T& y = vNormalizedAxis.y;
			const T& z = vNormalizedAxis.z;

			Matrix3T mRotate;
			mRotate.m_RowCol[0][0] = t * x * x + c;
			mRotate.m_RowCol[0][1] = t * x * y + s * z;
			mRotate.m_RowCol[0][2] = t * x * z - s * y;
			mRotate.m_RowCol[1][0] = t * x * y - s * z;
			mRotate.m_RowCol[1][1] = t * y * y + c;
			mRotate.m_RowCol[1][2] = t * y * z + s * x;
			mRotate.m_RowCol[2][0] = t * x * z + s * y;
			mRotate.m_RowCol[2][1] = t * y * z - s * x;
			mRotate.m_RowCol[2][2] = t * z * z + c;

			*this = mRotate * *this;
		}

		void Scale(T x, T y, T z)
		{
			m_Single[0] *= x;
			m_Single[1] *= x;
			m_Single[2] *= x;
			m_Single[3] *= y;
			m_Single[4] *= y;
			m_Single[5] *= y;
			m_Single[6] *= z;
			m_Single[7] *= z;
			m_Single[8] *= z;
		}

		void Scale(const Vector3& Scale)
		{
			Scale(vScale.x, vScale.y, vScale.z);
		}

		union
		{
			T  m_Single[9];
			T  m_RowCol[3][3];
		};
	};

#	if defined ArgonX64
	typedef Matrix3T<double> Matrix3;
#	else 
	typedef Matrix3T<float> Matrix3;
#	endif

} //Namespace

#endif //_ARGONMATRIX3_HEADER_
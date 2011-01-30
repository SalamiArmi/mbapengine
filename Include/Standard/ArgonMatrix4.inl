
template <class T>
inline Matrix4T::Matrix4T(T m00, T m01, T m02, T m03,	T m10, T m11, T m12, T m13,	T m20, T m21, T m22, T m23,	T m30, T m31, T m32, T m33)
{
	T* pMatrix = m_Single;

	*pMatrix++ = m00;
	*pMatrix++ = m01;
	*pMatrix++ = m02;
	*pMatrix++ = m03;
	*pMatrix++ = m10;
	*pMatrix++ = m11;
	*pMatrix++ = m12;
	*pMatrix++ = m13;
	*pMatrix++ = m20;
	*pMatrix++ = m21;
	*pMatrix++ = m22;
	*pMatrix++ = m23;
	*pMatrix++ = m30;
	*pMatrix++ = m31;
	*pMatrix++ = m32;
	*pMatrix = m33;
}

template <class T>
inline Matrix4T::operator T*(void)
{
	return m_Single;
}

template <class T>
inline Matrix4T::operator const T*(void) const
{
	return m_Single;
}

template <class T>
inline Matrix4T Matrix4T::operator*(const Matrix4T& In) const
{
	Matrix4T cTmp;

	for (int i = 0; i < 4; ++i)
	{
		cTmp.m_RowCol[i][0] = m_RowCol[i][0] * In.m_RowCol[0][0] +
			m_RowCol[i][1] * In.m_RowCol[1][0] +
			m_RowCol[i][2] * In.m_RowCol[2][0] +
			m_RowCol[i][3] * In.m_RowCol[3][0];
		cTmp.m_RowCol[i][1] = m_RowCol[i][0] * In.m_RowCol[0][1] +
			m_RowCol[i][1] * In.m_RowCol[1][1] +
			m_RowCol[i][2] * In.m_RowCol[2][1] +
			m_RowCol[i][3] * In.m_RowCol[3][1];
		cTmp.m_RowCol[i][2] = m_RowCol[i][0] * In.m_RowCol[0][2] +
			m_RowCol[i][1] * In.m_RowCol[1][2] +
			m_RowCol[i][2] * In.m_RowCol[2][2] +
			m_RowCol[i][3] * In.m_RowCol[3][2];
		cTmp.m_RowCol[i][3] = m_RowCol[i][0] * In.m_RowCol[0][3] +
			m_RowCol[i][1] * In.m_RowCol[1][3] +
			m_RowCol[i][2] * In.m_RowCol[2][3] +
			m_RowCol[i][3] * In.m_RowCol[3][3];
	}

	return cTmp;
}

template <class T>
inline Vector3 Matrix4T::operator*(const Vector3& In) const
{
	return Vector3(m_Single[0] * In.x + m_Single[4] * In.y + m_Single[8] * In.z + m_Single[12],
		m_Single[1] * In.x + m_Single[5] * In.y + m_Single[9] * In.z + m_Single[13],
		m_Single[2] * In.x + m_Single[6] * In.y + m_Single[10] * In.z + m_Single[14]);
}

template <class T>
inline bool Matrix4T::operator==(const Matrix4T& In) const
{
	return (memcmp(m_Single, In.m_Single, 16 * sizeof(T)) == 0);
}

template <class T>
inline bool Matrix4T::operator!=(const Matrix4T& In) const
{
	return (memcmp(m_Single, In.m_Single, 16 * sizeof(T)) != 0);
}

template <class T>
inline void Matrix4T::SetIdentity()
{
	memset(m_Single, 0, 16 * sizeof(T));
	m_Single[0] = m_Single[5] = m_Single[10] = m_Single[15] = 1.0f;
}

template <class T>
inline void Matrix4T::GetVectorComponents(Vector3& vUp, Vector3& vOut, Vector3& vRight)
{
	vRight.Set(m_Single[0], m_Single[4], m_Single[8]);
	vUp.Set(m_Single[1], m_Single[5], m_Single[9]);
	vOut.Set(m_Single[2], m_Single[6], m_Single[10]);
}

template <class T>
inline bool Matrix4T::Invert(Matrix4T& mResult) const
{
	const T c_fTiny = 1.0e-20f;

	T fA0 = m_Single[ 0] * m_Single[ 5] - m_Single[ 1] * m_Single[ 4];
	T fA1 = m_Single[ 0] * m_Single[ 6] - m_Single[ 2] * m_Single[ 4];
	T fA2 = m_Single[ 0] * m_Single[ 7] - m_Single[ 3] * m_Single[ 4];
	T fA3 = m_Single[ 1] * m_Single[ 6] - m_Single[ 2] * m_Single[ 5];
	T fA4 = m_Single[ 1] * m_Single[ 7] - m_Single[ 3] * m_Single[ 5];
	T fA5 = m_Single[ 2] * m_Single[ 7] - m_Single[ 3] * m_Single[ 6];
	T fB0 = m_Single[ 8] * m_Single[13] - m_Single[ 9] * m_Single[12];
	T fB1 = m_Single[ 8] * m_Single[14] - m_Single[10] * m_Single[12];
	T fB2 = m_Single[ 8] * m_Single[15] - m_Single[11] * m_Single[12];
	T fB3 = m_Single[ 9] * m_Single[14] - m_Single[10] * m_Single[13];
	T fB4 = m_Single[ 9] * m_Single[15] - m_Single[11] * m_Single[13];
	T fB5 = m_Single[10] * m_Single[15] - m_Single[11] * m_Single[14];

	T fDet = fA0 * fB5 - fA1 * fB4 + fA2 * fB3 + fA3 * fB2 - fA4 * fB1 + fA5 * fB0;
	if (fabs(fDet) <= c_fTiny)
		return false;

	mResult.SetIdentity( );
	mResult.m_Single[ 0] =  m_Single[ 5] * fB5 - m_Single[ 6] * fB4 + m_Single[ 7] * fB3;
	mResult.m_Single[ 4] = -m_Single[ 4] * fB5 + m_Single[ 6] * fB2 - m_Single[ 7] * fB1;
	mResult.m_Single[ 8] =  m_Single[ 4] * fB4 - m_Single[ 5] * fB2 + m_Single[ 7] * fB0;
	mResult.m_Single[12] = -m_Single[ 4] * fB3 + m_Single[ 5] * fB1 - m_Single[ 6] * fB0;
	mResult.m_Single[ 1] = -m_Single[ 1] * fB5 + m_Single[ 2] * fB4 - m_Single[ 3] * fB3;
	mResult.m_Single[ 5] =  m_Single[ 0] * fB5 - m_Single[ 2] * fB2 + m_Single[ 3] * fB1;
	mResult.m_Single[ 9] = -m_Single[ 0] * fB4 + m_Single[ 1] * fB2 - m_Single[ 3] * fB0;
	mResult.m_Single[13] =  m_Single[ 0] * fB3 - m_Single[ 1] * fB1 + m_Single[ 2] * fB0;
	mResult.m_Single[ 2] =  m_Single[13] * fA5 - m_Single[14] * fA4 + m_Single[15] * fA3;
	mResult.m_Single[ 6] = -m_Single[12] * fA5 + m_Single[14] * fA2 - m_Single[15] * fA1;
	mResult.m_Single[10] =  m_Single[12] * fA4 - m_Single[13] * fA2 + m_Single[15] * fA0;
	mResult.m_Single[14] = -m_Single[12] * fA3 + m_Single[13] * fA1 - m_Single[14] * fA0;
	mResult.m_Single[ 3] = -m_Single[ 9] * fA5 + m_Single[10] * fA4 - m_Single[11] * fA3;
	mResult.m_Single[ 7] =  m_Single[ 8] * fA5 - m_Single[10] * fA2 + m_Single[11] * fA1;
	mResult.m_Single[11] = -m_Single[ 8] * fA4 + m_Single[ 9] * fA2 - m_Single[11] * fA0;
	mResult.m_Single[15] =  m_Single[ 8] * fA3 - m_Single[ 9] * fA1 + m_Single[10] * fA0;

	T fInvDet = 1.0f / fDet;
	mResult.m_Single[ 0] *= fInvDet;
	mResult.m_Single[ 1] *= fInvDet;
	mResult.m_Single[ 2] *= fInvDet;
	mResult.m_Single[ 3] *= fInvDet;
	mResult.m_Single[ 4] *= fInvDet;
	mResult.m_Single[ 5] *= fInvDet;
	mResult.m_Single[ 6] *= fInvDet;
	mResult.m_Single[ 7] *= fInvDet;
	mResult.m_Single[ 8] *= fInvDet;
	mResult.m_Single[ 9] *= fInvDet;
	mResult.m_Single[10] *= fInvDet;
	mResult.m_Single[11] *= fInvDet;
	mResult.m_Single[12] *= fInvDet;
	mResult.m_Single[13] *= fInvDet;
	mResult.m_Single[14] *= fInvDet;
	mResult.m_Single[15] *= fInvDet;

	return true;
}

template <class T>
inline void Matrix4T::Multiply4f(const T In[4], T Result[4]) const
{
	Result[0] = m_RowCol[0][0] * In[0] + m_RowCol[0][1] * In[1] + m_RowCol[0][2] * In[2] + m_RowCol[0][3] * In[3];
	Result[1] = m_RowCol[1][0] * In[0] + m_RowCol[1][1] * In[1] + m_RowCol[1][2] * In[2] + m_RowCol[1][3] * In[3];
	Result[2] = m_RowCol[2][0] * In[0] + m_RowCol[2][1] * In[1] + m_RowCol[2][2] * In[2] + m_RowCol[2][3] * In[3];
	Result[3] = m_RowCol[3][0] * In[0] + m_RowCol[3][1] * In[1] + m_RowCol[3][2] * In[2] + m_RowCol[3][3] * In[3];
}

template <class T>
inline void Matrix4T::RotateX(T Radians)
{
	T fCosine = cosf(Radians);
	T fSine = sinf(Radians);

	Matrix4T mTmp;
	mTmp.m_RowCol[1][1] = fCosine;
	mTmp.m_RowCol[1][2] = fSine;
	mTmp.m_RowCol[2][1] = -fSine;
	mTmp.m_RowCol[2][2] = fCosine;

	// this function can be further optimized by hardcoding
	// the multiplication here and removing terms with 0.0 multipliers
	*this = mTmp * *this;
}

template <class T>
inline void Matrix4T::RotateY(T Radians)
{
	T fCosine = cosf(Radians);
	T fSine = sinf(Radians);

	Matrix4T mTmp;
	mTmp.m_RowCol[0][0] = fCosine;
	mTmp.m_RowCol[0][2] = -fSine;
	mTmp.m_RowCol[2][0] = fSine;
	mTmp.m_RowCol[2][2] = fCosine;

	// this function can be further optimized by hardcoding
	// the multiplication here and removing terms with 0.0 multipliers
	*this = mTmp * *this;
}

template <class T>
inline void Matrix4T::RotateZ(T Radians)
{
	T fCosine = cosf(Radians);
	T fSine = sinf(Radians);

	Matrix4T mTmp;
	mTmp.m_RowCol[0][0] = fCosine;
	mTmp.m_RowCol[1][0] = -fSine;
	mTmp.m_RowCol[0][1] = fSine;
	mTmp.m_RowCol[1][1] = fCosine;

	// this function can be further optimized by hardcoding
	// the multiplication here and removing terms with 0.0 multipliers
	*this = mTmp * *this;
}

template <class T>
inline void Matrix4T::RotateArbitrary(const Vector3& vAxis, T Radians)
{
	T s = sinf(Radians);
	T c = cosf(Radians);
	T t = 1.0f - c;

	Vector3 vNormalizedAxis(vAxis);
	vNormalizedAxis.Normalize( );
	const T& x = vNormalizedAxis.x;
	const T& y = vNormalizedAxis.y;
	const T& z = vNormalizedAxis.z;

	Matrix4T mTmp;
	mTmp.m_RowCol[0][0] = t * x * x + c;
	mTmp.m_RowCol[0][1] = t * x * y + s * z;
	mTmp.m_RowCol[0][2] = t * x * z - s * y;
	mTmp.m_RowCol[1][0] = t * x * y - s * z;
	mTmp.m_RowCol[1][1] = t * y * y + c;
	mTmp.m_RowCol[1][2] = t * y * z + s * x;
	mTmp.m_RowCol[2][0] = t * x * z + s * y;
	mTmp.m_RowCol[2][1] = t * y * z - s * x;
	mTmp.m_RowCol[2][2] = t * z * z + c;

	*this = mTmp * *this;
}

template <class T>
inline void Matrix4T::Scale(T x, T y, T z)
{
	Matrix4T mTmp;

	mTmp.m_RowCol[0][0] = x;
	mTmp.m_RowCol[1][1] = y;
	mTmp.m_RowCol[2][2] = z;

	*this = mTmp * *this;
}

template <class T>
inline void Matrix4T::Scale(const Vector3& vScale)
{
	Scale(vScale.x, vScale.y, vScale.z);
}


inline void Matrix4T::Translate(T x, T y, T z)
{
	Matrix4T mTmp;

	mTmp[12] = x;
	mTmp[13] = y;
	mTmp[14] = z;

	*this = mTmp * *this;
}

template <class T>
inline void Matrix4T::Translate(const Vector3& vTranslate)
{
	Translate(vTranslate.x, vTranslate.y, vTranslate.z);
}


template <class T> inline void MatSwap(T& tA, T& tB)
{
	T tTemp = tA;
	tA = tB; 
	tB = tTemp;
}

template <class T>
inline void Matrix4T::Transpose(Matrix4T& mResult) const
{
	mResult = *this;

	MatSwap(mResult.m_Single[1], mResult.m_Single[4]);
	MatSwap(mResult.m_Single[2], mResult.m_Single[8]);
	MatSwap(mResult.m_Single[6], mResult.m_Single[9]);
	MatSwap(mResult.m_Single[3], mResult.m_Single[12]);
	MatSwap(mResult.m_Single[7], mResult.m_Single[13]);
	MatSwap(mResult.m_Single[11], mResult.m_Single[14]);            
}

template <class T>
inline void Matrix4T::LookAt(const Vector3& vEye, const Vector3& vCenter, const Vector3& vUp)
{
	Vector3 vF(vCenter - vEye);
	vF.Normalize( );

	Vector3 vUpPrime(vUp);
	vUpPrime.Normalize( );

	Vector3 vS = vF.Cross(vUpPrime);
	Vector3 vU = vS.Cross(vF);

	Matrix4T mTemp;
	mTemp.m_RowCol[0][0] = vS[0];
	mTemp.m_RowCol[1][0] = vS[1];
	mTemp.m_RowCol[2][0] = vS[2];

	mTemp.m_RowCol[0][1] = vU[0];
	mTemp.m_RowCol[1][1] = vU[1];
	mTemp.m_RowCol[2][1] = vU[2];

	mTemp.m_RowCol[0][2] = -vF[0];
	mTemp.m_RowCol[1][2] = -vF[1];
	mTemp.m_RowCol[2][2] = -vF[2];

	*this = *this * mTemp;

	Translate(-vEye);
}

template <class T>
inline void Matrix4T::Ortho(T fLeft, T fRight, T fBottom, T fTop, T fNear, T fFar, bool bOpenGL)
{
	Matrix4T mTemp;
	if (bOpenGL)
	{
		// mimic glOrtho
		mTemp.m_Single[0] = 2.0f / (fRight - fLeft);
		mTemp.m_Single[5] = 2.0f / (fTop - fBottom);
		mTemp.m_Single[10] = -2.0f / (fFar - fNear);
		mTemp.m_Single[12] = -(fRight + fLeft) / (fRight - fLeft);
		mTemp.m_Single[13] = -(fTop + fBottom) / (fTop - fBottom);
		mTemp.m_Single[14] = -(fFar + fNear) / (fFar - fNear);
		mTemp.m_Single[15] = 1.0f;
	}
	else
	{
		// as defined in "Real-Time Rendering" by Akenine-Moller & Eric Haines
		//mTemp.m_Single[0] = 2.0f / (fRight - fLeft);
		//mTemp.m_Single[5] = 2.0f / (fTop - fBottom);
		//mTemp.m_Single[10] = -1.0f / (fFar - fNear);
		//mTemp.m_Single[12] = -(fRight + fLeft) / (fRight - fLeft);
		//mTemp.m_Single[13] = -(fTop + fBottom) / (fTop - fBottom);
		//mTemp.m_Single[14] = -fNear / (fFar - fNear);
		//mTemp.m_Single[15] = 1.0f;

		// as defined in D3DXMatrixOrthoOffCenterRH documentation
		mTemp.m_Single[0] = 2.0f / (fRight - fLeft);
		mTemp.m_Single[5] = 2.0f / (fTop - fBottom);
		mTemp.m_Single[10] = 1.0f / (fNear - fFar);
		mTemp.m_Single[12] = (fLeft + fRight) / (fLeft - fRight);
		mTemp.m_Single[13] = (fTop + fBottom) / (fBottom - fTop);
		mTemp.m_Single[14] = fNear / (fNear - fFar);
		mTemp.m_Single[15] = 1.0f;
	}

	*this = *this * mTemp;
}

inline void Matrix4T::Frustum(T fLeft, T fRight, T fBottom, T fTop, T fNear, T fFar)
{
	Matrix4T mTemp;

	T a = (fRight + fLeft) / (fRight - fLeft);
	T b = (fTop + fBottom) / (fTop - fBottom);
	T c = -(fFar + fNear) / (fFar - fNear);
	T d = -(2.0f * (fFar * fNear)) / (fFar - fNear);

	mTemp.m_Single[0] = 2.0f * fNear / (fRight - fLeft);
	mTemp.m_Single[5] = 2.0f * fNear / (fTop - fBottom);
	mTemp.m_Single[8] = a;
	mTemp.m_Single[9] = b;
	mTemp.m_Single[10] = c;
	mTemp.m_Single[11] = -1.0f;
	mTemp.m_Single[14] = d;
	mTemp.m_Single[15] = 0.0f;

	*this = *this * mTemp;
}

template <class T>
inline void Matrix4T::Perspective(T fFieldOfView, T fAspectRatio, T fNear, T fFar)
{
	Matrix4T mTemp;

	T f = 1.0f / tan(0.5f * fFieldOfView);

	mTemp.m_Single[0] = f / fAspectRatio;
	mTemp.m_Single[5] = f;
	mTemp.m_Single[10] = (fFar + fNear) / (fNear - fFar);
	mTemp.m_Single[11] = -1.0f;
	mTemp.m_Single[14] = 2.0f * fFar * fNear / (fNear - fFar);
	mTemp.m_Single[15] = 0.0f;

	*this = *this * mTemp;
}

template <class T>
inline void Matrix4T::GetEulerAngles( T &x, T &y, T &z)
{
	if(m_RowCol[2][1]>1)
		m_RowCol[2][1]=1;
	if(m_RowCol[2][1]<-1)
		m_RowCol[2][1]=-1;
	x=asin(m_RowCol[2][1]);
	const double epsilon=0.01;
	if(x+epsilon<(3.1415926535/2))
	{
		if(x-epsilon>(-3.1415926535/2))
		{
			z=atan2(-m_RowCol[0][1],m_RowCol[1][1]);
			y=atan2(-m_RowCol[2][0],m_RowCol[2][2]);
		}
		else
		{
			z=-atan2(m_RowCol[0][2],m_RowCol[0][0]);
			y=0;
		}
	}
	else
	{
		z=atan2(m_RowCol[0][2],m_RowCol[0][0]);
		y=0;
	}

	x=-x;
	y=-y;
	z=-z;
}

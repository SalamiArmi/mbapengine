template <class T>
inline Matrix3T::Matrix3T(bool SetToIdentity)
{
    if (SetToIdentity)
        SetIdentity( );
}

template <class T>
inline Matrix3T Matrix3T::operator*(const Matrix3T& In) const
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

template <class T>
inline Vector3 Matrix3T::operator*(const Vector3& In) const
{
    return Vector3(m_RowCol[0][0] * In.x + m_RowCol[0][1] * In.y + m_RowCol[0][2] * In.z,
                m_RowCol[1][0] * In.x + m_RowCol[1][1] * In.y + m_RowCol[1][2] * In.z,
                m_RowCol[2][0] * In.x + m_RowCol[2][1] * In.y + m_RowCol[2][2] * In.z);
}

template <class T>
inline bool Matrix3T::operator==(const Matrix3T& In) const
{
    return (memcmp(m_Single, In.m_Single, 9 * sizeof(T)) == 0);
}
template <class T>

inline bool Matrix3T::operator!=(const Matrix3T& In) const
{
    return (memcmp(m_Single, In.m_Single, 9 * sizeof(T)) != 0);
}

template <class T>
inline void Matrix3T::SetIdentity(void)
{
    memset(m_Single, 0, 9 * sizeof(T));
    m_Single[0] = m_Single[4] = m_Single[8] = 1.0f;                   
}

template <class T>
inline void Matrix3T::RotateX(T Radians)
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

template <class T>
inline void Matrix3T::RotateY(T Radians)
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

template <class T>
inline void Matrix3T::RotateZ(T Radians)
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

template <class T>
inline void Matrix3T::RotateArbitrary(const Vector3& vAxis, T Radians)
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

template <class T>
inline void Matrix3T::Scale(T x, T y, T z)
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

template <class T>
inline void Matrix3T::Scale(const Vector3& vScale)
{
    Scale(vScale.x, vScale.y, vScale.z);
}
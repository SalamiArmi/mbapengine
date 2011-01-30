template <class T>
inline Vector3T::Vector3T( ) :
    x(0.0f),
    y(0.0f),
    z(0.0f)
{
}

template <class T>
inline Vector3T::Vector3T(T _x, T _y, T _z) :
    x(_x),
    y(_y),
    z(_z)
{
}

template <class T>
inline Vector3T::Vector3T(const T Pos[3]) :
    x(afPos[0]),
    y(afPos[1]),
    z(afPos[2])
{
}

template <class T>
inline Vector3T::operator T*()
{
    return &x;
}

template <class T>
inline Vector3T::operator const T*() const
{
    return &x;
}

template <class T>
inline bool Vector3T::operator<(const Vector3T& In) const
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

template <class T>
inline bool Vector3T::operator==(const Vector3T& In) const
{
    return (x == In.x && y == In.y && z == In.z);
}

template <class T>
inline bool Vector3T::operator!=(const Vector3T& In) const
{
    return (x != In.x || y != In.y || z != In.z);    
}

template <class T>
inline Vector3T Vector3T::operator-(const Vector3T& In) const
{
    return Vector3T(x - In.x, y - In.y, z - In.z);
}

template <class T>
inline Vector3T Vector3T::operator+(const Vector3T& In) const
{
    return Vector3T(x + In.x, y + In.y, z + In.z);
}

template <class T>
inline Vector3T Vector3T::operator+=(const Vector3T& In)
{
    x += In.x;
    y += In.y;
    z += In.z;

    return *this;
}

template <class T>
inline Vector3T Vector3T::operator*(const Vector3T& In) const
{
    return Vector3T(x * In.x, y * In.y, z * In.z);
}

template <class T>
inline Vector3T Vector3T::operator*=(const Vector3T& In)
{
    x *= In.x;
    y *= In.y;
    z *= In.z;

    return *this;
}

template <class T>
inline Vector3T Vector3T::operator*(T Scale) const
{
    return Vector3T(x * Scale, y * Scale, z * Scale);
}

template <class T>
inline Vector3T Vector3T::operator*=(T Scale)
{
    x *= Scale;
    y *= Scale;
    z *= Scale;

    return *this;
}

template <class T>
inline Vector3T operator * ( T Scale, const class Vector3T& v )
{
	return Vector3T(v.x * Scale, v.y * Scale, v.z * Scale);
}

template <class T>
inline Vector3T Vector3T::operator-() const
{
    return Vector3T(-x, -y, -z);
}

template <class T>
inline Vector3T Vector3T::operator -=(const Vector3T& In)
{
	// subtraction
	x -= In.x;
	y -= In.y;
	z -= In.z;

	return *this;
}

inline Vector3T Vector3T::operator / (T Scalar) const
{
	return Vector3T(x / Scalar, y / Scalar, z / Scalar);
}

template <class T>
inline Vector3T& Vector3T::operator /= (T Scalar)
{
	x /= Scalar;
	y /= Scalar;
	z /= Scalar;
	return *this;
}

template <class T>
inline void Vector3T::Set(T _x, T _y, T _z)
{
    x = _x;
    y = _y;
    z = _z;
}

template <class T>
inline void Vector3T::LinCombVector3( const Vector3T& Pos, const Vector3T& Dir, const double t) 
{
	int i;
	for(i = 0; i < 3; i++) {
		this->operator[](i) = Pos[i]+(T)(t)*Dir[i];
	}
}

template <class T>
inline Vector3T Vector3T::Cross(const Vector3T& In) const
{
    return Vector3T(y * In.z - z * In.y, z * In.x - x * In.z, x * In.y - y * In.x);
}

template <class T>
inline T Vector3T::Distance(const Vector3T& In) const
{
    return ((*this - In).Magnitude( ));    
}

template <class T>
inline T Vector3T::DistanceSquared(const Vector3T& In) const
{
    return ((*this - In).MagnitudeSquared( )); 
}


template <class T>
inline T Vector3T::Dot(const Vector3T& In) const
{
    return (x * In.x + y * In.y + z * In.z); 
}

template <class T>
inline T Vector3T::Magnitude() const
{
    return T(sqrt(MagnitudeSquared( )));
}

template <class T>
inline T Vector3T::MagnitudeSquared() const
{
    return (x * x + y * y + z * z); 
}

template <class T>
inline void Vector3T::Normalize()
{
    T fMagnitude = Magnitude( );
    if (fMagnitude > FLT_EPSILON)
        Scale(1.0f / fMagnitude);
}

template <class T>
inline void Vector3T::Scale(T Scale)
{
    x *= Scale;
    y *= Scale;
    z *= Scale;
}

template <class T>
inline T Vector3T::Angle(Vector3T& Compare)
{
	T dotproduct = Dot(Compare);
	T lengtha = MagnitudeSquared();
	T lengthb = Compare.MagnitudeSquared();
	T result = acos( dotproduct / (lengtha * lengthb) );
	 
	if( dotproduct < 0.0f )
	{
		if( result > 0.0f )
			result += c_fPi;
		else
			result -= c_fPi;
	}
	return result;
}

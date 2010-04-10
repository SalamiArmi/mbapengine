#ifndef ZARANTAS_Vector3_HEADER
#define ZARANTAS_Vector3_HEADER

#include <cmath>

namespace OOS
{
	const float PI = 3.14159265f;
	const float TO_RAD = PI / 180.0f;
	const float TO_DEG = 180.0f / PI;

	template <typename T> class Vector3T
	{
	public:
		typedef T type;

		//Data
		T x;
		T y;
		T z;

		inline Vector3T()
		{
		}

		//Construtors
		inline Vector3T(const T X, const T Y, const T Z) : x(X), y(Y), z(Z)
		{
		}

		inline Vector3T(const Vector3T &NewVector3T): x(NewVector3T.x),y(NewVector3T.y),z(NewVector3T.z)
		{
		}

		/*explicit inline Vector3T(const Vector3T xyz) : x(xyz), y(xyz), z(xyz)
		{
		}*/

		//Destructor
		inline ~Vector3T()
		{
		}

		//Operator Overloads
		//equals to 
		inline bool operator == (const Vector3T &NewVector3T)
		{
			if (x == NewVector3T.x && y == NewVector3T.y && z == NewVector3T.z) //Check if two Vector3Tors are equal
			{
				return true; //Continue
			}
			return false; //Exit 
		}

		//Not equal to 
		bool operator != (const Vector3T NewVector3T)
		{
			return x!=NewVector3T.x || y!=NewVector3T.y || y!=NewVector3T.y;
		}

		inline Vector3T operator += (const Vector3T &NewVector3T)
		{
			x += NewVector3T.x;
			y += NewVector3T.y;
			z += NewVector3T.z;
			return(*this);
		}

		inline Vector3T operator *=(const Vector3T &NewVector3T)
		{
			x *= NewVector3T.x;
			y *= NewVector3T.y;
			z *= NewVector3T.z;
			return(*this);
		}

		inline Vector3T operator /=(const Vector3T &NewVector3T)
		{
			x /= NewVector3T.x;
			y /= NewVector3T.y;
			z /= NewVector3T.z;
			return(*this);
		}

		inline Vector3T& operator -=(const Vector3T &NewVector3T)
		{
			x -= NewVector3T.x;
			y -= NewVector3T.y;
			z -= NewVector3T.z;
			return(*this);
		} 

		inline Vector3T& operator + (const Vector3T &NewVector3T)
		{
			x += NewVector3T.x;
			y += NewVector3T.y;
			z += NewVector3T.z;

			return (*this);
		}

		inline Vector3T operator * ( const T Scalar ) const
		{
			return Vector3T(
				x * fScalar,
				y * fScalar,
				z * fScalar);
		}

		inline Vector3T& operator * (const Vector3T& NewVector3T) const
		{
			return Vector3T(
				x * NewVector3T.x,
				y * NewVector3T.y,
				z * NewVector3T.z);
		}

		inline Vector3T& operator / (const Vector3T& NewVector3T) const
		{
			return Vector3T(
				x / NewVector3T.x,
				y / NewVector3T.y,
				z / NewVector3T.z);
		}

		inline Vector3T& operator -(const Vector3T &NewVector3T) //Minus Vector3Tors
		{
			x -= NewVector3T.x;
			y -= NewVector3T.y;
			z -= NewVector3T.z;

			return *this;
		}

		inline Vector3T& operator -() const 
		{
			return Vector3T(-x, -y, -z);
		}

		inline Vector3T operator [] (unsigned int i) const
		{
			return *(&x+i);
		}

		inline Vector3T& operator [] (unsigned int i)
		{
			return *(&x+i);
		}

		inline void normalise()
		{
			T length = sqrt(x*x + y*y + z*z);
			x /= length;
			y /= length;
			z /= length;
		}

		inline void fill(const T& value)
		{
			x = y = z = value;
		}

		inline void Zero()
		{
			fill(0.0f);
		}

		inline T dot(const Vector3T &NewVector3T) //Finding the dot product then returning
		{
			return x * NewVector3T.x + y * NewVector3T.y + z * NewVector3T.z;
		}

		inline T Angle(const Vector3T &NewVector3T) //Finding the angle then making it Degrees
		{
			T Angle;
			Angle = (x * NewVector3T.x + y * NewVector3T.y + z * NewVector3T.z) * TO_DEG;
			return Angle;
		}

		inline const T lengthSquared()
		{
			return dot(*this);
		}

		inline Vector3T Cross(const Vector3T &NewVector3T) //Cross product of a Vector3Tor
		{
			return Vector3T(y * NewVector3T.z - z * NewVector3T.y, z * NewVector3T.x - x * NewVector3T.z, x * NewVector3T.y - y * NewVector3T.x);
		}

		inline T length() //Finding the Length
		{
			return sqrtf(lengthSquared());
		}

		inline T length(const Vector3T &NewVector3T) //Finding the Length
		{
			return sqrt(NewVector3T.x * NewVector3T.x + NewVector3T.y * NewVector3T.y + NewVector3T.z * NewVector3T.z); 
		}

		inline Vector3T Vector3Torscalar(T &Factor) //Scaling the Vector3Tor by a supplied Factor
		{
			x *= Factor;
			y *= Factor;
			z *= Factor;
			return this;
		}
	};

	typedef Vector3T<float> Vector3;
}
#endif 
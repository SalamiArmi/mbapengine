#ifndef _VECTOR2_HEADER_
#define _VECTOR2_HEADER_

#include "math.h"

namespace OOS
{
	template <typename T>
	class vector2T
	{
	public:
		__forceinline vector2T()
		:
		x(0.0),
		y(0.0)
		{
		}

		__forceinline vector2T(const T scalar)
		:
		x(scalar),
		y(scalar)
		{
		}

		__forceinline vector2T(const T _x, const T _y)
		{
			x = _x;
			y = _y;
		}

		__forceinline vector2T(const T inArray[2])
		{
			x = Array[0];
			y = Array[1];
		}

		__forceinline vector2T(const vector2T &copy)
		{
			*this = copy;
		}

		__forceinline ~vector2T()
		{
		}

		__forceinline T* ptr()
		{
			return &x;
		}

		//Pointer accessor for direct copying
		__forceinline T* const ptr() const
		{
			return &x;
		}

		__forceinline const T dot(const vector2T &rhs) const
		{
			return ((x * rhs.x) + (y * rhs.y));
		}

		// Returns the squared length of a vector as a float (more efficient than length())
		__forceinline const T lengthSquared() const
		{
			return dot(*this);
		}

		// Returns the length of a vector as a float
		__forceinline const T length() const
		{
			return sqrtf(lengthSquared());
		}

		// Makes the length of the vector equal to one
		__forceinline void normalise() 
		{
			*this /= length();
		}

		// Returns the results of normalise without effecting the underlying container
		__forceinline const vector2T normaliseCopy() const
		{
			vector2T result = *this;
			result /= result.length();
			return result;
		}

		//Returns a vector at a point half way between this and the passed in vector.
		__forceinline const T midPoint( const vector2T& rhs ) const
        {
            return vector2T(
                (x + rhs.x) * 0.5, (y + rhs.y) * 0.5);
        }

		__forceinline void SetCrossZ(const vector2T& rhs, const float a_z)
		{
			x = a_z * rhs.y;
			y = -a_z * rhs.x;
		}

		__forceinline vector2T &operator +=(const vector2T &rhs)
		{
			x += rhs.x;
			y += rhs.y;
			return *this;
		}

		__forceinline vector2T &operator -=(const vector2T &rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
			return *this;
		}

		__forceinline vector2T &operator *=(const vector2T &rhs)
		{
			x *= rhs.x;
			y *= rhs.y;
			return *this;
		}

		__forceinline vector2T &operator /=(const vector2T &rhs)
		{
			x /= rhs.x;
			y /= rhs.y;
			return *this;
		}

		__forceinline const vector2T operator -(void) const
		{
			return vector2T(-x, -y);
		}

		__forceinline const vector2T operator +(const vector2T &rhs) const
		{
			return vector2T(x + rhs.x, y + rhs.y);
		}

		__forceinline const vector2T operator -(const vector2T &rhs) const
		{
			return vector2T(x - rhs.x, y - rhs.y);
		}

		__forceinline const vector2T operator *(const vector2T &rhs) const
		{
			return vector2T(x * rhs.x, y * rhs.y);
		}

		__forceinline const vector2T operator /(const vector2T &rhs) const
		{
			return vector2T(x / rhs.x, y / rhs.y);
		}

		__forceinline const vector2T operator /(const T &rhs) const
		{
			return vector2T(x / rhs, y / rhs);
		}

		//equals to 
		__forceinline bool operator == (const vector2T &rhs)
		{
			if (x == rhs.x && y == rhs.y) //Check if two Vector3Tors are equal
			{
				return true; //Continue
			}
			return false; //Exit 
		}

		//Not equal to 
		__forceinline bool operator != (const vector2T rhs)
		{
			return x!=rhs.x || y!=rhs.y;
		}

		T x, y;
	};

	typedef vector2T<float> Vector2;
}

#endif //_VECTOR2_HEADER_
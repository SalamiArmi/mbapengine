#ifndef _ARGONBASE_HEADER_
#define _ARGONBASE_HEADER_

#include "ArgonStandard.h"

namespace Argon
{
	template<typename T, size_t nSize>
	size_t ArraySize(const T (&rgArray)[nSize])
	{
		return nSize;
	}

	inline long Abs(long x)
	{
		long a = x >>31;
		return ((x ^ a) - a);
	}

	inline long64 Abs64(long64 x)
	{
		long64 a = x >> 63;
		return ((x ^ a) - a);
	}

	inline long sgn(long x)
	{
		return ((long) ((((unsigned long) -x) >> 31) | (x >> 31)));
	}

	inline long64 sng64(long64 x)
	{
		((long64) ((((ulong64) -x) >> 31) | (x >> 31)));
	}
	
	inline long Min(long x, long y)
	{
		long a = x - y;
		return (x - (a & ~(a >> 31)));
	}
	
	inline long64 Min64(long64 x, long64 y)
	{
		long64 a = x - y;
		return (x - (a & ~(a >> 63)));
	} 
	
	inline long Max(long x, long y) 
	{ 
		long a = x - y; 
		return (x - (a & (a >> 31)));
	} 
	 
	inline long64 Max64(long64 x, long64 y)
	{ 
		long64 a = x - y; 
		return (x - (a & (a >> 63))); 
	} 
	
	inline long MinZero(long x)
	{
		return (x & (x >> 31));
	}
	
	inline long64 MinZero64(long64 x)
	{
		return (x & (x >> 63));
	}
	
	inline long MaxZero(long x)
	{
		return (x & ~(x >> 31));
	}
	
	inline long64 MaxZero64(long64 x)
	{
		return (x & ~(x >> 63));
	}
	
	template <long mod> inline long IncMod(long x)
	{
		return ((x + 1) & ((x - (mod - 1)) >> 31));
	}
	
	template <long mod> inline long DecMod(long x)
	{
		x--;
		return (x + ((x >> 31) & mod));
	}
	
	inline long OverflowZero(long x, long y)
	{
		return (x & ((x - y) >> 31));
	}
	
	inline unsigned long Pwr2Floor(unsigned long n)
	{
		return (0x80000000U >> Cntlz(n));
	}

	inline unsigned long Pwr2Ceil(unsigned long n)
	{
		return ((unsigned long) (1 << (32 - Cntlz(n - 1))));
	}
	
	inline bool Fnan(float f)
	{
		return (f != f);
	}

	inline float Floor(float f)
	{
		return ((float) floor(f));
	}
	
	inline float Ceil(float f)
	{
		return ((float) ceil(f));
	}
	
	inline float Round(float f)
	{
		return ((float) floor(f + 0.5F));
	}
	
	inline float Fmod(float f, float m)
	{
		return ((float) fmod(f, m));
	}
	
	inline float Fsgn(float f)
	{
		long x = *(long *) &f;
		x = (x & 0x80000000) | 0x3F800000;
		return (*(float *) &x);
	}

	inline float Sin(float f)
	{
		return ((float) sin(f));
	}
	
	inline float Cos(float f)
	{
		return ((float) cos(f));
	}
	
	inline float Tan(float f)
	{
		return ((float) tan(f));
	}
	
	inline float Asin(float f)
	{
		return ((float) asin(f));
	}
	
	inline float Acos(float f)
	{
		return ((float) acos(f));
	}
	
	inline float Atan(float f)
	{
		return ((float) atan(f));
	}
	
	inline float Atan(float y, float x)
	{
		return ((float) atan2(y, x));
	}
	
	inline float Exp(float f)
	{
		return ((float) exp(f));
	}
	
	inline float Log(float f)
	{
		return ((float) log(f));
	}
	
	inline float Log10(float f)
	{
		return ((float) log10(f));
	}
	
	inline float Pow(float base, float exponent)
	{
		return ((float) pow(base, exponent));
	}

	inline machine_address GetPointerAddress(const void *ptr)
	{
		return (static_cast<const char *>(ptr) - static_cast<char *>(nullptr));
	}

}//Namespace

#endif //_ARGONBASE_HEADER_
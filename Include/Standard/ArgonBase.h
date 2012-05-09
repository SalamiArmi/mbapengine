#ifndef _ARGONBASE_HEADER_
#define _ARGONBASE_HEADER_

#include "ArgonStandard.h"
#include "Math.h"

#include "limits.h"

namespace 
{
	unsigned long hex_7F800000		= 0x7F800000;
	unsigned long hex_FF800000		= 0xFF800000;
}

namespace Argon
{
	const float infinity =				*(float *) &hex_7F800000;
	const float minus_infinity =		*(float *) &hex_FF800000;

	const float one_over_3 =			1.0F / 3.0F;
	const float one_over_6 =			1.0F / 6.0F;
	const float one_over_7 =			1.0F / 7.0F;
	const float one_over_12 =			1.0F / 12.0F;
	const float one_over_31 =			1.0F / 31.0F;
	const float one_over_32 =			1.0F / 32.0F;
	const float one_over_60 =			1.0F / 60.0F;
	const float one_over_63 =			1.0F / 63.0F;
	const float one_over_64 =			1.0F / 64.0F;
	const float one_over_127 =			1.0F / 127.0F;
	const float one_over_128 =			1.0F / 128.0F;
	const float one_over_255 =			1.0F / 255.0F;
	const float one_over_256 =			1.0F / 256.0F;
	const float one_over_32767 =		1.0F / 32767.0F;
	const float one_over_32768 =		1.0F / 32768.0F;
	const float one_over_65535 =		1.0F / 65535.0F;
	const float one_over_65536 =		1.0F / 65536.0F;

	const float pi =					3.1415926535897932384626433832795F;
	const float two_pi =				6.2831853071795864769252867665590F;
	const float four_pi =				12.566370614359172953850573533118F;
	const float three_pi_over_2 =		4.7123889803846898576939650749193F;
	const float three_pi_over_4 = 		2.3561944901923449288469825374596F;
	const float two_pi_over_3 =			2.0943951023931954923084289221863F;
	const float four_pi_over_3 = 		4.1887902047863909846168578443727F;
	const float two_pi_over_15 = 		0.41887902047863909846168578443727F;
	const float four_pi_over_15 = 		0.83775804095727819692337156887453F;
	const float pi_over_2 =				1.5707963267948966192313216916398F;
	const float pi_over_3 =				1.0471975511965977461542144610932F;
	const float pi_over_4 =				0.78539816339744830961566084581988F;
	const float pi_over_6 =				0.52359877559829887307710723054658F;
	const float pi_over_8 =				0.39269908169872415480783042290994F;
	const float pi_over_12 =			0.26179938779914943653855361527329F;
	const float pi_over_20 =			0.15707963267948966192313216916398F;
	const float pi_over_240 =			0.01308996938995747182692768076366F;
	const float one_over_pi =			1.0F / pi;
	const float two_over_pi =			2.0F / pi;
	const float one_over_two_pi =		1.0F / two_pi;
	const float one_over_four_pi =		1.0F / four_pi;

	const float sqrt_2 =				1.4142135623730950488016887242097F;
	const float sqrt_2_over_2 =			0.70710678118654752440084436210485F;
	const float sqrt_2_over_3 =			0.47140452079103168293389624140323F;
	const float sqrt_3 =				1.7320508075688772935274463415059F;
	const float sqrt_3_over_2 =			0.86602540378443864676372317075294F;
	const float sqrt_3_over_3 =			0.57735026918962576450914878050196F;

	const float ln_2 =					0.69314718055994530941723212145818F;
	const float one_over_ln_2 =			1.4426950408889634073599246810019F;

	const float gravity =				-9.8e-6F;
	const float half_gravity =			-4.9e-6F;
	const float degrees =				180.0F * one_over_pi;

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
		return (static_cast<const char *>(ptr) - static_cast<char *>(NULL));
	}

	inline float Sqrt(float f) 
	{ 
		if (f == 0.0F) return (0.0F);
		 
		unsigned long i = 0x5F375A86 - (*reinterpret_cast<unsigned long *>(&f) >> 1); 
		float r = *reinterpret_cast<float *>(&i); 
		r = 0.5F * r * (3.0F - f * r * r); 
		r = 0.5F * r * (3.0F - f * r * r);
		return (r * f);
	}

	inline float InverseSqrt(float f)
	{
		if (f == 0.0F) return (infinity);
		
		unsigned long i = 0x5F375A86 - (*reinterpret_cast<unsigned long *>(&f) >> 1);
		float r = *reinterpret_cast<float *>(&i);
		r = 0.5F * r * (3.0F - f * r * r);
		r = 0.5F * r * (3.0F - f * r * r);
		return (r);
	}

}//Namespace

#endif //_ARGONBASE_HEADER_
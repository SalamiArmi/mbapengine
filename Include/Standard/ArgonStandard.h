///////////////////////////////////////////////////////////////////////////////////
//
//									Argon Engine
//
//		Standard.h
//
//		Description: All types or standard types used throughout the Argon Engine
//
//
///////////////////////////////////////////////////////////////////////////////////


#ifndef _ARGONSTANDARD_HEADER_
#define _ARGONSTANDARD_HEADER_

#include <assert.h>

namespace Argon
{

//////////////////////////////////////////////////////////
// Argon Variable Types
#	if defined ArgonX64
		typedef _w64 unsigned long	ulong;
#	else 
		typedef unsigned long		ulong;
#	endif

	typedef __int64					long64;
	typedef unsigned __int64		ulong64;

	typedef unsigned long			machine_address;

	typedef unsigned short			ushort;
	typedef unsigned int			uint;
	typedef unsigned char			uchar;
	typedef float					Real;

//////////////////////////////////////////////////////////
// Argon Variable Sizes
#	define ArgonCharBit				8
#	define ArgonMinSignedChar		-128
#	define ArgonMaxSignedChar		127
#	define ArgonMaxUChar			255
#	define ArgonMinShort			-32768
#	define ArgonMaxShort			32767
#	define ArgonMaxUShort			0xffff
#	define ArgonMinInt				-2147483648
#	define ArgonMaxInt				2147483647
#	define ArgonMaxUInt				4294967295
#	define ArgonMaxReal				3.402823466e+38F
#	define AronMinReal				(-3.402823466e+38F)

#	if defined ArgonX64
#		define ArgonLongMin			-9223372036854775808
#		define ArgonLongMax			9223372036854775807
#		define ArgonULongMax		18446744073709551615
#	else 
#		define ArgonLongMin			-2147483648
#		define ArgonLongMax			2147483647
#		define ArgonULongMax		4294967295
#	endif

#	define ArgonPI					3.14159265358979323846
#	define ArgonTwoPI				6.28318530717958647692528
#	define ArgonFeetToMETERS		0.3048f

//////////////////////////////////////////////////////////
// Argon Import Exports
#	ifndef ArgonExport
#		define ArgonExport extern "C" __declspec(dllexport)
#	endif
#	ifndef ArgonImport
#		define ArgonImport __declspec(dllimport)
#	endif
#	ifndef ArgonAPIExport
#		define ArgonAPI __declspec(dllimport)
#	else
#		define ArgonAPI __declspec(dllexport)
#	endif
#	ifndef ArgonStandardExport
#		define ArgonStandard __declspec(dllimport)
#	else
#		define ArgonStandard __declspec(dllexport)
#	endif

////////////////////////////////////////////////////////////
// Argon Inline
#	if _MSC_VER >= 1200
#		define ArgonInline __forceinline
#	else
#		define ArgonInline inline
#	endif

////////////////////////////////////////////////////////////
// Argon Assert

#	ifndef ArgonAssert
#		if _DEBUG
#			define ArgonAssert(Expression) assert(Expression)
#		else
#			define ArgonAssert(Expression)
#		endif
#	endif

////////////////////////////////////////////////////////////
// Argon NULL
#	ifndef NULL
#		define NULL 0
#	endif

////////////////////////////////////////////////////////////
// Argon FLT_EPSILON
#	ifndef FLT_EPSILON
#		define FLT_EPSILON 1.192092896e-07F
#	endif

}

#endif //_ARGONSTANDARD_HEADER_
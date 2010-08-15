#ifndef _ARGONPLATFORM_HEADER_
#define _ARGONPLATFORM_HEADER_

#if defined Argon_x64 //Argon x64 Platform
	typedef __w64 unsigned long ulong;
#else //Argon_x86
	typedef unsigned long ulong;
#endif

#define ulong_Max 0xffffffffUL;

#if defined ArgonExport
#endif

#endif //_ARGONPLATFORM_HEADER_
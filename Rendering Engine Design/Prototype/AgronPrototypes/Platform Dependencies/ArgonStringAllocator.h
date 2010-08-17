////////////////////////////////////////////////////////////////
//
//	ArgonStringAllocator.h : String Allocators
//
//	Copyright ©2010 Argon. All rights reserved.
//	Removal of this copyright notice is not permitted.
//
///////////////////////////////////////////////////////////////

#ifndef _ARGONSTRINGALLOCATOR_HEADER_
#define _ARGONSTRINGALLOCATOR_HEADER_

typedef unsigned long ulong;

namespace Argon
{
	template< typename T > class Allocator
	{
	public:
		virtual ~Allocator()
		{

		}

		virtual T* Allocate(const size_t Size) const = 0;
		virtual ulong Length(const T* String) const = 0;
	};

	class CharAllocator : Allocator<char>
	{
	public:
		CharAllocator()
		{
		}

		~CharAllocator()
		{
		}

		char* Allocate(const size_t Size) const
		{
			char* Return = new char[Size+1];
			Return[Size] = '\0'; //Null terminate String
			return Return;
		}

		inline ulong Length(const char* String) const
		{
			return strlen(String);
		}

	protected:

	};

	class WideCharacterAllocator : Allocator<wchar_t>
	{
	public:
		WideCharacterAllocator()
		{
		}

		~WideCharacterAllocator()
		{
		}

		inline wchar_t* Allocate(const size_t Size) const
		{
			wchar_t* Return = new wchar_t[Size+1];
			Return[Size] = '\0'; //Null terminate String
			return Return;
		}

		inline ulong Length(const wchar_t* String) const
		{
			ulong Len;
			for(Len = 0; String[Len] != 0; ++Len);
			return Len;
		}

	protected:

	};

} //Namespace

#endif //_ARGONSTRINGALLOCATOR_HEADER_
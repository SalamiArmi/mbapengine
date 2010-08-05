#ifndef _ARGONSTRINGALLOCATOR_HEADER_
#define _ARGONSTRINGALLOCATOR_HEADER_

typedef unsigned long ulong;

namespace Argon
{
	template< typename T > class Allocator
	{
	public:
		~Allocator();

		virtual T Allocate(size_t Size) const = 0;
		virtual ulong Length(T String) const = 0;
	};

	class CharAllocator : Allocator<char*>
	{
	public:
		CharAllocator()
		{
		}

		~CharAllocator()
		{
		}

		char* Allocate(size_t Size) const
		{
			char* Return = new char[Size+1];
			Return[Size+1] = '\0'; //Null terminate String
			return Return;
		}

		ulong Length(char* String) const
		{
			ulong Len;
			for(Len = 0; String[Len] != 0; ++Len);
			return Len;
		}

	protected:

	};

} //Namespace

#endif //_ARGONSTRINGALLOCATOR_HEADER_
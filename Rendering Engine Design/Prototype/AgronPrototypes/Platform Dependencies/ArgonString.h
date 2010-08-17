#ifndef _ARGONSTRING_HEADER_
#define _ARGONSTRING_HEADER_

#include "ArgonPlatform.h"
#include "ArgonStringAllocator.h"

#include "String.h"

namespace Argon
{
	template< typename T, typename AllocatorT > class StringT
	{
	public:

		typedef T Iterator;

		///Constructor(VOID)
		///
		///Create a new string with the defined template type
		///
		///No Params:
		StringT() : m_Allocator(new AllocatorT())
		{
		}

		///Constructor(VOID)
		///
		///Create a new string with the defined template type
		///
		///Param T: The type of string to create
		StringT( T* aString ) : m_Allocator( new AllocatorT() )
		{
			m_String = aString;
			m_Size = m_Allocator->Length(aString);
		}

		///Constructor(VOID)
		///
		///Create a String using a Bool
		///
		///Param aBool: The value to create the string from
		StringT( bool aBool )
		{
			if(aBool)
			{
				m_String = m_Allocator->Allocate(4);
				m_String[0] = "T";
				m_String[1] = "r";
				m_String[2] = "u";
				m_String[3] = "e";
			}
			else
			{
				m_String = m_Allocator->Allocate(5);
				m_String[0] = "F";
				m_String[1] = "a";
				m_String[2] = "l";
				m_String[3] = "s";
				m_String[3] = "e";
			}
			m_Size = 5;
		}

		///Constructor(VOID)
		///
		///Create a String using int
		///
		///Param aInt: The value to create the string from
		StringT( int aInt );

		///Constructor(VOID)
		///
		///Create a String using long
		///
		///Param aLong: The value to create the string from
		StringT( long aLong );

		///Constructor(VOID)
		///
		///Create a String using ulong
		///
		///Param UnsignedLong: The value to create the string from
		StringT( ulong UnsignedLong );

		///Constructor(VOID)
		///
		///Create a String using float
		///
		///Param aFloat: The value to create the string from
		StringT( float aFloat );

		///Constructor(VOID)
		///
		///Create a String using double
		///
		///Param aDouble: The value to create the string from
		StringT( double aDouble );

		///Destructor(VOID)
		///
		///Destroy the string
		///
		///No Params:
		~StringT()
		{
			delete m_Allocator;
			//delete[] m_String;
		}

		///LENGTH(ULONG)
		///
		///Get the length of the String
		///
		///No Params:
		ulong Length() const
		{
			return m_Allocator->Length(m_String);
		}

		///C_STR(LPCHAR)
		///
		///Get a C style pointer to the string
		///
		///No Params:
		char* c_str() const
		{
			char* Return = new char[ m_Size + 1 ];
			Return[m_Allocator->Length(m_String)] = '\0';

			for(ulong Index = 0; Index < m_Size; ++Index)
			{
				Return[Index] = m_String[Index];
			}
			return Return;
		}

		wchar_t* cwide_str() const
		{
			wchar_t* Return = new wchar_t[ m_Size + 1 ];
			Return[m_Allocator->Length(m_String)] = '\0';

			for(ulong Index = 0; Index < m_Size; ++Index)
			{
				Return[Index] = m_String[Index];
			}
			return Return;
		}


		bool Empty() const
		{
			const bool empty = (m_Size == 0) ? true : false;
			return empty;
		}

		///FINDSTRING(ulong)
		///
		/// Looks for the substring inside the current string
		///
		///Param str: The string to attempt to find within this string
		bool FindString( StringT<T, AllocatorT> str )
		{
			const bool Found = FindStringInString(str.m_String, m_String); 
			return Found;
		}


		T At(ulong Index)
		{
			return m_String[Index];
		}

		Iterator Begin()
		{
			return m_String[0];
		}

		Iterator End()
		{
			return m_String[m_Size];
		}

		StringT operator+( const StringT<T, AllocatorT> &str ) const
		{
			String NewString(*this);
			NewString += str;
			return NewString;
		}

		StringT operator+( const T* str ) const
		{
			String NewString(*this);
			NewString += str;
			return NewString;
		}

		StringT &operator+=(const StringT<T, AllocatorT> &str)
		{
			const ulong TotalLength = m_Allocator->Length(m_String) + str.Length();

			T* String = m_Allocator->Allocate(TotalLength);

			memcpy(String, m_String, m_Size);

			for(ulong Index = 0; Index < str.m_Size; ++Index)
				String[m_Allocator->Length(m_String) + Index] = str.m_String[Index];

			//delete m_String;
			m_String = String;
			m_Size = TotalLength-1;

			return *this;
		}

		StringT &operator+=(const T* Str)
		{
			const size_t StrLength = m_Allocator->Length(Str);
			const ulong TotalLength = StrLength + m_Size; //Total length of the 2 strings

			T* String = m_Allocator->Allocate(TotalLength);
			memcpy(String, m_String, m_Size); //Copy this string across

			for(ulong Index = 0; Index < StrLength; ++Index)
				String[m_Size + Index] = Str[Index]; //Move adding string accros

			//delete m_String;
			m_String = String;
			m_Size = TotalLength;

			return *this;
		}

		StringT &operator= (const StringT<T, AllocatorT> &Str)
		{
			T* String = m_Allocator->Allocate(Str.m_Size);

			memcpy(String, Str.m_String, Str.m_Size);

			//delete m_String;
			m_String = String;
			m_Size = Str.m_Size;

			return *this;
		}

		StringT &operator= (const T* Str)
		{
			m_Size = m_Allocator->Length(Str);

			T* String = m_Allocator->Allocate(m_Size);
			memcpy(String, Str, m_Size);

			//delete m_String;
			m_String = String;

			return *this;
		}

		bool operator==( const StringT<T, AllocatorT> &Str ) const
		{
			if ( memcmp(m_String, Str, m_Size > Str.m_Size ? m_Size : Str.m_Size) == 0 )
				return true;

			return false;
		}

		bool operator==( T* Str ) const
		{
			size_t StrLength = m_Allocator->Length(Str);
			if ( memcmp(m_String, Str, m_Size > StrLength ? m_Size : StrLength) == 0 )
				return true;

			return false;
		}

		bool operator!=( const StringT<T, AllocatorT> &Str ) const
		{
			if (memcmp(m_String, Str, m_Size > Str.m_Size ? m_Size : Str.m_Size) == 0)
				return false;

			return true;
		}

		bool operator!=( const T* Str ) const
		{
			size_t StrLength = m_Allocator->Length(Str);
			if (memcmp(m_String, Str, m_Size > StrLength ? m_Size : StrLength) == 0)
				return false;

			return true;
		}

		T& operator[] (ulong Index)
		{
			if(Index < m_Size)
				return m_String[Index];
			return "";
		}

	private:

		bool FindStringInString(T* String, T* inString, ulong Start = 0)
		{
			ulong Index = Start;
			while(Index < m_Size)
			{
				if(FindCharacter(inString[Index], m_String) < m_Size)
				{
					++Index;
					return FindStringInString(String, inString, Index);
				}
				else
				{
					return false;
				}
			}
			return false;
		}

		ulong FindCharacter(T character, T* inString)
		{
			ulong n = m_Size;
			if (n != 0) {
				const char *p = inString;

				do {
					if (*p++ == character)
						return (inString - (p - 1)) + 1;
				} while (--n != 0);
			}
			return ulong_Max;
		}


	private:
		T*				m_String;
		AllocatorT*		m_Allocator;
		ulong			m_Size;
	};

	typedef StringT< char, CharAllocator > String;
	typedef StringT< wchar_t, WideCharacterAllocator > wString;
}
#endif //_ARGONSTRING_HEADER_
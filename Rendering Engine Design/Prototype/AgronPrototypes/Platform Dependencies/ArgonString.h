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
		StringT() : m_Allocator(new AllocatorT()), m_String(0x0)
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
		///Create a String using a short
		///
		///Param aShort: The value to create the string from
		StringT( short aShort );

		///Constructor(VOID)
		///
		///Create a String using unsigned short
		///
		///Param UnsignedShort: The value to create the string from
		StringT( unsigned short UnsignedShort );

		///Constructor(VOID)
		///
		///Create a String using int
		///
		///Param aInt: The value to create the string from
		StringT( int aInt );

		///Constructor(VOID)
		///
		///Create a String using unsigned int
		///
		///Param UnsignedInt: The value to create the string from
		StringT( unsigned int UnsignedInt );

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
			//delete m_Allocator;
			//delete m_String;
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


		bool Empty()
		{
			bool empty = (m_Size == 0) ? true : false;
			return empty;
		}

		///FINDSTRING(ulong)
		///
		/// Looks for the substring inside the current string
		///
		///Param str: The string to attempt to find within this string
		ulong FindString( const StringT<T, AllocatorT> &str ) const
		{
			char *ptr = strstr(m_String, str.m_String);

			if(ptr == NULL) 
				return -1; // The substring was not found

			// The substring was found, return an index to the first character of it
			// inside the larger string
			return (int) (ptr - m_String); 
		}


		T At(ulong Index)
		{
			if(Index < Length())
				return m_String[Index];
			//return "";
		}

		Iterator Begin()
		{
			return m_String[0];
		}

		Iterator End()
		{
			return m_String[m_Size];
		}

		///
		/// The + operator appends strings in place.
		///
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

		StringT &operator+=( const StringT<T, AllocatorT> &str )
		{
			ulong TotalLength = m_Allocator->Length(m_String) + str.Length() + 1;

			T* String = m_Allocator->Allocate(TotalLength);
			String[TotalLength-1] = '\0'; //Null Terminate

			for(ulong Index = 0; Index < m_Size; ++Index)
				String[Index] = m_String[Index];

			for(ulong Index = 0; Index < str.m_Size; ++Index)
				String[m_Allocator->Length(m_String) + Index] = str.m_String[Index];

			//delete m_String;
			m_String = String;
			m_Size = TotalLength-1;

			return *this;
		}

		StringT &operator+=( const T* Str )
		{
			ulong TotalLength = m_Allocator->Length(Str) + m_Allocator->Length(m_String) + 1;

			T* String = m_Allocator->Allocate(TotalLength);
			String[TotalLength-1] = '\0'; //Null Terminate

			for(ulong Index = 0; Index < m_Size; ++Index)
				String[Index] = m_String[Index];

			for(ulong Index = 0; Index < Str.m_Size; ++Index)
				String[m_Allocator->Length(m_String) + Index] = Str[Index];

			//delete m_String;
			m_String = String;
			m_Size = TotalLength;

			return *this;
		}

		///
		/// = operator assigns a string to the value of another string
		///
		StringT &operator= ( const StringT<T, AllocatorT> &str )
		{
			ulong TotalLength = str.Length() + 1;

			T* String = m_Allocator->Allocate(TotalLength);
			String[TotalLength-1] = '\0'; //Null Terminate

			for(ulong Index = 0; Index < TotalLength-1; ++Index)
				String[Index] = m_String[Index];

			//delete m_String;
			m_String = String;
			m_Size = TotalLength-2;

			return *this;
		}

		StringT &operator= ( T* Str )
		{
			m_Size = m_Allocator->Length(Str);

			T* String = m_Allocator->Allocate(m_Size+1);
			String[m_Size] = '\0'; //Null Terminate

			for(ulong Index = 0; Index < m_Size; ++Index)
				String[Index] = Str[Index];

			//delete m_String;
			m_String = String;

			return *this;
		}

		///
		/// == compares strings for equality
		///
		bool operator==( const StringT<T, AllocatorT> &Str ) const
		{
			if(Str.m_Size != m_Size)
				return false;

			//Length is the same try digits
			for(ulong Index = 0; Index < m_Size; ++Index)
				if( m_String[Index] == Str.m_String[Index] )
					return true;

			return false;
		}

		bool operator==( const T* Str ) const
		{
			if(Str.m_Size != m_Size)
				return false;

			//Length is the same try digits
			for(ulong Index = 0; Index < m_Size; ++Index)
				if( m_String[Index] == Str[Index] )
					return true;

			return false;
		}

		///
		/// != compares strings for inequality
		///
		bool operator!=( const StringT<T, AllocatorT> &Str ) const
		{
			if(Str.m_Size != m_Size)
				return true;

			//Length is the same try digits
			for(ulong Index = 0; Index < m_Size; ++Index)
				if( m_String[Index] == Str.m_String[Index] )
					return false;

			return true;
		}

		bool operator!=( const T* Str ) const
		{
			if(m_Allocator->Length(Str) != m_Size)
				return true;

			//Length is the same try digits
			for(ulong Index = 0; Index < m_Size; ++Index)
				if( m_String[Index] == Str[Index] )
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

		bool FindCharacter(char character, StringT<T, AllocatorT> inString)
		{
			for(ulong Index = 0; Index < inString.Length(); ++Index)
			{
				if(inString.m_pString[Index] == character)
					return true;
			}
			return false;
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
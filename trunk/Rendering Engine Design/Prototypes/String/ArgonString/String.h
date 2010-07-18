#ifndef _STRING_HEADER_
#define _STRING_HEADER_

#ifdef _W64
	typedef __w64 unsigned long ulong;
#else 
	typedef unsigned long ulong;
#endif

namespace Argon
{
	template< typename T > class StringT
	{
	public:
		///Constructor(VOID)
		///
		///Create a new string with the defined template type
		///
		///No Params:
		StringT();

		///Constructor(VOID)
		///
		///Create a new string with the defined template type
		///
		///Param T: The type of string to create
		StringT( const T aString );

		///Constructor(VOID)
		///
		///Create a String using a Bool
		///
		///Param aBool: The value to create the string from
		StringT( bool aBool );

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
		///Create a String using char
		///
		///Param aChar: The value to create the string from
		StringT( char aChar );

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
		~StringT();

		///LENGTH(ULONG)
		///
		///Get the length of the String
		///
		///No Params:
		ulong Length() const;

		///C_STR(LPCHAR)
		///
		///Get a C style pointer to the string
		///
		///No Params:
		char* c_str() const;

		///FINDSTRING(ulong)
		///
		/// Looks for the substring inside the current string
		///
		///Param str: The string to attempt to find within this string
		ulong FindString( const T &str ) const;

		///TOUPPER(VOID)
		///
		///Converts a section of the string to UpperCase
		///
		///Param Count: The amount to change to Uppercase
		///Param Start: The stating point to change to Uppercase
		void ToUpper( ulong Count = 0, ulong Start = 0 );

		///TOLOWER(VOID)
		///
		///Converts a section of the string to LowerCase
		///
		///Param Count: The amount to change to LowerCase
		///Param Start: The stating point to change to LowerCase
		void ToLower( ulong count = 0, ulong start = 0 );

		///
		/// The + operator appends strings in place.
		///
		StringT operator+( const StringT &str ) const;
		StringT operator+( const T cstr ) const;

		///
		/// += concatenates strings together
		///
		StringT & operator+=( const StringT &str );
		StringT & operator+=( const T cstr );

		///
		/// = operator assigns a string to the value of another string or character array
		///
		StringT & operator= ( const StringT &str );
		StringT & operator= ( const T cstr );

		///
		/// == compares strings for equality
		///
		bool     operator==( const StringT &str ) const;
		bool     operator==( const T cstr ) const;

		///
		/// != compares strings for inequality
		///
		bool     operator!=( const StringT &str ) const;
		bool     operator!=( const T cstr ) const;

	private:
		T m_String;
	};
}
#endif //_STRING_HEADER_
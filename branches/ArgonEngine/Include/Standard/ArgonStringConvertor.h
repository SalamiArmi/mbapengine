#ifndef _STRINGCONVERTOR_HEADER_
#define _STRINGCONVERTOR_HEADER_

#include "ArgonStandard.h"
#include "ArgonString.h"

namespace Argon
{
	class Vector2;

	class StringConvertor
	{
	public:
		///parse a string to a wstring
		static WideString ToWideString(String string);

		///Parse a Float to a String
		static float ParseFloat(String string);

		///Parse a int to a string
		static int ParseInt(String string);

		///ToString(bool)
		///
		///Parse a Bool to a string
		///
		///Bool Formatting True: true || TRUE || True
		///Bool Formatting False: false || FALSE || False
		///Accepted Keywords: True or False
		///
		///Param string: The bool string parsed to a bool
		static bool ParseBool(String string);

		///parseVector2(Argon::Vector2)
		///
		///Convert a string to a Argon::Vector2
		///
		///Param string: The string being parsed to a Vector2
		static Vector2 ParseVector2(String string);

		///ToString(std::string)
		///
		///Convert a Real to a String
		///A real is also a Float
		///
		///Param real: The real being parsed to a string
		static String ToString(Real real);

		///convert a int to a String
		static String ToString(int Integer);

		///ToString(std::string)
		///
		///convert a unsigned int to String
		///
		///Param UnsignedInt: The UnsignedInt being parsed to a string
		static String ToString(unsigned int UnsignedInt);

		///ToString(std::string)
		///
		///convert a unsigned short to String
		///
		///Param ushort: The unsigned short being parsed to a string
		static String ToString(unsigned short ushort);

		///ToString(std::string)
		///
		///Convert a Vector 2 to a string
		///
		///Param vector2: The vector being parsed to a string
		static String ToString(Vector2 vector2);

		///ToString(std::string)
		///
		///Convert a DWORD to a string
		///
		///Param dword: The DWORD being parsed to a string
		static String ToString(ulong dword);

		///ToString(std::string)
		///
		///Convert a boolean to a string
		///
		///Param boolean: The bool being parsed to a string
		static String ToString(bool boolean);
	};

#include "ArgonStringConvertor.inl"
}

#endif //_STRINGCONVERTOR_HEADER_
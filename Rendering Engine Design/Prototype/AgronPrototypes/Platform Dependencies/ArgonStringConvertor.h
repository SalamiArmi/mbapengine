#ifndef _STRINGCONVERTOR_HEADER_
#define _STRINGCONVERTOR_HEADER_

#include <string>
#include "Math.h"
#include "Vector2.h"

namespace Zarantas
{
	class StringConvertor
	{
	public:
		///parse a string to a wstring
		static std::wstring ToLPWSTR(std::string s);

		///Parse a string to a Wstring
		static std::wstring ToWString(const std::string& s);

		///Parse a Float to a String
		static float parseFloat(std::string string);

		///Parse a int to a string
		static int parseInt(std::string string);

		///Parse a std::string to a LPCSTR
		static const char* ToLPCSTR(std::string string);

		///ToString(bool)
		///
		///Parse a Bool to a string
		///
		///Bool Formatting True: true || TRUE || True
		///Bool Formatting False: false || FALSE || False
		///Accepted Keywords: True or False
		///
		///Param string: The bool string parsed to a bool
		static bool parseBool(std::string string);

		///parseVector2(Zarantas::Vector2)
		///
		///Convert a string to a Zarantas::Vector2
		///
		///Param string: The string being parsed to a Vector2
		static Zarantas::Vector2 parseVector2(std::string string);

		///ToString(std::string)
		///
		///Convert a Real to a String
		///A real is also a Float
		///
		///Param real: The real being parsed to a string
		static std::string ToString(Zarantas::Real real);

		///convert a int to a String
		static std::string ToString(int Integer);

		///ToString(std::string)
		///
		///convert a unsigned int to String
		///
		///Param UnsignedInt: The UnsignedInt being parsed to a string
		static std::string ToString(unsigned int UnsignedInt);

		///ToString(std::string)
		///
		///convert a unsigned short to String
		///
		///Param ushort: The unsigned short being parsed to a string
		static std::string ToString(unsigned short ushort);

		///ToString(std::string)
		///
		///Convert a Vector 2 to a string
		///
		///Param vector2: The vector being parsed to a string
		static std::string ToString(Zarantas::Vector2 vector2);

		///ToString(std::string)
		///
		///Convert a DWORD to a string
		///
		///Param dword: The DWORD being parsed to a string
		static std::string ToString(unsigned long dword);

		///ToString(std::string)
		///
		///Convert a boolean to a string
		///
		///Param boolean: The bool being parsed to a string
		static std::string ToString(bool boolean);
	};
}

#endif //_STRINGCONVERTOR_HEADER_
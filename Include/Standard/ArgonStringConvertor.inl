#include "ArgonStringConvertor.h"
#include <sstream>
#include "windows.h"

namespace Argon
{
	float StringConvertor::parseFloat(String string)
	{
		return atof(string.c_str());
	}

	std::wstring StringConvertor::ToLPWSTR(const String s)
	{
		int length;
		int slength = (int)s.length() + 1;
		length = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
		wchar_t* buf = new wchar_t[length];
		MultiByteToWideChar(0, 0, s.c_str(), slength, buf, length);
		std::wstring r(buf);
		delete[] buf;
		return r;
	}

	const char* StringConvertor::ToLPCSTR(String string)
	{
		LPCSTR lpcstrReturn;
		return lpcstrReturn = string.c_str();
	}


	std::wstring StringConvertor::ToWString(const String& s)
	{
		std::wstring temp(s.length(),L' ');
		std::copy(s.begin(), s.end(), temp.begin());
		return temp;
	}

	int StringConvertor::parseInt(String string)
	{
		return atoi(string.c_str());
	}

	bool StringConvertor::parseBool(String string)
	{
		if (string == "true" || string == "TRUE" || string == "True")
			return true;
		else if (string == "false" || string == "FALSE" || string == "False")
			return false;
		else 
			return NULL;
	}

	Argon::Vector2 StringConvertor::parseVector2(String string)
	{
		Argon::Vector2 tempVector;
		std::istringstream iss(string);

		String sub;
		iss >> sub;
		tempVector.x = parseFloat(sub);

		iss >> sub;
		tempVector.y = parseFloat(sub);

		return tempVector;
	}

	String StringConvertor::ToString(Argon::Real real)
	{
		std::stringstream StringStreamOutput;
		StringStreamOutput << real;
		return StringStreamOutput.str();
	}


	String StringConvertor::ToString(int Integer)
	{
		std::stringstream StringStreamOutput;
		StringStreamOutput << Integer;
		return StringStreamOutput.str();
	}


	String StringConvertor::ToString(unsigned int UnsignedInt)
	{
		std::stringstream StringStreamOutput;
		StringStreamOutput << UnsignedInt;
		return StringStreamOutput.str();
	}

	String StringConvertor::ToString(unsigned short ushort)
	{
		std::stringstream StringStreamOutput;
		StringStreamOutput << ushort;
		return StringStreamOutput.str();
	}

	String StringConvertor::ToString(Argon::Vector2 vector2)
	{
		std::stringstream StringStreamOutput;
		StringStreamOutput << vector2.x;
		StringStreamOutput << " ";
		StringStreamOutput << vector2.y;
		return StringStreamOutput.str();
	}

	String StringConvertor::ToString(unsigned long dword)
	{
		std::stringstream StringStreamOutput;
		StringStreamOutput << dword;

		return StringStreamOutput.str();
	}

	String StringConvertor::ToString(bool boolean)
	{
		std::istringstream iss(boolean);
		String s;
		iss >> std::boolalpha >> s;
		return s;
	}
}
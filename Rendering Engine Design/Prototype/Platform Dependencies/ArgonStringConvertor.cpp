#include "StringConvertor.h"
#include <sstream>
#include "windows.h"

Bnamespace Zarantas
{
	float StringConvertor::parseFloat(std::string string)
	{
		return atof(string.c_str());
	}

	std::wstring StringConvertor::ToLPWSTR(const std::string s)
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

	const char* StringConvertor::ToLPCSTR(std::string string)
	{
		LPCSTR lpcstrReturn;
		return lpcstrReturn = string.c_str();
	}


	std::wstring StringConvertor::ToWString(const std::string& s)
	{
		std::wstring temp(s.length(),L' ');
		std::copy(s.begin(), s.end(), temp.begin());
		return temp;
	}

	int StringConvertor::parseInt(std::string string)
	{
		return atoi(string.c_str());
	}

	bool StringConvertor::parseBool(std::string string)
	{
		if (string == "true" || string == "TRUE" || string == "True")
			return true;
		else if (string == "false" || string == "FALSE" || string == "False")
			return false;
		else 
			return NULL;
	}

	Zarantas::Vector2 StringConvertor::parseVector2(std::string string)
	{
		Zarantas::Vector2 tempVector;
		std::istringstream iss(string);

		std::string sub;
		iss >> sub;
		tempVector.x = parseFloat(sub);

		iss >> sub;
		tempVector.y = parseFloat(sub);

		return tempVector;
	}

	std::string StringConvertor::ToString(Zarantas::Real real)
	{
		std::stringstream StringStreamOutput;
		StringStreamOutput << real;
		return StringStreamOutput.str();
	}


	std::string StringConvertor::ToString(int Integer)
	{
		std::stringstream StringStreamOutput;
		StringStreamOutput << Integer;
		return StringStreamOutput.str();
	}


	std::string StringConvertor::ToString(unsigned int UnsignedInt)
	{
		std::stringstream StringStreamOutput;
		StringStreamOutput << UnsignedInt;
		return StringStreamOutput.str();
	}

	std::string StringConvertor::ToString(unsigned short ushort)
	{
		std::stringstream StringStreamOutput;
		StringStreamOutput << ushort;
		return StringStreamOutput.str();
	}

	std::string StringConvertor::ToString(Zarantas::Vector2 vector2)
	{
		std::stringstream StringStreamOutput;
		StringStreamOutput << vector2.x;
		StringStreamOutput << " ";
		StringStreamOutput << vector2.y;
		return StringStreamOutput.str();
	}

	std::string StringConvertor::ToString(unsigned long dword)
	{
		std::stringstream StringStreamOutput;
		StringStreamOutput << dword;

		return StringStreamOutput.str();
	}

	std::string StringConvertor::ToString(bool boolean)
	{
		if (boolean == true)
		{
			return "True";
		}
		else if (boolean == false)
		{
			return "False";
		}
	}
}
#include "StringConvertor.h"
#include <sstream>

namespace OOS
{
	float StringConvertor::parseFloat(std::string string)
	{
		return atof(string.c_str());
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

	//FTG::Vector2 StringConvertor::parseVector2(std::string string)
	//{
	//	FTG::Vector2 tempVector;
	//	std::istringstream iss(string);

	//	std::string sub;
	//	iss >> sub;
	//	tempVector.x = parseFloat(sub);

	//	iss >> sub;
	//	tempVector.y = parseFloat(sub);

	//	return tempVector;
	//}

	std::string StringConvertor::ToString(float real)
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

	//std::string StringConvertor::ToString(FTG::Vector2 vector2)
	//{
	//	std::stringstream StringStreamOutput;
	//	StringStreamOutput << vector2.x;
	//	StringStreamOutput << " ";
	//	StringStreamOutput << vector2.y;
	//	return StringStreamOutput.str();
	//}
}
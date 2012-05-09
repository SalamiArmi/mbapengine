#include "ArgonParser.h"

namespace Argon
{	
	Parser::~Parser()
	{
	}

	bool Parser::SupportsFile(IOStream* Stream)
	{
		return false;
	}

	void Parser::ReadHeader()
	{
		
	}

} //Namespace
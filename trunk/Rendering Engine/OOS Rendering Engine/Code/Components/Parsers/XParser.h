#ifndef _XPARSER_HEADER_
#define _XPARSER_HEADER_

#include <string>
#include "Parser.h"

namespace OOS
{
	class XParser : public Parser
	{
	public:
		XParser();
		~XParser();

		Mesh* ReadFile( std::string FileName );
		bool writeFile( std::string FileName );

		bool canParse( std::string FileName );

	protected:

	};

};

#endif //_XPARSER_HEADER_
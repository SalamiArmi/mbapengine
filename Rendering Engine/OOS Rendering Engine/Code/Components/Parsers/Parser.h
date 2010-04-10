#define _PARSER_HEADER_
#ifdef _PARSER_HEADER_

#include <string>
#include "System.h"

namespace OOS
{
	class Mesh;

	class Parser
	{
	public:
		Parser() { System::getSingleton().registorParser(this); }
		virtual ~Parser();

		bool canParse(std::string FileName)	{ return false; }

		Mesh* parseFile(std::string FileName) { return NULL; }

	protected:
		std::string m_Name;
	};
}

#endif //_PARSER_HEADER_
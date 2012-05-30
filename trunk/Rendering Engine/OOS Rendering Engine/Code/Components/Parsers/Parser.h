#define _PARSER_HEADER_
#ifdef _PARSER_HEADER_

#include <string>
#include "Vector3.h"
#include "System.h"

namespace OOS
{
	class Mesh;

	class Parser
	{
	public:
		Parser() { System::getSingleton().registorParser(this); }
		virtual ~Parser() {  }

		bool canParse(std::string FileName)	{ return false; }

		Mesh* parseFile(std::string FileName) { return NULL; }
		bool writeFile(std::string FileName) { return false; }

		Vector<Vector3>		&getNormals(Mesh* mesh);
		Vector<UINT>		&getIndices(Mesh* mesh);
		Vector<int>			&getFaceMaterial(Mesh* mesh);
		Vector<Vector3>		&getTextureCoord0(Mesh* mesh);
		Vector<std::string> &getMaterialNames(Mesh* mesh);

		void closeFile() {  }

	protected:
		std::string m_Name;
		std::string m_Extension;
	};
}

#endif //_PARSER_HEADER_
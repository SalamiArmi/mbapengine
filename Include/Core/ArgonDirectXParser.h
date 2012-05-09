#ifndef _ARGONDIRECTXPARSER_HEADER_
#define _ARGONDIRECTXPARSER_HEADER_

#include <Interface/IOStream.h>

#include "ArgonGeometryParser.h"
#include "ArgonDirectXFileStructs.h"

namespace Argon
{
	class DirectXParser : public GeometryParser
	{
	public:
		DirectXParser();
		~DirectXParser();

		///SUPPORTSFILE(VOID)
		///
		///Check if this $Parser$ can handle the $IOStream$ attempting to be parsed
		///
		///Param Stream: The Stream that will be read
		bool SupportsFile(IOStream* Stream);

		///READHEADER(VOID)
		///
		///Read the header and prepare construct it into readable data
		///
		///No Params
		void ReadHeader();

		///READBODY(VOID)
		///
		///Once the header is constructed attempt to read the body. If a header isn't constructed no body can be read.
		///
		///No Params
		void ReadBody();

		///GETSIGNATURE(VOID)
		///
		///The signature will determin if the file can be read or not.
		///
		///No Params
		char* GetSignature();

	private:

		bool ReadTokens();
		void ReadTokenTemplate(stTokenTemplate *pToken);
		void ReadTokenTemplateParts(stTokenTemplate *pToken);
		void ReadTokenFloatList(stTokenFloatList *pToken);
		void ReadTokenIntList(stTokenIntList *pToken);
		void ReadTokenGUID(stTokenGUID *pToken);
		void ReadTokenInt(stTokenInt *pToken);
		void ReadTokenFloat(stTokenFloat *pToken);
		void ReadTokenString(stTokenString *pToken);
		void ReadTokenName(stTokenName *pToken);

		void ProcessMesh();
		void ProcessVerts();
		void ProcessFaces();
		void ProcessNormals();
		void ProcessTexCoord();
		void ProcessMaterialNames();

		uint		m_SavedVerticesNumber;
		uint		m_IndexOffset;

		IOStream*	m_Stream;

	}; //Class
} //namespace

#endif //_ARGONDIRECTXPARSER_HEADER_
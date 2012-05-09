#ifndef _ARGONPARSER_HEADER_
#define _ARGONPARSER_HEADER_

#include <Standard/ArgonVector.h>
#include <Standard/ArgonString.h>
#include <Standard/ArgonIOExplorer.h>

namespace Argon
{
	class Parser
	{
	public:
		virtual ~Parser();

		///SUPPORTSFILE(VOID)
		///
		///Check if this $Parser$ can handle the filedata attempting to be parsed
		///
		///Param FileData: The file data in string form
		virtual bool SupportsFile(IOStream* Stream);

		///READHEADER(VOID)
		///
		///Read the header and prepare construct it into readable data
		///
		///No Params
		virtual void ReadHeader();

		///READBODY(VOID)
		///
		///Once the header is constructed attempt to read the body. If a header isn't constructed no body can be read.
		///
		///No Params
		virtual void ReadBody() = 0;

		///GETSIGNATURE(VOID)
		///
		///The signature will determin if the file can be read or not.
		///
		///No Params
		virtual char* GetSignature() = 0;

	protected:
		struct Header
		{
		public:
			char*			m_FileSignature;	//4 Bytes
			ulong			m_HeaderLength;		//The total length of the header
			Vector<ulong>	m_Offsets;			//Each offset will lead to a point within the body containing specific data
		}; //Struct

		IOExplorer*			m_IOExplorer;
		Header				m_FileHeader;
	};

} //Namespace

#endif //_ARGONPARSER_HEADER_
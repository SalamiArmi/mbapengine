#ifndef _ARGONDIRECTXFILESTRUCTS_HEADER_
#define _ARGONDIRECTXFILESTRUCTS_HEADER_

namespace Argon
{
#define XOFFILE_FORMAT_HEADER \
	((long)'x' + ((long)'o' << 8) + ((long)'f' << 16) + ((long)' ' << 24))

#define XOFFILE_FORMAT_VERSION03 \
	((long)'0' + ((long)'3' << 8))

#define XOFFILE_FORMAT_VERSION02 \
	((long)'0' + ((long)'3' << 8))

#define XOFFILE_FORMAT_BINARY \
	((long)'b' + ((long)'i' << 8) + ((long)'n' << 16) + ((long)' ' << 24))

#define XOFFILE_FORMAT_TEXT   \
	((long)'t' + ((long)'x' << 8) + ((long)'t' << 16) + ((long)' ' << 24))

#define XOFFILE_FORMAT_COMPRESSED \
	((long)'c' + ((long)'m' << 8) + ((long)'p' << 16) + ((long)' ' << 24))

#define XOFFILE_FORMAT_FLOAT_BITS_32 \
	((long)'0' + ((long)'0' << 8) + ((long)'3' << 16) + ((long)'2' << 24))

#define XOFFILE_FORMAT_FLOAT_BITS_64 \
	((long)'0' + ((long)'0' << 8) + ((long)'6' << 16) + ((long)'4' << 24))


	struct XFileHeader {
		unsigned long Magic; // Sig
		unsigned short Major_Version;
		unsigned short Minor_Version;
		unsigned long Format;
		unsigned long Float_Size;
	};

#define TOKEN_NAME         			1
#define TOKEN_STRING       			2
#define TOKEN_INTEGER      			3
#define TOKEN_GUID         			5
#define TOKEN_INTEGER_LIST 			6
#define TOKEN_FLOAT_LIST   			7

#define TOKEN_OBRACE      			10
#define TOKEN_CBRACE      			11
#define TOKEN_OPAREN      			12
#define TOKEN_CPAREN      			13
#define TOKEN_OBRACKET    			14
#define TOKEN_CBRACKET    			15
#define TOKEN_OANGLE      			16
#define TOKEN_CANGLE      			17
#define TOKEN_DOT         			18
#define TOKEN_COMMA       			19
#define TOKEN_SEMICOLON   			20
#define TOKEN_TEMPLATE    	        31
#define TOKEN_WORD        			40
#define TOKEN_DWORD       			41
#define TOKEN_FLOAT       			42
#define TOKEN_DOUBLE      			43
#define TOKEN_CHAR        			44
#define TOKEN_UCHAR       			45
#define TOKEN_SWORD       			46
#define TOKEN_SDWORD      			47
#define TOKEN_VOID        			48
#define TOKEN_LPSTR       			49
#define TOKEN_UNICODE     			50
#define TOKEN_CSTRING		     	51
#define TOKEN_ARRAY       			52


#define TOKEN_COMMENT				254
#define TOKEN_UNKNOWN				255 //unknown block


#pragma pack(1)

	struct stXHeader
	{						// size		desc
		char m_sig[4];		// 4		Magic Number (required) "xof "
		char m_minor[2];	// 2		Minor Version 03
		char m_major[2];	// 2		Major Version 02
		char m_type[4];		// 4		Format Type (required) 
		//	"txt " Text File
		//	"bin " Binary File  
		//	"tzip" MSZip Compressed Text File
		//	"bzip" MSZip Compressed Binary File
		char m_accuracy[4]; // 4		Float Accuracy "0032" 32 bit or "0064" 64 bit

	};// End stXHeader

#pragma pack()


#define MATOKEN_STRING			128
#define MATOKEN_INT_LIST		128
#define MATOKEN_FLOAT_LIST		128

#pragma pack(1)
	struct stTokenName
	{
		unsigned short	m_token;			// token_name 
		unsigned int	m_count;			// Length of name field, in bytes 
		char			m_name[MATOKEN_STRING];	// array count ASCII name 
	};

	struct stTokenString
	{
		unsigned short	m_token;			// WORD 2 token_string 
		unsigned int	m_count;			// DWORD 4 Length of string field in bytes 
		char			m_string[MATOKEN_STRING];// BYTE array count ASCII string  
		unsigned int	m_terminator;		// DWORD 4 tOKEN_SEMICOLON or TOKEN_COMMA 
	};

	struct stTokenInt
	{
		unsigned short	m_token;			// WORD 2 tOKEN_INTEGER 
		unsigned int	m_value;			// DWORD 4 Single integer 
	};

	struct stTokenFloat
	{
		unsigned short	m_token;			// WORD 2 tOKEN_INTEGER 
		unsigned float	m_value;			// ????????????????????
	};

	struct stTokenGUID
	{
		unsigned short m_token;				// WORD 2 tOKEN_GUID 
		unsigned int   m_Data1;				// DWORD 4 UUID data field 1 
		unsigned short m_Data2;				// WORD 2 UUID data field 2 
		unsigned short m_Data3;				// WORD 2 UUID data field 3 
		unsigned char  m_Data4[8];			// BYTE array 8 UUID data field 4 
	};

	struct stTokenIntList
	{
		unsigned short m_token;				// WORD 2 tOKEN_INTEGER_LISt 
		unsigned int   m_count;				// DWORD 4 Number of integers in list field 
		unsigned int   m_list[MATOKEN_INT_LIST];// DWORD 4 x count Integer list  
	};

	struct stTokenFloatList
	{
		unsigned short m_token;				// WORD 2 tOKEN_FLOAT_LISt 
		unsigned int   m_count;				// DWORD 4 Number of floats or doubles in list field  
		float		   m_list[MATOKEN_FLOAT_LIST];	// float/double array 4 or 8 x count Float or double list  
		// determined from the header accuracy
	};
#pragma pack()

	struct stTokenTemplate
	{
		int			m_token;					// TOKEN_TEMPLATE
		stTokenName	m_tokName;					// TOKEN_NAME
		stTokenGUID m_tokGUID;					// TOKEN_GUID
	};

} //namespace

#endif //_ARGONDIRECTXFILESTRUCTS_HEADER_
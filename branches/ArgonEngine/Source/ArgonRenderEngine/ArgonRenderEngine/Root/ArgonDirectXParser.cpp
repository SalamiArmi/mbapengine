#include "ArgonDirectXParser.h"
#include <Interface/IOStream.h>

namespace Argon
{
	DirectXParser::DirectXParser()
		: m_IndexOffset(0),
		m_SavedVerticesNumber(0),
		m_Stream(NULL)
	{
	}
	
	DirectXParser::~DirectXParser()
	{
	}

	bool DirectXParser::SupportsFile(IOStream* Stream)
	{
		if(Stream)
		{
			m_Stream = Stream;
			m_IOExplorer = new IOExplorer(m_Stream);
			XFileHeader FileHeader;

			Stream->Read((char*)&FileHeader, sizeof(XFileHeader));
			if(FileHeader.Magic != XOFFILE_FORMAT_HEADER || FileHeader.Format  != XOFFILE_FORMAT_BINARY)
			{
				delete m_IOExplorer;
				m_IOExplorer = NULL;
				return false;
			}
		}

		return true;
	}

	void DirectXParser::ReadHeader()
	{
		ReadBody();
	}

	void DirectXParser::ReadBody()
	{
		bool ContinueReading = true;
		while(ContinueReading)
		{
			ContinueReading = ReadTokens();
		}
	}

	char* DirectXParser::GetSignature()
	{
		return (char*)XOFFILE_FORMAT_HEADER;
	}

	bool DirectXParser::ReadTokens()
	{
		ushort TokenType;
		bool Read = m_Stream->Read((char*)&TokenType, sizeof(ushort));

		if (!Read)
		{
			return false;
		}

		switch (TokenType)
		{
			case TOKEN_NAME:
			{
				stTokenName Token;
				ReadTokenName(&Token);

				// Mesh
				if(String(Token.m_name) == String("Mesh"))
				{
					ProcessMesh();
				}
				else if(String( Token.m_name) == String("MeshNormals"))
				{
					ProcessNormals();
				}
				else if(String(Token.m_name) == String("MeshTextureCoords"))
				{
					ProcessTexCoord();
				}
				else if(String(Token.m_name) == String("MeshMaterialList")) 
				{
					ProcessMaterialNames();
				}
				break;
			}
			case TOKEN_STRING:
			{
				stTokenString Token;
				ReadTokenString(&Token);
				break;
			}
			case TOKEN_INTEGER:
			{
				stTokenInt Token;
				ReadTokenInt(&Token);
				break;
			}
			case TOKEN_FLOAT:
			{
				stTokenFloat Token;
				ReadTokenFloat(&Token);
				break;
			}
			case TOKEN_GUID:
			{
				stTokenGUID Token;
				ReadTokenGUID(&Token);
				break;
			}
			case TOKEN_INTEGER_LIST:
			{
				stTokenIntList Token;
				ReadTokenIntList(&Token);
				break;
			}
			case TOKEN_FLOAT_LIST:
			{
				stTokenFloatList Token;
				ReadTokenFloatList(&Token);
				break;
			}
			case TOKEN_OBRACE:
			{
				break;
			}
			case TOKEN_CBRACE:
			{
				break;
			}
			case TOKEN_TEMPLATE:
			{
				stTokenTemplate Token;
				ReadTokenTemplate(&Token);
				break;
			}
			default:
			{
				// Once we reach an unknown type we'll just bail out here, usually
				// the templates or something
				return false;
			}
		}
		return true;
	}

	void DirectXParser::ReadTokenTemplate(stTokenTemplate* Token)
	{
		// TOKEN_TEMPLATE name TOKEN_OBRACE class_id template_parts TOKEN_CBRACE
		Token->m_token = TOKEN_TEMPLATE;

		ushort TokenType;
		m_Stream->Read((char*)&TokenType, sizeof(TokenType));
		if (TokenType != TOKEN_NAME)
		{
		}

		ReadTokenName(&Token->m_tokName);

		m_Stream->Read((char*)&TokenType, sizeof(TokenType));
		if ( TokenType != TOKEN_OBRACE )
		{
		}

		m_Stream->Read((char*)&TokenType, sizeof(TokenType));
		if ( TokenType != TOKEN_GUID )
		{
		}

		ReadTokenGUID(&Token->m_tokGUID);
		ReadTokenTemplateParts(Token);
	}

	void DirectXParser::ReadTokenTemplateParts(stTokenTemplate* Token)
	{
		// primitive_type optional_name TOKEN_SEMICOLON
		ushort TokenType = 0;

		while(TokenType != TOKEN_CBRACE)
		{
			m_Stream->Read( (char*)&TokenType, sizeof(TokenType) );
			switch (TokenType)
			{
				case TOKEN_NAME:
				{
					stTokenName TokenName; // name is optional
					ReadTokenName(&TokenName);
				}
				case TOKEN_SEMICOLON:
				{
					continue;
				}
				default:
				{
					continue;
				}
			}
		}
	}

	void DirectXParser::ReadTokenFloatList(stTokenFloatList* Token)
	{
		Token->m_token = TOKEN_FLOAT_LIST;
		m_Stream->Read((char*)&Token->m_count, sizeof(uint));

		memset(&Token->m_list[0], 0, sizeof(Token->m_list));

		for (uint Index = 0; Index < Token->m_count; ++Index)
		{
			float Temp;
			m_Stream->Read((char*)&Temp, sizeof(float));
			
			if (Index < MATOKEN_FLOAT_LIST)
			{
				Token->m_list[Index] = Temp;
			}
		}
	}

	void DirectXParser::ReadTokenIntList(stTokenIntList* Token)
	{
		Token->m_token = TOKEN_INTEGER_LIST;
		m_Stream->Read((char*)&Token->m_count, sizeof(uint));

		memset(&Token->m_list[0], 0, sizeof(Token->m_list));

		for(uint Index = 0; Index < Token->m_count; ++Index )
		{
			uint Temp;
			m_Stream->Read((char*)&Temp, sizeof(uint));
			
			if (Index < MATOKEN_INT_LIST)
			{
				Token->m_list[Index] = Temp;
			}
		}
	}

	void DirectXParser::ReadTokenGUID(stTokenGUID *Token)
	{
		Token->m_token = TOKEN_GUID;

		m_Stream->Read((char*)&Token->m_Data1, sizeof(uint));
		m_Stream->Read((char*)&Token->m_Data2, sizeof(ushort));
		m_Stream->Read((char*)&Token->m_Data3, sizeof(ushort));

		for (int Index = 0; Index < 8; ++Index)
		{
			m_Stream->Read((char*)&Token->m_Data4, sizeof(uchar));
		}
	}

	void DirectXParser::ReadTokenInt(stTokenInt *Token)
	{
		Token->m_token = TOKEN_INTEGER;
		m_Stream->Read((char*)&Token->m_value, sizeof(uint));
	}

	void DirectXParser::ReadTokenFloat(stTokenFloat *Token)
	{
		Token->m_token = TOKEN_FLOAT;

		float Temp;
		size_t float_size = 4; // TODO - dependent on file 32 or 64 bit.
		m_Stream->Read((char*)&Temp, float_size);
	}

	void DirectXParser::ReadTokenString(stTokenString *Token)
	{
		Token->m_token = TOKEN_STRING;
		m_Stream->Read( (char*)&Token->m_count, sizeof(uint) );

		// Size doesn't include the null terminator!
		memset(&Token->m_string, '\0', sizeof(Token->m_string));

		for(uint Index = 0; Index < Token->m_count; ++Index)
		{
			char Temp;
			m_Stream->Read((char*)&Temp, sizeof(char));
			if ((Index + 1) < MATOKEN_STRING )
			{
				Token->m_string[Index] = Temp;
			}
		}

		m_Stream->Read((char*)&Token->m_terminator, sizeof(uint));
	}

	void DirectXParser::ReadTokenName(stTokenName *Token)
	{
		Token->m_token = TOKEN_NAME;
	
		m_Stream->Read((char*)&Token->m_count, sizeof(uint));

		// Size doesn't include the null terminator!
		memset(&Token->m_name, '\0', sizeof(Token->m_name));

		for(uint Index = 0; Index < Token->m_count; ++Index)
		{
			char Temp;
			m_Stream->Read( (char*)&Temp, sizeof(char));

			if((Index + 1) < MATOKEN_STRING)
			{
				Token->m_name[Index] = Temp;
			}
		}
	}

	void DirectXParser::ProcessMesh()
	{
		// Name (optional)
		ushort TokenType;
		m_Stream->Read((char*)&TokenType, sizeof(TokenType));
		if ( TokenType == TOKEN_NAME )
		{
			stTokenName Token;
			ReadTokenName(&Token);

			m_Stream->Read((char*)&TokenType, sizeof(TokenType));
		}

		ArgonAssert( TokenType == TOKEN_OBRACE );

		//Mystery Count/Mystery List
		m_Stream->Read( (char*)&TokenType, sizeof(TokenType) );
		ArgonAssert(TokenType == TOKEN_INTEGER_LIST);
		stTokenIntList tok2;
		ReadTokenIntList(&tok2);
		
		//Vertex count/Vertex list
		ProcessVerts();

		//Index Count/Index List 
		ProcessFaces();
	}

	void DirectXParser::ProcessVerts()
	{
		m_SavedVerticesNumber = m_Vertices.Size();

		ushort TokenType;
		m_Stream->Read((char*)&TokenType, sizeof(TokenType));
		ArgonAssert(TokenType == TOKEN_FLOAT_LIST);

		uint Count = 0;
		m_Stream->Read((char*)&Count, sizeof(uint));

		Count /= 3;
		for(uint Index = 0; Index < Count; ++Index)
		{
			float x = 0.0f, y = 0.0f, z = 0.0f;
			m_Stream->Read((char*)&x, sizeof(float));
			m_Stream->Read((char*)&y, sizeof(float));
			m_Stream->Read((char*)&z, sizeof(float));
			
			m_Vertices.Push_Back(Vector3(x, y, z));
		}
	}

	void DirectXParser::ProcessFaces()
	{
		m_IndexOffset = m_Indices.Size();

		ushort TokenType;
		m_Stream->Read( (char*)&TokenType, sizeof(TokenType));
		ArgonAssert(TokenType == TOKEN_INTEGER_LIST);

		uint Count = 0;
		m_Stream->Read((char*)&Count, sizeof(uint));
		m_Stream->Read((char*)&Count, sizeof(uint));

		for (uint i = 0; i < Count; ++i)
		{
			uint n;
			m_Stream->Read((char*)&n, sizeof(float)); // TODO float_size
			ArgonAssert(n == 3);
			
			for(uint j = 0; j < n; ++j)
			{
				uint Index;
				m_Stream->Read((char*)&Index, sizeof(float)); // TODO float_size
				m_Indices.Push_Back(Index + m_SavedVerticesNumber);
			}
		}
	}

	void DirectXParser::ProcessNormals()
	{
		// Name (optional)
		ushort TokenType;
		m_Stream->Read((char*)&TokenType, sizeof(TokenType));
		if (TokenType == TOKEN_NAME)
		{
			stTokenName tok;
			ReadTokenName(&tok);

			m_Stream->Read((char*)&TokenType, sizeof(TokenType));
		}

		ArgonAssert(TokenType == TOKEN_OBRACE);

		// Mystery Count/Mystery List
		m_Stream->Read((char*)&TokenType, sizeof(TokenType));
		ArgonAssert(TokenType == TOKEN_INTEGER_LIST);
		stTokenIntList tok2;
		ReadTokenIntList(&tok2);

		// Normals Count/Normals List
		m_Stream->Read((char*)&TokenType, sizeof(TokenType));
		ArgonAssert(TokenType == TOKEN_FLOAT_LIST);

		uint Count = 0;
		m_Stream->Read((char*)&Count, sizeof(uint));
		Count /= 3;

		Vector<Vector3> aFaceNormals;
		aFaceNormals.Resize(Count);

		for(uint i = 0; i < Count; ++i)
		{
			float x, y, z;
			m_Stream->Read((char*)&x, sizeof(float));
			m_Stream->Read((char*)&y, sizeof(float));
			m_Stream->Read((char*)&z, sizeof(float));

			aFaceNormals[i] = Vector3(x, y, z);
		}

		// Face Normals Count / Face Normals List
		m_Stream->Read((char*)&TokenType, sizeof(TokenType));
		ArgonAssert(TokenType == TOKEN_INTEGER_LIST);

		Count = 0;
		m_Stream->Read((char*)&Count, sizeof(uint));
		m_Stream->Read((char*)&Count, sizeof(uint) );

		int* aaa = new int[Count * 3];
		for (uint i = 0; i < Count; ++i)
		{
			uint n;
			m_Stream->Read((char*)&n, sizeof(float));
			ArgonAssert(n == 3);
			
			for (uint j = 0; j < n; ++j)
			{
				int index;
				m_Stream->Read((char*)&index, sizeof(int));
				aaa[ 3 * i + j ] = index;
			}
		}

		ArgonAssert( m_Vertices.Size() > m_SavedVerticesNumber );
		Vector<Vector<int>> aVertexNormals;
		aVertexNormals.Resize(m_Vertices.Size() - m_SavedVerticesNumber);

		for (uint i = 0; i < Count * 3; ++i)
		{
			int nNormalIndex = aaa[i];
			int nVertexIndex = m_Indices[i + m_IndexOffset];
			aVertexNormals[ nVertexIndex - m_SavedVerticesNumber ].Push_Back(nNormalIndex);
		}

		for(uint i = 0; i < aVertexNormals.Size(); ++i)
		{
			Vector3 v(0, 0, 0);
			if (aVertexNormals[i].Size())
			{
				for(uint j = 0; j < aVertexNormals[i].Size(); ++j)
				{
					uint nNormalIndex = aVertexNormals[i][j];
					v += aFaceNormals[ nNormalIndex ];
				}
				v /= (float)aVertexNormals[i].Size();
			}

			m_Normals.Push_Back(v);
		}

		delete[] aaa;
	}

	void DirectXParser::ProcessTexCoord()
	{
		ushort TokenType;

		// Name (optional)
		m_Stream->Read((char*)&TokenType, sizeof(TokenType));
		if (TokenType == TOKEN_NAME)
		{
			stTokenName tok;
			ReadTokenName(&tok);

			m_Stream->Read((char*)&TokenType, sizeof(TokenType));
		}

		ArgonAssert(TokenType == TOKEN_OBRACE);

		// Mystery List
		m_Stream->Read((char*)&TokenType, sizeof(TokenType));
		ArgonAssert(TokenType == TOKEN_INTEGER_LIST);

		uint Count = 0;
		m_Stream->Read((char*)&Count, sizeof(uint));

		for (uint i = 0; i < Count; ++i)
		{
			uint x;
			m_Stream->Read((char*)&x, sizeof(uint));
		}

		// Co-ordinates
		m_Stream->Read((char*)&TokenType, sizeof(TokenType));
		ArgonAssert( TokenType == TOKEN_FLOAT_LIST );

		m_Stream->Read((char*)&Count, sizeof(uint));

		Count /= 2;

		for (uint i = 0; i < Count; ++i)
		{
			float u;
			float v;
			m_Stream->Read((char*)&u, sizeof(float));
			m_Stream->Read((char*)&v, sizeof(float));
			
			m_TexCoord.Push_Back(Vector3(u,v,0));
		}
	}

	void DirectXParser::ProcessMaterialNames()
	{
		ushort TokenType;
		uint Count;
		uint MaterialCount;

		// Name (optional?)
		m_Stream->Read((char*)&TokenType, sizeof(TokenType));
		if (TokenType == TOKEN_NAME)
		{
			stTokenName tok;
			ReadTokenName(&tok);

			m_Stream->Read((char*)&TokenType, sizeof(TokenType));
		}

		ArgonAssert(TokenType == TOKEN_OBRACE);

		// Material Count..
		m_Stream->Read((char*)&TokenType, sizeof(TokenType));
		ArgonAssert(TokenType == TOKEN_INTEGER_LIST);

		// Total count
		m_Stream->Read((char*)&Count, sizeof(uint));

		// Number of materials
		m_Stream->Read((char*)&MaterialCount, sizeof(uint));

		// Remaining count
		m_Stream->Read((char*)&Count, sizeof(uint));

		// Material Face ID's
		for (uint i = 0; i < Count; ++i)
		{
			uint x;
			m_Stream->Read((char*)&x, sizeof(uint));

			m_FaceMaterial.Push_Back(x);
		}

		// Read each material definition
		for (uint i = 0; i < MaterialCount; ++i)
		{
			bool Brace = false;
			m_Stream->Read((char*)&TokenType, sizeof(TokenType));
			if (TokenType == TOKEN_OBRACE)
			{
				Brace = true;
				m_Stream->Read((char*)&TokenType, sizeof(TokenType));
			}
			
			if (TokenType == TOKEN_CBRACE) continue;

			ArgonAssert( TokenType == TOKEN_NAME );

			stTokenName tok;
			ReadTokenName(&tok);
			m_MaterialNames.Push_Back(tok.m_name);

			if (Brace)
			{
				m_Stream->Read((char*)&TokenType, sizeof(TokenType));
				ArgonAssert(TokenType == TOKEN_CBRACE);
			}
		}
	}

} //Namespace
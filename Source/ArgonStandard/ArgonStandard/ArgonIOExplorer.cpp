#include <Standard/ArgonIOExplorer.h>

namespace Argon
{
	ArgonStandard IOExplorer::IOExplorer(IOStream* Stream)
		: m_Stream(Stream)
	{
	}

	ArgonStandard IOExplorer::~IOExplorer()
	{
	}

	ArgonStandard IOExplorer& IOExplorer::operator <<(String Parse) 
	{
		//Write the total string length to the stream.
		//First the length then the bytes.
		ulong Length = Parse.Length();
		(*this) << Length;
		m_Stream->Write(Parse.c_str(), Length);
		return (*this);
	}

	ArgonStandard IOExplorer& IOExplorer::operator >>(String &Parse)
	{
		//Read out the Length then the Bytes
		ulong Length = 0;
		(*this) >> Length;

		char* Buffer = new char[Length];
		m_Stream->Read(Buffer, Length);

		Parse = Buffer;
		delete Buffer;

		return (*this);
	}

	ArgonStandard IOExplorer& IOExplorer::operator <<(ulong Parse)
	{
		char* const p = reinterpret_cast<char* const>(Parse);
		m_Stream->Write(p, sizeof(ulong));

		return (*this);
	}

	ArgonStandard IOExplorer& IOExplorer::operator >>(ulong &Parse)
	{
		char Buffer[sizeof(ulong)];
		m_Stream->Read(Buffer, sizeof(ulong));
		Parse = reinterpret_cast<ulong>(Buffer);

		return (*this);
	}

	ArgonStandard IOExplorer& IOExplorer::operator <<(long Parse)
	{
		char* const p = reinterpret_cast<char* const>(Parse);
		m_Stream->Write(p, sizeof(long));

		return (*this);
	}

	ArgonStandard IOExplorer& IOExplorer::operator >>(long &Parse)
	{
		char Buffer[sizeof(long)];
		m_Stream->Read(Buffer, sizeof(long));
		Parse = reinterpret_cast<long>(Buffer);

		return (*this);
	}

	ArgonStandard IOExplorer& IOExplorer::operator <<(long64 Parse)
	{
		char* const p = reinterpret_cast<char* const>(Parse);
		m_Stream->Write(p, sizeof(long64));

		return (*this);
	}

	ArgonStandard IOExplorer& IOExplorer::operator >>(long64 &Parse)
	{
		char Buffer[sizeof(long64)];
		m_Stream->Read(Buffer, sizeof(long64));
		Parse = reinterpret_cast<long64>(Buffer);

		return (*this);
	}

	ArgonStandard IOExplorer& IOExplorer::operator <<(ulong64 Parse)
	{
		char* const p = reinterpret_cast<char* const>(Parse);
		m_Stream->Write(p, sizeof(ulong64));

		return (*this);
	}

	ArgonStandard IOExplorer& IOExplorer::operator >>(ulong64 &Parse)
	{
		char Buffer[sizeof(ulong64)];
		m_Stream->Read(Buffer, sizeof(ulong64));
		Parse = reinterpret_cast<ulong64>(Buffer);

		return (*this);
	}

	ArgonStandard IOExplorer& IOExplorer::operator <<(ushort Parse)
	{
		char* const p = reinterpret_cast<char* const>(Parse);
		m_Stream->Write(p, sizeof(ushort));

		return (*this);
	}

	ArgonStandard IOExplorer& IOExplorer::operator >>(ushort &Parse)
	{
		char Buffer[sizeof(ushort)];
		m_Stream->Read(Buffer, sizeof(ushort));
		Parse = reinterpret_cast<ushort>(Buffer);

		return (*this);
	}

	ArgonStandard IOExplorer& IOExplorer::operator <<(short Parse)
	{
		char* const p = reinterpret_cast<char* const>(Parse);
		m_Stream->Write(p, sizeof(short));

		return (*this);
	}

	ArgonStandard IOExplorer& IOExplorer::operator >>(short &Parse)
	{
		char Buffer[sizeof(short)];
		m_Stream->Read(Buffer, sizeof(short));
		Parse = reinterpret_cast<short>(Buffer);

		return (*this);
	}

	ArgonStandard IOExplorer& IOExplorer::operator <<(float Parse)
	{
		return (*this);
	}

	ArgonStandard IOExplorer& IOExplorer::operator >>(float &Parse)
	{
		return (*this);
	}

	ArgonStandard IOExplorer& IOExplorer::operator <<(uint Parse)
	{
		char* const p = reinterpret_cast<char* const>(Parse);
		m_Stream->Write(p, sizeof(uint));

		return (*this);
	}

	ArgonStandard IOExplorer& IOExplorer::operator >>(uint &Parse)
	{
		char Buffer[sizeof(uint)];
		m_Stream->Read(Buffer, sizeof(uint));
		Parse = reinterpret_cast<uint>(Buffer);

		return (*this);
	}

	ArgonStandard IOExplorer& IOExplorer::operator <<(int Parse)
	{
		char* const p = reinterpret_cast<char* const>(Parse);
		m_Stream->Write(p, sizeof(int));

		return (*this);
	}

	ArgonStandard IOExplorer& IOExplorer::operator >>(int &Parse)
	{
		char Buffer[sizeof(int)];
		m_Stream->Read(Buffer, sizeof(int));
		Parse = reinterpret_cast<int>(Buffer);

		return (*this);
	}
}//Namespace
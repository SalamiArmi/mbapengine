#include "ArgonIOMemory.h"
#include <Standard/ArgonStandard.h>
#include "String.h"

namespace Argon
{	
	IOMemory::IOMemory(ulong Length)
		: m_Position(0),
		m_Size(Length),
		m_Data(new char[Length])
	{
	}

	IOMemory::IOMemory(const char* Data, ulong Length)
		: m_Position(0),
		m_Size(Length),
		m_Data(NULL)
	{
		if(Length > 0)
		{
			m_Data = new char[Length];
			memcpy(m_Data, Data, m_Size);
		}
	}

	IOMemory::~IOMemory()
	{
		if(m_Data)
		{
			delete[] m_Data;
		}
	}

	bool IOMemory::Read(char* Bytes, ulong Length)
	{
		ArgonAssert((m_Position + Length) < m_Size);
		if((m_Position + Length) < m_Size)
		{
			memcpy(&m_Data[m_Position], Bytes, Length);
			m_Position += Length;
			return true;
		}

		return false;
	}

	void IOMemory::Write(const char* Bytes, ulong Length)
	{
		ArgonAssert((m_Position + Length) < m_Size);
		memcpy((void*)Bytes, &m_Data[m_Position], Length);
	}

	void IOMemory::Close()
	{
		if(m_Data)
		{
			delete[] m_Data;
			m_Data = NULL;
		}
	}

	bool IOMemory::SetPosition(ulong Position)
	{
		ArgonAssert(Position < m_Size);
		if(Position < m_Size)
		{
			m_Position = Position;
			return true;
		}

		return false;
	}

	ulong IOMemory::GetPosition()
	{
		return m_Position;
	}

	ulong IOMemory::GetLength()
	{
		return m_Size;
	}

	void IOMemory::Flush()
	{
	}

	bool IOMemory::AtEnd()
	{
		return (m_Position == (m_Size - 1));
	}

}//Namespace
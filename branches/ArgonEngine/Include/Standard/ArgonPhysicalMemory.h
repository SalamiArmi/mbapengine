#ifndef _ARGONPHYSICALMEMORY_HEADER_
#define _ARGONPHYSICALMEMORY_HEADER_

#include "Standard/ArgonMutex.h"
#include "Interface/IBuffer.h"

namespace Argon
{
	template< typename T > class PhysicalMemory : public IArgonUnknownImp<IBuffer, GUID_IBuffer>, public MutexImpl
	{
	public:
		PhysicalMemory(ulong Size)
			: m_Size(Size),
			m_Memory(NULL),
			m_LockCount(0),
			m_Usage(IBuffer::USAGE_Dynamic)
		{
			m_Memory = new T[Size];
		}

		~PhysicalMemory()
		{
			delete[] m_Memory;
			m_Memory = NULL;
		}

		IBuffer::Usage GetUsageType()
		{
			return m_Usage;
		}

		IBuffer::BufferType GetBufferType()
		{
			return BUFFERTYPE_PhysicalMemory;
		}

		bool Is32Bit()
		{
			return false;
		}

		ulong GetSize()
		{
			return m_Size;
		}

		bool LoadPhysicalData(void** Data)
		{
			LockImpl();
			++m_LockCount;
			(*Data) = m_Memory;
			
			return (m_LockCount > 0);
		}

		bool UnloadPhysicalData()
		{
			--m_LockCount;
			UnlockImpl();

			return !(m_LockCount);
		}

		bool UploadToVideoMemory()
		{
			return false;
		}

	private:
		int m_LockCount;
		IBuffer::Usage m_Usage;

		ulong m_Size;
		T* m_Memory;
	};

} //Namespace

#endif //_ARGONPHYSICALMEMORY_HEADER_
////////////////////////////////////////////////////////////////
//
//	ArgonMemory.h : Argon Memory Utilities
//
//	Copyright ©2010 Argon. All rights reserved.
//	Removal of this copyright notice is not permitted.
//
///////////////////////////////////////////////////////////////

#ifndef _REFERENCEPOINTER_HEADER_
#define _REFERENCEPOINTER_HEADER_

#include <limits>
#include "ArgonMemoryPool.h"

//#define _USE_MEMORY_POOL_

namespace Argon
{
	template< typename Type > class AutoPtr
	{
	public:

		explicit AutoPtr()
		{
			m_StoredPtr = new Type();
		}

		~AutoPtr()
		{
			delete m_StoredPtr;
		}

		Type& operator*() const
		{
			return *m_StoredPtr;
		}

		Type* operator =(Type* Rhs) const
		{
			Rhs = m_StoredPtr;
			return this;
		}

		Type* operator->() const
		{
			return m_StoredPtr;
		}

	protected:

	private:
		Type*	m_StoredPtr;
	};
}

///(VOID)
///
/// Custom new operator using the memory pool
///
///No Params:
inline void* operator new(size_t BlockSize, const char* pDescription)
{
#if defined _USE_MEMORY_POOL_
	return NULL; //TODO
#else
	return malloc(BlockSize);
#endif
}

///(VOID)
///
/// Custom delete operator using the memory pool
///
///
///No Params:
inline void operator delete(void* pBlock, const char* Description)
{
#if defined _USE_MEMORY_POOL_
	
#else
	free(pBlock);
#endif
}

///ARGONNEWARRAY(VOID)
///
///Create a new array that will use the custom allocator
///
///Param ElementCount: The total amount of elements to create
///Param Description: A brief descriptioin of the deleted object
template<typename T> inline T* ArgonNewArray(size_t ElementCount, const char* Description)
{
	size_t TotalSize = sizeof(HeapHandle) + ElementCount * sizeof(T);	//Find the Total Size
	char* DataBlock = (char*)(malloc(TotalSize));						//Allocate the many Bits
	if(DataBlock)
	{
		T* Block = (T*)(DataBlock + sizeof(HeapHandle)); //Get the Data after the Heap Handle

		*((size_t*) DataBlock) = ElementCount; //Record the elements

		//Create each position by calling the constructor
		T* Elements = Block;
		for(size_t Index = 0; Index < ElementCount; ++Index)
		{
			(void) new (static_cast<void*>(Elements + Index)) T;
		}

		m_CurrentMemory += TotalSize;
		return Block;
	}
	return NULL;
}

///ARGONDELETEARRAY(VOID)
///
/// Custom Delete array Function
///
///Param Block: The block of data thast will be cleaned
template<typename T> inline void ArgonDeleteArray(T*& DataBlock, const char* Description)
{
	if(DataBlock)
	{
		HeapHandle* HeapHandle = (HeapHandle*)(((char*)DataBlock) - sizeof(HeapHandle));

		if(HeapHandle)
		{
			//Get the Elements
			T* Elements = DataBlock;

			if(Elements)
			{
				//Deallocate each T
				for(size_t Index = 0; Index < HeapHandle->ElementCount; ++Index)
				{
					(Elements + Index)->~T;
				}

				DeAllocate(HeapHandle);
				DataBlock = NULL;
			}
		}
	}
}

#endif //_REFERENCEPOINTER_HEADER_
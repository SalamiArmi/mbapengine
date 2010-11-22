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
#include "ArgonSingleton.h"

namespace Argon
{
	class MemoryAllocator : public singleton<MemoryAllocator>
	{
		friend singleton;
	public:
		typedef size_t				SizeType;
		typedef _w64 int			DifferenceType;

		template<typename OtherAllocator> struct Rebind
		{
			typedef MemoryAllocator Other;
		};

		inline explicit MemoryAllocator()
		{

		}

		inline ~MemoryAllocator()
		{

		}

		inline explicit MemoryAllocator(MemoryAllocator const&)
		{

		}

		template<typename T> inline T* Address(T& Ref)
		{ 
			return &Ref; 
		}

		template<typename T> inline const T* Address(const T& Ref)
		{ 
			return &Ref;
		}

		template<typename T> inline T* Allocate(size_t Size)
		{ 
			return malloc(Size); 
		}

		struct HeapHandle
		{
			size_t ElementCount;	
		};

		template<typename T> inline T* AllocateArray(size_t ElementCount, const char* Description)
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

		template<typename T>inline void DeAllocate(T* Ptr, size_t Size) 
		{ 
			free(Ptr);
			m_CurrentMemory -= Size;
		}

		template<typename T> inline void DeAllocateArray(T*& DataBlock, const char* Description)
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
						m_CurrentMemory -= sizeof(HeapHandle) + HeapHandle->ElementCount * sizeof(T);
						
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

		template<typename T> inline size_t MaxSize() const 
		{ 
			return std::numeric_limits<size_t>::max() / sizeof(T);
		}

		template<typename T>inline void Destroy(T* Ptr)
		{ 
			Ptr->~AllocatorType();
		}

		inline bool operator==(MemoryAllocator const&) 
		{ 
			return true; 
		}

		inline bool operator!=(MemoryAllocator const& Object) 
		{ 
			return !operator==(Object);
		}

	private:
		size_t	m_PeakMemory;
		size_t	m_CurrentMemory;
	};

	template<typename Type> class ValuePtr 
	{
	protected:

		class InternalAllocBase
		{
		public:
			virtual Type* Clone( Type const* ) const = 0;
			virtual void UnLoad( Type* ) const = 0; 
		};

		template< typename Derived > class InternalAllocater : InternalAllocBase
		{
		public:

			Type* Clone( Type const* Ptr ) const
			{
				if(!Ptr) return 0x0; //Ptr is NULL

				Derived* Value = Allocater.Allocate(1);
				try
				{
					Allocater.Construct(Value, *static_cast<Derived const*>(Ptr));
				}
				catch(...)
				{
					Allocator.DeAllocate(Value,1);
				}
				return Value;
			}

			void UnLoad(Type* Ptr) const
			{
				if(Ptr != 0x0)
				{
					Derived* Temp = static_cast<Derived*>(Ptr);
					try
					{
						Allocater.Destroy(Temp);
					}
					catch(...)
					{
						Allocater.DeAllocate(Temp,1);
						throw;
					}
					Allocater.DeAllocate(Temp,1);
				}
			}

			static InternalAllocater Global;
		};

	public:

		template<typename Derived> ValuePtr(Derived* Ptr)
		{
			Load();
			Reset(Ptr);
		}

		ValuePtr(Type* Ptr = 0x0)
		{
			Load();
			Reset(Ptr);
		}

		ValuePtr(ValuePtr const &Rhs)
		{
			Load();
			Reset(Rhs);
		}

		template<typename Derived> ValuePtr& Reset(Derived* Ptr)
		{
			return InternalReset(Ptr, &InternalAllocator<Derived>::Global);
		}

		virtual ~ValuePtr()
		{	
			delete this;
		}

	protected:

		void Load()
		{
			m_Ptr(0x0);
			m_InternalAllocater = &InternalAllocater::Global;
		}

		ValuePtr& InternalReset(Type* Ptr, InternalAllocBase* Alloc)
		{
			
		}

	private:
		Type* m_Ptr;
		InternalAllocBase* m_InternalAllocater;
	};

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

inline void* operator new(size_t sBlockSize, const char* pDescription)
{
    return Argon::MemoryAllocator::instance() ? Argon::MemoryAllocator::instance()->Allocate<void>(sBlockSize) : malloc(sBlockSize);
}


inline void operator delete(void* pBlock, const char* Description)
{
    if (pBlock)
    {
		if (Argon::MemoryAllocator::instance())
			Argon::MemoryAllocator::instance()->DeAllocate(pBlock, sizeof(pBlock));
        else
            free(pBlock);
    }
}

template<typename T> inline T* ArgonNewArray(size_t ElementCount, const char* Description)
{
	return Argon::MemoryAllocator::instance() ? Argon::MemoryAllocator::instance()->AllocateArray<T>(ElementCount, Description) : 0x0;
}

template<typename T> inline void ArgonDeleteArray(T*& pBlock, const char* Description)
{
	Argon::MemoryAllocator::instance()->DeAllocateArray<T>(pBlock, Description)
}

#endif //_REFERENCEPOINTER_HEADER_
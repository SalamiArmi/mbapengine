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

#include "Windows.h"
#include <algorithm> // for std::swap

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

	template< typename AllocatorType > class MemoryAllocator
	{
	public:
		typedef AllocatorType ValueType;
		typedef ValueType* Pointer;
		typedef const ValueType* ConstPointer;
		typedef ValueType& Reference;
		typedef const ValueType& ConstReference;
		typedef size_t SizeType;
		typedef _w64 int DifferenceType;

		template< typename OtherAllocator > struct Rebind
		{
			typedef MemoryAllocator< AllocatorType > Other;
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

		template<typename U>
		inline explicit MemoryAllocator(MemoryAllocator<U> const&) 
		{

		}

		inline Pointer Address(Reference Ref)
		{ 
			return &Ref; 
		}

		inline ConstPointer Address(ConstReference Ref)
		{ 
			return &Ref;
		}

		inline Pointer Allocate(SizeType Count)
		{ 
			return reinterpret_cast<Pointer>(::operator new(Count * sizeof (AllocatorType))); 
		}

		inline void DeAllocate(Pointer Ptr, SizeType) 
		{ 
			::operator delete(Ptr); 
		}

		inline SizeType MaxSize() const 
		{ 
			return std::numeric_limits<SizeType>::max() / sizeof(AllocatorType);
		}

		inline void Construct(Pointer Ptr, const AllocatorType& Type)
		{ 
			new(Ptr) AllocatorType(Type); 
		}

		inline void Destroy(Pointer Ptr)
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

	};

	template<typename Type> class RefPtr
	{
	public:
		RefPtr() :
		  m_RefCount(0x1),
			  m_Ptr(new Type())
		  {

		  }

		  void AddRef()
		  {
			  InterlockedIncrement(&m_RefCount);
		  }

		  void RemoveRef()
		  {
			  --m_RefCount;
			  if(m_RefCount == 0)
				  UnLoad();
		  }

		  RefPtr* Get()
		  {
			  AddRef();
			  return this;
		  }

		  bool operator!() const 
		  { 
			  return !m_ptr; 
		  }

		  RefPtr<Type>& operator=(const RefPtr<Type>& Rhs)
		  {
			  Type* optr = Rhs.Get();
			  if (optr)
				  optr->AddRef();
			  Type* ptr = m_Ptr;
			  m_Ptr = optr;
			  if (ptr)
				  ptr->RemoveRef();
			  return *this;
		  }

		  RefPtr<Type>& operator=(Type* optr)
		  {
			  if (optr)
				  optr->Type();
			  T* ptr = m_ptr;
			  m_Ptr = optr;
			  if (ptr)
				  ptr->RemoveRef();
			  return *this;
		  }

		  Type& operator *() const
		  {
			  return *m_Ptr;
		  }

		  Type* operator->() const
		  {
			  return m_Ptr;
		  }

	private:

		virtual ~RefPtr()
		{
			RemoveRef();
		}

		void UnLoad()
		{
			delete m_Ptr;
			m_RefCount = 0;
		}

		Type*			m_Ptr;
		volatile long   m_RefCount;
	};

	template<class Type> inline void swap(Type& Left, Type& Right)
	{	//exchange values stored at Left and Right
		if (&Left != &Right)
		{	// different, worth swapping
			Type Temp = Left;

			Left = Right;
			Right = Temp;
		}
	}

	template<typename Type, typename ValuePtrAllocater = MemoryAllocator<Type>> class ValuePtr 
	{
	public:

		ValuePtr()
		{

		}

	protected:

		class BaseAlloc
		{
		public:

			virtual Type* clone( Type const* ) const = 0;

			virtual void UnLoad( Type* ) const = 0;
		};


		template< typename Derived > class InternalAllocater : public BaseAlloc
		{
		public:

			Type* Clone( Type const* Ptr ) const
			{
				if(!Ptr) return 0x0; //Ptr is NULL

				Derived* Value = ValuePtrAllocater.Allocate(1);
				try
				{
					PtrAllocator.Construct( Value, *static_cast<Derived const*>(Ptr));
				}
				catch(...)
				{
					PtrAllocator.DeAllocate(Value,1);
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
						PtrAllocator.Destroy(Temp);
					}
					catch(...)
					{
						PtrAllocator.DeAllocate(Temp,1);
						throw;
					}
					PtrAllocator.DeAllocate(Temp,1);
				}
			}

			static InternalAllocater Global;
			static typename ValuePtrAllocater::template Rebind<Derived>::Other PtrAllocator;
		};

		public:

		template<typename Derived> ValuePtr(Derived* Ptr)
		{
			Load();
			Reset(Ptr);
		}

		ValuePtr(Type* Ptr = 0)
		{
			Load();
			Reset(Ptr);
		}

		ValuePtr(ValuePtr const& Rhs)
		{
			Load();
			Reset(Rhs);
		}

		template<typename Derived> ValuePtr& Reset(Derived* Ptr)
		{
			return InternalReset(Ptr, &InternalAllocater<Derived>::Global);
		}

		template<typename Derived> ValuePtr& Allocate(Derived* const &Value = Derived())
		{
			return Reset(static_cast<Derived*>(InternalAllocater<Derived>::Global.Clode(&Value)));
		}

		inline ValuePtr& Allocate()
		{
			return Allocate<Type>();
		}

		template<typename Derived> ValuePtr& operator =(Derived* Ptr)
		{
			return InternalReset(Ptr, &InternalAllocater<Derived>::Global);
		}

		inline Type& operator*()
		{
			return *m_Ptr;
		}

		inline Type const& operator*() const
		{
			return *m_Ptr;
		}

		inline Type* operator->()
		{
			return m_Ptr;
		}

		inline Type* const operator->() const
		{
			return m_Ptr;
		}

		friend void Swap(ValuePtr& Lhs, ValuePtr& Rhs)
		{
			swap(Lhs.m_Ptr, Rhs.m_Ptr);
			swap(Lhs.m_InternalAllocater, Rhs.m_InternalAllocater);
		}

		Type* Orphan()
		{
			Type* Temp = m_Ptr;
			m_Ptr = 0x0;
			return Temp;
		}

		virtual ~ValuePtr()
		{	
			Reset(m_Ptr);
		}

	protected:

		void Load()
		{
			m_Ptr = 0x0;
			m_InternalAllocater = &InternalAllocater<Type>::Global;
		}


		ValuePtr& InternalReset(Type* Ptr, BaseAlloc* InternalAlloc)
		{
			std::swap(m_Ptr, Ptr);
			std::swap(m_InternalAllocater, InternalAlloc);
			InternalAlloc->UnLoad(Ptr);
			return *this;
		}

	private:
		Type* m_Ptr;
		BaseAlloc* m_InternalAllocater;
	};

	template < typename Type, typename Allocator > template < typename Derived > typename ValuePtr< Type, Allocator >::template InternalAllocater< Derived > ValuePtr< Type, Allocator >::InternalAllocator< Derived >::Global 
		= typename ValuePtr< Type, Allocator >::template InternalAllocator< Derived >( ); 	

	template < typename Type, typename Allocator > template < typename Derived > typename Allocator::template Rebind< Derived >::Other ValuePtr< Type, Allocator >::InternalAllocater< Derived >::Allocater	
		= typename Allocator::template Rebind< Derived >::Other();

}

#endif //_REFERENCEPOINTER_HEADER_
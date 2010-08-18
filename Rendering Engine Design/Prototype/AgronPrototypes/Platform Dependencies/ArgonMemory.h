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
			typedef Allocator< AllocatorType > Other;
		};

		inline explicit MemoryAllocator()
		{

		}

		inline ~MemoryAllocator()
		{

		}

		inline explicit MemoryAllocator(Allocator const&)
		{

		}

		template<typename U>
		inline explicit MemoryAllocator(Allocator<U> const&) 
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

	template< typename Type, typename Allocater = MemoryAllocator<Type> > class ValuePtr 
	{
	public:

		ValuePtr()
		{

		}

		template< typename Derived > class InternalAllocater
		{
		public:

			Type* Clone( Type const* Ptr ) const
			{
				if(!Ptr) return 0x0; //Ptr is NULL

				Derived* Value = Allocater.Allocate(1);
				try
				{
					Allocater.Construct( Value, *static_cast<Derived const*>(Ptr));
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
			static typename Allocater::template Rebind<Derived>::Other allocator;
		};


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

	private:
		Type* m_Ptr;
		InternalAllocater* m_InternalAllocater;
	};

	template<typename Type, typename Allocater> template<typename Derived> typename ValuePtr<Type, Allocater>::template InternalAllocater<Derived> ValuePtr<Type, Allocater>::InternalAllocator<Derived>::Global = 
		typename ValuePtr<Type, Allocater>::template InternalAllocater<Derived>();

	template < typename Type, typename Allocator > template < typename Derived > template Allocater::template Rebind<Derived>::Other ValuePtr<Type, Allocater>::InternalAllocater<Derived>::Allocater = 
		typename Allocater::template Rebind<Derived>::Other();

}

#endif //_REFERENCEPOINTER_HEADER_
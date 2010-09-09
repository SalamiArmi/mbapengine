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
		InternalAllocater* m_InternalAllocater;
	};

	template < typename Type, typename Allocator > 
	template < typename Derived > 
	typename ValuePtr< Type, Allocator >::template InternalAllocater< Derived >
		ValuePtr< Type, Allocator >::InternalAllocator< Derived >::Global 
		= typename ValuePtr< Type, Allocator >::template InternalAllocator< Derived >( ); 	

	template < typename Type, typename Allocator > 
	template < typename Derived > 
	typename Allocator::template Rebind< Derived >::Other 
		ValuePtr< Type, Allocator >::InternalAllocater< Derived >::Allocater	
		= typename Allocator::template Rebind< Derived >::other( );
}

#endif //_REFERENCEPOINTER_HEADER_
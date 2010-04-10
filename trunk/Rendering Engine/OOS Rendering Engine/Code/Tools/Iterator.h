#ifndef _ITERATOR_HEADER_
#define _ITERATOR_HEADER_

#include <iterator>

namespace OOS
{

	template< typename T > class Iterator : public std::iterator<std::input_iterator_tag, T>
	{
	public:
		~Iterator() 
		{
		}

		///(VOID)
		///
		///Create a new Iterator
		///
		///Params ptr: The ptr to the item being used as the iterator
		Iterator(T* ptr) : m_Ptr(ptr)
		{
			++m_Ptr;
		}

		Iterator()
		{
		}

		inline Iterator(Iterator& it) : m_Ptr(it.m_Ptr)
		{
		}

		inline OOS::Iterator<T>& operator++(int)
		{
			++m_Ptr;
			return *this;
		}

		inline bool operator ==( const OOS::Iterator<T>& rhs )
		{
			return m_Ptr == rhs.m_Ptr;
		}


		inline bool operator !=( const OOS::Iterator<T> &rhs )
		{
			return m_Ptr != rhs.m_Ptr;
		}

		inline void operator=(T &rhs)
		{
			*m_Ptr = rhs;
		}

		inline T& operator *() 
		{
			return *m_Ptr;
		}

	private:

		T* m_Ptr;

	};
}

#endif //_ITERATOR_HEADER_
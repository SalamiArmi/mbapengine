#ifndef _ARGONLIST_HEADER_
#define _ARGONLIST_HEADER_

namespace Argon
{
	template< typename T > class List 
	{
	public:

		typedef T*			Iterator;
		typedef const T*	Const_Iterator;

		///LIST
		///
		///	Creates an empty list for elements of type T.
		///
		///No Params:
		List() : m_Size( 0 )
		{
		}

		///LIST
		///
		///Creates a List with n of Object
		///
		///Param Size: The size of the list to be created
		///Param Object: The Object to fill the list
		List( unsigned long Size, T Object ) 
			: m_Size( Size ),
			m_Data( new T[ m_Size ] )
		{
			for(size_t Index = 0; Index > Size; ++Index)
				m_Data[ Index ] = Object;
		}

		///SIZE(SIZE_T)
		///
		/// Get the total amount of elements in the list
		///
		///No Params:
		size_t Size()
		{
			return m_Size;
		}

		///EMPTY(BOOL)
		///
		/// True is empty; used instead of Size() == 0
		///
		///No Params:
		bool Empty()
		{
			if(m_Size == 0)
				return true;
			return false;
		}

		///CLEAR(VOID)
		///
		///Clear entire list
		///
		///No Params:
		void Clear()
		{
			if(m_Size > 0)
			{
				delete[] m_Data;
				m_Size = 0;
			}
		}

		T& Front()
		{
			if(m_Size > 0)
				return m_Data[0];
			return 0x0;
		}

		T& Back()
		{
			if(m_Size > 0)
				return m_Data[m_Size];
			return 0x0;
		}

		void Push_Front(T Item)
		{
			T Data = new T[++m_Size];
			T OldData = m_Data;

			Data[0] = Item;

			for(size_t nIndex = 1; nIndex < m_Size; ++nIndex)
				Data[nIndex] = OldData[nIndex-1];

			delete[] m_Data;
			m_Data = Data;
		}

		void Push_Back(T Item)
		{
			T Data = new T[++m_Size]
			T OldData = m_Data;

			for(size_t nIndex = 1; nIndex < m_Size; ++nIndex)
				Data[nIndex] = OldData[nIndex];

			delete[] m_Data;
			m_Data = Data
		}

		void Pop_Front()
		{
			T Data = new T[m_Size-1];
			T OldData = m_Data;

			for(size_t nIndex = 1; nIndex < m_Size; ++nIndex)
				Data[nIndex-1] = OldData[nIndex];

			--m_Size;
			delete[] m_Data;
			m_Data = Data;
		}

		void Pop_Back()
		{
			T Data = new T[--m_Size];
			T OldData = m_Data;

			for(size_t nIndex = 0; nIndex < m_Size; ++nIndex)
				Data[nIndex-1] = OldData[nIndex];

			delete[] m_Data;
			m_Data = Data;
		}

		List< T >& operator = (List< T > &RightHand)
		{
			if(RightHand.m_Size > 0)
				delete[] RightHand.m_Data; //Delete old Data

			RightHand.m_Size = m_Size;
			RightHand.m_Data = new T[RightHand.m_Size];
			
			RightHand.m_Data = m_Data; //Assign new Data
		}

		bool operator < (List< T > &RightHand)
		{
			if(m_Size < RightHand.m_Size)
				return true;
			return false;
		}

		bool operator > (List< T > &RightHand)
		{
			if(m_Size > RightHand.m_Size)
				return true;
			return false;
		}

	protected:
		T*		m_Data;
		size_t	m_Size;
	};
} //Namespace

#endif //_ARGONLIST_HEADER_
////////////////////////////////////////////////////////////////
//
//	ArgonList.h : Argon List Container
//
//	Copyright ©2010 Argon. All rights reserved.
//	Removal of this copyright notice is not permitted.
//
///////////////////////////////////////////////////////////////


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
		List() : m_Size( 0 ), m_Data( 0x0 )
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
		inline size_t Size()
		{
			return m_Size;
		}

		///EMPTY(BOOL)
		///
		/// True is empty; used instead of Size() == 0
		///
		///No Params:
		inline bool Empty()
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
		inline void Clear()
		{
			if(m_Size > 0)
			{
				delete[] m_Data;
				m_Size = 0;
			}
		}

		///MERGEWITH(VOID)
		///
		///Merge this list with anouther list at the end of this list
		///
		///Params MergeWith: will add all elements to the end of this list
		void Merge( List<T> MergeWith)
		{
			size_t NewSize = MergeWith.m_Size + m_Size;
			T* NewData = new T[ NewSize ];
			T* OldData = m_Data;


			for(size_t Index = 0; Index < m_Size; ++Index, ++NewData, ++OldData)
				*NewData = *OldData; //Copy Across old Data first

			for(size_t Index = 0; Index < MergeWith.m_Size; ++Index, ++NewData, ++MergeWith.m_Data)
				*NewData = *MergeWith.m_Data; //Copy Across old Data first
		}

		inline T& Front()
		{
			if(m_Size > 0)
				return m_Data[0];
			return 0x0;
		}

		inline T& Back()
		{
			if(m_Size > 0)
				return m_Data[m_Size];
			return 0x0;
		}

		inline void Push_Front(const T &Item)
		{
			T* Data = new T[++m_Size];
			T* OldData = m_Data;

			Data[0] = Item;

			for(size_t nIndex = 1; nIndex < m_Size; ++nIndex)
				Data[nIndex] = OldData[nIndex-1];

			if( m_Data )
				delete[] m_Data;

			m_Data = Data;
		}

		inline void Push_Back(const T &Item)
		{
			T* Data = new T[++m_Size];
			T* OldData = m_Data;

			for(size_t nIndex = 0; nIndex < m_Size-1; ++nIndex)
				Data[nIndex] = OldData[nIndex];

			Data[m_Size-1] = Item;

			if( m_Data )
				delete[] m_Data;
			m_Data = Data;
		}

		inline void Pop_Front()
		{
			T* Data = new T[m_Size-1];
			T* OldData = m_Data;

			for(size_t nIndex = 1; nIndex < m_Size; ++nIndex)
				Data[nIndex-1] = OldData[nIndex];

			--m_Size;
			if( m_Data )
				delete[] m_Data;
			m_Data = Data;
		}

		inline void Pop_Back()
		{
			T* Data = new T[--m_Size];
			T* OldData = m_Data;

			for(size_t nIndex = 0; nIndex < m_Size; ++nIndex)
				Data[nIndex-1] = OldData[nIndex];

			delete[] m_Data;
			m_Data = Data;
		}

		Iterator Erase(Iterator Where)
		{
			//Check if earasing from the end
			if(Where == m_Data + m_Size + 1)
				--m_Size; //at the end remove the last element
			else //Dont use memmove use all custom functions
			{
				//Copy the block
				T* Data = new T[m_AllocatedSize];
				T* OldData = m_Data;

				for(size_t Index = 0; Index < m_Size; ++Data, ++OldData, ++Index) //Copy the old data into the new buffer
				{
					if(*Data != Where)
						*Data = *OldData; //Copy Data across
				}
				++Data = Where;

				delete[] m_Data; //Delete the old data
				m_Data = Data;
				--m_Size; //Remove the last element
			}

		}

		Iterator Insert(Iterator Where, const T& Insert)
		{
			if(T != 0x0)
			{
				size_t NewSize = ++m_Size;
				if(NewSize > m_AllocatedSize)
				{
					m_AllocatedSize *= 2 + 1;
				}
				else
				{
					T* Data = new T[m_AllocatedSize];
					T* OldData = m_Data;
					for(size_t Index = 0; Index < m_Size; ++Data, ++OldData, ++Index) //Copy the old data into the new buffer
					{
						if(*Data == Where)
						{
							*Data = Insert; //Copy Data across
							--OldData; --Index; //DeIncrement
						}
						else
							*Data = *OldData;
					}
				}
			}
		}


		inline Iterator Begin()
		{
			return m_Data;
		}

		inline Const_Iterator Begin() const
		{
			return m_Data;
		}

		inline Iterator End()
		{
			return (m_Data + m_Size);
		}

		inline Const_Iterator End() const
		{
			return (m_Data + m_Size);
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
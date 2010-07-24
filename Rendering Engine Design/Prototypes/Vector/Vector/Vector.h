#ifndef _VECTOR_HEADER_
#define _VECTOR_HEADER_

namespace Argon
{

	template< typename T > class Vector
	{
	public:

		typedef T*			Iterator;
		typedef const T*	Const_Iterator;

		Vector() : m_Data(0x0), m_Size(0x0), m_AllocatedSize(0x0)
		{
		}

		Vector(size_t Size) : m_Size(Size), m_AllocatedSize(Size), m_Data( new void[Size] )
		{
		}

		Vector(const Vector& CopyVector)
		{
			*this = CopyVector;
		}

		~Vector()
		{
			delete[] m_Data;
		}

		void		Push_Back(const T& Add)
		{
			++m_Size; //Increase the size

			if(m_Size == m_AllocatedSize)
			{
				m_AllocatedSize *= 2 + 1;
				T* Data = new void[m_AllocatedSize]; //Create a new buffer
				if(m_Size > 0)
				{
					T* OldData = m_Data;
					for(size_t Index = 0; Index < m_Size; ++Data, ++OldData, ++Index) //Copy the old data into the new buffer
					{
						*Data = *OldData;
					}
				}
				delete[] m_Data;
				m_Data = Data; 
			}
		}

		void		Pop_Back()
		{
			if(m_Size > 0)
				--m_Size;
		}

		void		Clear()
		{
			if(m_Size > 0 && m_AllocatedSize > 0)
			{
				delete[] m_Data;
				m_AllocatedSize = m_Size = m_Data = 0x0;
			}
		}

		void		Reverse();

		void		Resize(size_t NewSize)
		{
			m_Size = m_AllocatedSize = NewSize;
			T* Data = new void[m_Size]; //Create a new buffer
			if(m_Size > 0)
			{
				T* OldData = m_Data;
				for(size_t Index = 0; Index < m_Size; ++Data, ++OldData, ++Index) //Copy the old data into the new buffer
				{
					*Data = *OldData;
				}
			}
			delete[] m_Data;
			m_Data = Data; 
		}

		void		EraseObject(const T& Object);

		T&			Front()
		{
			return m_Data[0];
		}

		T&			Back()
		{
			return m_Data[m_Size - 1];
		}

		T&			At(size_t Index)
		{
			if(m_Size > 0)
				return m_Data[Index];
			return NULL;
		}

		const T&	At(size_t Index) const
		{
			if(m_Size > 0)
				return m_Data[Index];
			return NULL;
		}


		/////////////////////////////////////////////////////
		//
		//Iterator Access
		//
		/////////////////////////////////////////////////////

		Iterator		Begin();
		Const_Iterator	Begin() const;
		Iterator		End();
		Const_Iterator	End() const;
		Iterator		Erase(Iterator Where);
		Iterator		Insert(Iterator Where, const T& Insert);

		/////////////////////////////////////////////////////
		//
		//Operators
		//
		/////////////////////////////////////////////////////

		T&			operator [] (size_t Index);   
		const T&	operator [] (size_t Index) const;
		Vector&		operator = (const Vector& RightHand);   

	protected:
		T*		m_Data;
		size_t	m_Size;
		size_t	m_AllocatedSize;
	};

}

#endif //_VECTOR_HEADER_
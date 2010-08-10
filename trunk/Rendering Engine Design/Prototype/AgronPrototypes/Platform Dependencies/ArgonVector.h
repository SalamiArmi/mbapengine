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

		Vector(size_t Size) : m_Size(Size), m_AllocatedSize(Size), m_Data( new T[Size] )
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

		size_t		Size()
		{
			return m_Size;
		}

		void		Push_Back(const T& Add)
		{
			if(m_Size == m_AllocatedSize)
			{
				m_AllocatedSize = (m_AllocatedSize * 2) + 1;
				T* Data = new T[m_AllocatedSize]; //Create a new buffer
				if(m_Size > 0 && m_Data)
				{
					T* OldData = m_Data;
					memcpy(Data, OldData, m_Size * sizeof(T)); //Copy the old data into the new buffer
					delete[] m_Data;
					m_Data = 0x0;
				}
				m_Data = Data; 
			}

			m_Data[m_Size++] = Add;
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
			T* Data = new T[m_Size]; //Create a new buffer
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

		Iterator		Begin()
		{
			return m_Data;
		}

		Const_Iterator	Begin() const
		{
			return m_Data;
		}

		Iterator		End()
		{
			return (m_Data + m_Size);
		}

		Const_Iterator	End() const
		{
			return (m_Data + m_Size);
		}

		Iterator		Erase(Iterator Where)
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

		Iterator		Insert(Iterator Where, const T& Insert)
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

		/////////////////////////////////////////////////////
		//
		//Operators
		//
		/////////////////////////////////////////////////////

		T&			operator [] (size_t Index)
		{
			if(Index < m_Size)
				return m_Data[Index];
			return 0x0;
		}

		const T&	operator [] (size_t Index) const
		{
			if(Index < m_Size)
				return m_Data[Index];
			return 0x0;
		}

		Vector&		operator = (const Vector& RightHand)
		{
			if(RightHand.m_Size > m_AllocatedSize)
			{
				T* Data = new T[RightHand.m_Size];
				delete[] m_Data;
				m_Data = Data;
				m_AllocatedSize = RightHand.m_Size;
			}

			m_Size = RightHand.m_Size;
			if(RightHand.m_Size > 0)
			{
				T* Data = m_Data;
				T* OldData = RightHand.m_Data;
				for(size_t Index = 0; Index < m_Size; ++Data, ++OldData, ++Index) //Copy the old data into the new buffer
					*Data = *OldData;
			}
			return *this;
		}

	protected:
		T*		m_Data;
		size_t	m_Size;
		size_t	m_AllocatedSize;
	};

}

#endif //_VECTOR_HEADER_
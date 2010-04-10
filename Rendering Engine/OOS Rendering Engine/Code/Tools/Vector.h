#ifndef _STACK_HEADER_
#define _STACK_HEADER_

#include "Iterator.h"
#include "BaseIteratableObject.h"

namespace OOS
{

	template <typename T> class Vector : public BaseIterableObject<T>
	{
	public:

		///Vector(VOID)
		///
		///Create a new Vector Container
		///
		///No Params:
		Vector()
		{
			m_Top = 0;
			m_Empty = true;
			m_Values =  new T [ m_Top ];
		}

		///~Vector(VOID)
		///
		///Delete the container
		///
		///No Params:
		~Vector()
		{
		}

		///PUSH_BACK(BOOLEAN)
		///
		///Add a Item to the top of the container
		///
		///Param T: Template Type of the item being added
		inline bool push_Back(T Item)
		{
			m_Values [m_Top++] = Item;
			return true;
		}

		///POP_BACK(BOOLEAN)
		///
		///Remove the top element off the container
		///
		///No Params:
		inline bool pop_back()
		{
			if ( !m_Empty )
			{
				Item = m_Stack[top--];

				if ( m_Top == 0 || m_Count == 0 )
				{
					m_Empty = true;
				}

				return true;
			}
			return false;
		}

		///REMOVE(BOOLEAN)
		///
		///Remove the item from the container
		///
		///Param item: The item being removed
		inline const bool remove( T &item ) const
		{
			for ( int index = 0; index < m_Top; ++index )
			{
				if ( m_Stack[ index ] == item )
				{
					removeAt(index);
				}
			}
		}

		///EMPTY(BOOLEAN)
		///
		///Empty the container and all its contenst
		///
		///No Params:
		inline const bool Empty() const
		{
			while ( m_Top > 0 )
			{
				m_Values[top--];

				if ( m_Top == 0 || m_Count == 0 )
				{
					m_Empty = true;
				}
			}
		}

		///GETLAST(TEMPLATE)
		///
		///Get the last item in the container
		///
		///No Params:
		inline const OOS::Iterator<T> end() const
		{
			return &m_Values[ m_Top - 1 ];
		}

		///(VOID)
		///
		///Access the item at the Indexed position
		///
		///Param Index: The position of the item being retrieved
		inline const T at(int Index) const
		{
			return *(&m_Values[ Index ] );
		}

		///FIRST(TEMPLATE)
		///
		///Get the first item in the list
		///
		///No Params:
		inline const T First() const
		{
			return (* ( m_Values[ 0 ] ) );
		}

				///FIRST(TEMPLATE)
		///
		///Get the first item in the list
		///
		///No Params:
		inline const T Last() const
		{
			return (* ( m_Values[ m_Top ] ) );
		}


		inline const OOS::Iterator<T> Begin() const
		{
			return &m_Values[ 0 ];
		}

		typedef OOS::Iterator<T> Iterator;
		typedef const OOS::Iterator<T> Const_Iterator;

	private:

	};

}

#endif //_STACK_HEADER_
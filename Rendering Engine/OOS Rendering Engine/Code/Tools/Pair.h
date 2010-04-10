#ifndef _MAP_HEADER_
#define _MAP_HEADER_

#include "BaseIteratableObject.h"

namespace OOS
{
	template <typename Keys, typename Values> class Pair : public OOS::BaseIterableObject<Values>
	{
	public:

		Pair()
		{
			m_Top = 0;
			m_Empty = true;
			m_Keys = new Keys [ m_Top ];
			m_Values = new Values [ m_Top ];
		}

		~Pair()
		{
			if ( m_Keys )
			{
				delete m_Keys;
			}
		}

		inline bool add(Keys Key, Values Value)
		{
			m_Keys [ m_Top ] = Key;
			m_Values [ m_Top++ ] = Value;

			if ( m_Top > 0 )
				m_Empty = false;

			return true;
		}

		inline bool remove(Keys Key)
		{
			if ( !isEmpty() )
			{

				for ( unsigned int index = 0; index < m_Top; ++index )
				{
					if ( m_Keys[index] == Key )
					{
						
						while ( index < m_Top )
						{
							m_Keys [ index ] = m_Keys [ index + 1 ];
							m_Values [ index ] = m_Values [ index + 1 ];
							++index;
						}

						m_Top--;

						if ( m_Top == 0 )
						{
							m_Empty = true;
						}

						return true;
					}
				}

			}
			return false;
		}

		const inline Keys KeyAt( int index ) const
		{
			return *( &m_Keys[ index ] );
		}

		const inline Values ValuesAt ( int index ) const
		{
			return  *( &m_Values [ index ] );
		}	

	protected:

		Keys* m_Keys;

	};

}

#endif //_MAP_HEADER_
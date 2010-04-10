#ifndef _BASEITERATABLEOBJECT_HEADER_
#define _BASEITERATABLEOBJECT_HEADER_

namespace OOS
{

	template < typename T > class BaseIterableObject
	{
	public:

		virtual ~BaseIterableObject()
		{
			delete m_Values;
		}

		///ISEMPTY(BOOLEAN)
		///
		///Is the container empty
		///
		///No Params:
		const bool isEmpty() const
		{
			return m_Empty;
		}

		///GETCOUNT(INTEGER)
		///
		///Get the current capicaty of the container
		///
		///No Params:
		const unsigned int Count() const
		{
			return m_Top;
		}

		///REMOVEAT(BOOLEAN)
		///
		///Remove the item at the indexed position
		///
		///Params Index: The position to remove the item
		inline bool removeAt(int Index)
		{
			while ( Index != m_Top )
			{
				m_Values[ Index ] = m_Values[ Index++ ];
				++Index;
			}
			return true;
		}

	protected:

		//The stack of the items
		T* m_Values;

		//The top of the container
		unsigned int m_Top;

		//Is the container empty
		bool m_Empty;
	};

}
#endif //_BASEITERATABLEOBJECT_HEADER_
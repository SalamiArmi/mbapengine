#define _FACTORY_HEADER_
#ifdef _FACTORY_HEADER_

#include "Vector.h"

namespace OOS
{
	template<typename T> class Factory
	{
	public:
		virtual ~Factory() {  }

		static T CreateType( )
		{
			T temp = new T();
			m_FactoryObjects.push_Back(temp);
		}

		static void destoryCreatedTypes( T Type )
		{
			for ( unsigned int index = 0; index < m_FactoryObjects.Count(); ++index )
			{
				delete m_FactoryObjects.at(index);
			}
		}

	protected:
		Vector<T> m_FactoryObjects;
	};
}

#endif //_VISUALFACTORY_HEADER_
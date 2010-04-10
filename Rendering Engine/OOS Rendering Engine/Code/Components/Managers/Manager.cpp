#include "Manager.h"
#include "Resource.h"
#include "Assert.h"
#include "System.h"

namespace OOS
{
	Manager::Manager( )
	{
		System::getSingleton().registorManager( this );
	}

	Manager::~Manager( )
	{

	}

	bool Manager::update ( )
	{
		return true;
	}

	bool Manager::Contains( std::string File )
	{
		for ( unsigned short index = 0; index < m_Resources.Count(); ++index )
		{
			if ( m_Resources.at( index )->getName() == File )
				return true;
		}
	
		return false;
	}

	bool Manager::Contains( Resource* Resource )
	{
		for ( unsigned short index = 0; index < m_Resources.Count(); ++index )
		{
			if ( m_Resources.at( index ) == Resource )
				return true;
		}
	
		return false;
	}

	Resource* Manager::getResource( unsigned short Index )
	{
		assert( Index < m_Resources.Count() );

		return m_Resources.at( Index );
	}
}
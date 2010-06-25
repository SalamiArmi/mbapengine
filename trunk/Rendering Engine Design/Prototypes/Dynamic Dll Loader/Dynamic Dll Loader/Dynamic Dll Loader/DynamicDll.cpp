#include "DynamicDll.h"

typedef void ( *EntryPoint ) ( int a, const char* b );

DynamicDllLoader::DynamicDllLoader( char* Name )
: m_Name( Name )
{

}

bool DynamicDllLoader::Load()
{
	//Scan directory
	HINSTANCE pModule = LoadLibraryExA( "BigZBot.dll", 0x0, 0x0 );
	if ( pModule )
	{
		EntryPoint LibEntryPoint = (EntryPoint)GetProcAddress( pModule, "AEntry" );
		if ( LibEntryPoint )
		{
			LibEntryPoint( 0x0, "Enter Here" );
			//do more things
		}
	}
	return true;
}

void DynamicDllLoader::UnLoad()
{
	for ( USHORT nIndex = 0; nIndex < m_DllInstances.size(); ++nIndex )
	{
		FreeLibrary( m_DllInstances.at( nIndex ) );
	}
}
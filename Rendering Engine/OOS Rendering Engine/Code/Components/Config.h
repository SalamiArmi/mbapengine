#ifndef _CONFIG_HEADER_
#define _CONFIG_HEADER_

namespace OOS
{
//Remove to import
#	define OOS_NONCLIENT_BUILD

#	if defined( _WIN32 )  
#		define OOS_PLATFORM_WIN32
#	endif


#	if defined OOS_PLATFORM_WIN32
#		if defined( OOS_NONCLIENT_BUILD )
#			define _OOSExport __declspec ( dllexport )
#		else
#			define _OOSExport __declspec ( dllimport )
#		endif
#	endif

}

#endif //_CONFIG_HEADER_
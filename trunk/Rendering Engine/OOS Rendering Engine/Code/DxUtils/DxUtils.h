#ifndef _DXUTILS_HEADER_
#define _DXUTILS_HEADER_

#include <memory>

namespace OOS
{

	template<class T> struct AutoZero : public T
	{
		AutoZero()
		{
			memset( this, 0, sizeof( T ) );
		}
	};

	template<class T> inline void SafeRelease( T& Face )
	{
		if ( Face )
		{
			Face->Release();
			Face = NULL;
		}
	}

}

#endif //_DXUTILS_HEADER_
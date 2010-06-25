#ifndef _DYANAMICDLL_HEADER_
#define _DYANAMICDLL_HEADER_

#include "Windows.h"
#include <vector>

class DynamicDllLoader // : public IUnknownImpl< I
{
public:
	DynamicDllLoader( char* Name );
	~DynamicDllLoader( );

	bool Load( );
	void UnLoad( );

protected:
	std::vector< HINSTANCE >	m_DllInstances;
	char*						m_Name;
};

#endif //_DYANAMICDLL_HEADER_

#include "DynamicDll.h"

int main()
{
	DynamicDllLoader* A = new DynamicDllLoader( "AAA" );
	A->Load();
		
	return 0;
}
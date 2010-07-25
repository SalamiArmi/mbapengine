#include "Vector.h"

#include <iostream>

int main()
{

	Argon::Vector< int > pp;

	for(int i = 0; i < 500; ++i)
	{
		pp.Push_Back(i);
	}

	for(Argon::Vector< int >::Iterator it = pp.Begin(); it != pp.End(); ++it)
		std::cout << *it << std::endl;

	return 0;
}
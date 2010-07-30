#include "ArgonVector.h"
#include "ArgonList.h"

#include <iostream>

int main()
{

	Argon::Vector< int > pp;
	Argon::List< int > ll;

	for(int i = 0; i < 500; ++i)
	{
		pp.Push_Back(i);
		ll.Push_Front( i );
	}

	for(Argon::Vector< int >::Iterator it = pp.Begin(); it != pp.End(); ++it)
	{
		std::cout << *it << std::endl;
	}

	for(Argon::List< int >::Iterator it = ll.Begin(); it != ll.End(); ++it)
		std::cout << *it << std::endl;

	return 0;
}
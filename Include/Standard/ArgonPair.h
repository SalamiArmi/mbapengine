#ifndef _ARGONPAIR_HEADER_
#define _ARGONPAIR_HEADER_

namespace Argon
{
	template<class T, class T2> class Pair
	{
	public:
		typedef T		FirstType;
		typedef T2		SecondType;

		inline Pair()	
			: First( NULL ),
			Second( NULL )
		{
		}

		inline Pair(const T& first, const T2& second)
			: First( first ),
			Second( second )
		{

		}

		template<class Other, class Other2> inline Pair(const Pair<Other, Other2>& Right)
			: First(Right.First), 
			Second(Right.Second)
		{

		}

		~Pair()
		{

		}

		T				First;
		T2				Second;
	};


	template<class Type1, class Type2> 
	inline Pair<Type1, Type2> MakePair(Type1 First, Type2 Second)
	{
		return (Pair<Type1, Type2>(First, Second));
	}

} //Namespace

#endif //_ARGONPAIR_HEADER_
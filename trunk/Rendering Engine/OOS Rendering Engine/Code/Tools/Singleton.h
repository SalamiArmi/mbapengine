#ifndef _SINGLETON_HEADER_
#define _SINGLETON_HEADER_

#include "assert.h"

namespace OOS
{

	template <typename T> class Singleton
	{
	public:
		Singleton()
		{
			assert(!mSingleton);
			mSingleton = static_cast<T*>(this);
		}

		~Singleton()
		{
		}

		///GET FUNCTION
		///Retrieve a referance of the singleton
		static T& getSingleton()
		{
			assert(mSingleton);
			return (*mSingleton);
		}

		static inline void destroySingleton()
		{
			delete mSingleton;
			mSingleton = 0;
		}

	protected:
		static T* mSingleton;
	};

	template<typename T> T* Singleton<T>::mSingleton = 0;

}

#endif //_SINGLETON_HEADER_

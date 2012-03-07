////////////////////////////////////////////////////////////////
//
//	ArgonSingleton.h :
//
//	Copyright ©2010 Argon. All rights reserved.
//	Removal of this copyright notice is not permitted.
//
///////////////////////////////////////////////////////////////


#ifndef _ARGONSINGLETON_HEADER_
#define _ARGONSINGLETON_HEADER_

#include "assert.h"

namespace Argon
{

	template <typename T> 
	class singleton
	{
	public:

		// Gets a reference to the instance of the singleton class.
		//
		//	returns a reference to the instance of the singleton class.
		//	If there is no instance of the class yet, one will be created.
		static T* instance()
		{
			if (m_instance == 0)
			{
				m_instance = new T;
			}

			assert(m_instance != 0);

			return m_instance;
		}

		// Destroys the singleton class instance.

		//	Be aware that all references to the single class instance will be
		//	invalid after this method has been executed!
		static inline void destroyInstance()
		{
			delete m_instance;
			m_instance = 0;
		}

	protected:

		// Default constructor.
		inline singleton()
		{
		}

		// Destructor
		inline virtual ~singleton()
		{
		}

	protected:

		// Copy constructor.
		inline singleton(const singleton& source)
		{
		}

		// singleton class instance
		static T* m_instance;
	};

	// static class member initialisation.
	template <typename T>
	T* singleton<T>::m_instance = 0;
}
#endif //_ARGONSINGLETON_HEADER_

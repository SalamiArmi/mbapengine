#ifndef _ARGONQSTRINGCREATOR_HEADER_
#define _ARGONQSTRINGCREATOR_HEADER_

#include "ArgonQString.h"
#include "ArgonPlatform.h"
#include "ArgonMap.h"
#include "ArgonVector.h"
#include "ArgonSingleton.h"
#include "ArgonString.h"

template<typename T, typename AllocatorT>class QStringCreator;

namespace Argon
{
	template< typename T > class QStringT
	{
	public:
		QStringT(T String) //Calls QStringCreator to check if string exists
		{
			m_String = QStringCreator<T, Allocator<T>>::instance()->CreateString(String);
		}

		QStringT(String aString)
		{
		}

		~QStringT()
		{

		}

	protected:
		T m_String;
	};

	template<typename T, typename AllocatorT> class QStringCreator : public singleton<QStringCreator<T,AllocatorT>>
	{
		friend singleton;
	public:
		QStringCreator()
		{
		}

		~QStringCreator()
		{
			
		}

		///CreateString(T)
		///
		///Create a new string and if already exists add a referance to the list
		///
		///Param String: The type of string to be looking for
		T CreateString(T String, QStringT<T>* Referance) const
		{
			//Check if the string exists
			for(Map<const T, Vector<QStringT<T>>>::container it = m_Referances.First(); it != m_Referances.Last(); ++it)
			{
				if((*it).m_Key == String)
				{
					(*it).m_Data.Push_Back(Referance);
					return (*it).m_Key;
				}
			}
	
			//Store Current String
			Vector< QStringT<T>* > StoreVector;
			StoreVector.Push_Back(Referance);
			T StoreString = m_Allocator->Allocate(m_Allocator->Length(String));
			for(size_t Index = 0; Index < m_Allocator->Length(String); ++Index)
				StoreString[Index] = String[Index];
			m_Referances.Insert(StoreString, StoreVector);

			return StoreString;
		}


		bool DestroyString(T String, QStringT<T> Referance)
		{
			Map< const T, Vector<QStringT<T>*>>::container it = m_Referances.First();
			for(ulong Index = 0; it != m_Referances.Last(); ++it, ++Index)
			{
				if((*it).m_Key == String)
				{
					(*it).m_Data.Erase((*it).m_Data.Begin() + Index);
					if((*it).m_Data.Size())
					{
						delete (*it);
						m_Referances.Erase(it);
					}	
					return true;
				}
			}

			return false;
		}

	protected:

	private:
		Map<const T, Vector<QStringT<T>>> m_Referances;
		AllocatorT* m_Allocator;
	};
}

#endif //_ARGONQSTRINGCREATOR_HEADER_
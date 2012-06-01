////////////////////////////////////////////////////////////////
//
//	ArgonQString.h :
//
//	Copyright ©2010 Argon. All rights reserved.
//	Removal of this copyright notice is not permitted.
//
///////////////////////////////////////////////////////////////

#ifndef _ARGONQSTRINGCREATOR_HEADER_
#define _ARGONQSTRINGCREATOR_HEADER_

#include "ArgonPlatform.h"
#include "ArgonPair.h"
#include "ArgonVector.h"
#include "ArgonSingleton.h"
#include "ArgonString.h"

template<typename T, typename AllocatorT>class QStringCreator;

namespace Argon
{
	template<typename T> class QStringT
	{
	public:

		QStringT() : m_String( NULL )
		{

		}

		QStringT(T String)
		{
			m_String = QStringCreator<T, CharAllocator>::instance()->CreateString(String);				//If string already exists dont make a new one
			m_Length = QStringCreator<T, CharAllocator>::instance()->GetAllocator()->Length(m_String); //Get the Length of the String
		}

		QStringT(String String)
		{
			m_String = QStringCreator<T, CharAllocator>::instance()->CreateString(String.c_str());				//If string already exists dont make a new one
			m_Length = String.Length();
		}

		~QStringT()
		{
		}

		unsigned long Length()
		{
			return m_Length;
		}

		const T c_str() 
		{
			return m_String;
		}

		bool operator ==(QStringT<T> LHS)
		{
			if(QStringCreator<T, CharAllocator>::instance()->GetAllocator()->Length(m_String) != QStringCreator<T, CharAllocator>::instance()->GetAllocator()->Length(LHS.m_String))
				return false;
			for(size_t Index = 0; Index < QStringCreator<T, CharAllocator>::instance()->GetAllocator()->Length(m_String); ++Index)
				if(m_String[Index] != LHS.m_String[Index])
					return false;
			return true;
		}

		bool operator ==(T LHS)
		{
			if(QStringCreator<T, CharAllocator>::instance()->GetAllocator()->Length(m_String)-1 != QStringCreator<T, CharAllocator>::instance()->GetAllocator()->Length(LHS))
				return false;
			for(size_t Index = 0; Index < QStringCreator<T, CharAllocator>::instance()->GetAllocator()->Length(m_String); ++Index)
				if(m_String[Index] != LHS[Index] && LHS[Index] != '\0')
					return false;
			return true;
		}

		bool operator !=(QStringT<T> LHS)
		{
			if(QStringCreator<T, CharAllocator>::instance()->GetAllocator()->Length(m_String) == QStringCreator<T, CharAllocator>::instance()->GetAllocator()->Length(LHS.m_String))
			{
				for(size_t Index = 0; Index < QStringCreator<T, CharAllocator>::instance()->GetAllocator()->Length(m_String); ++Index)
					if(m_String[Index] == LHS.m_String[Index])
						return false;
			}
			return true;
		}

		bool operator !=(T LHS)
		{
			if(QStringCreator<T, CharAllocator>::instance()->GetAllocator()->Length(m_String)-1 == QStringCreator<T, CharAllocator>::instance()->GetAllocator()->Length(LHS))
			{
				for(size_t Index = 0; Index < QStringCreator<T, CharAllocator>::instance()->GetAllocator()->Length(m_String); ++Index)
					if(m_String[Index] == LHS[Index] && LHS[Index] != '\0')
						return false;
			}
			return true;
		}

	protected:
		T				m_String;
		unsigned long	m_Length;
	};

	typedef QStringT<char*> QString;
	typedef QStringT<wchar_t*> wQString;


	template<typename T, typename AllocatorT> class QStringCreator : public singleton<QStringCreator<T,AllocatorT>>
	{
		friend singleton;
	public:
		QStringCreator() : m_Allocator( new AllocatorT )
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
		T CreateString(T String)
		{
			//Check if the string exists
			if( m_Referances.Size() > 0 )
			{
				for(Vector<T>::Const_Iterator it = m_Referances.Begin(); it != m_Referances.End(); ++it)
					if(strcmp((*it), String) == 0)
						return (*it);
			}
	
			//Store Current String
			size_t Length = m_Allocator->Length(String);
			T StoreString = m_Allocator->Allocate(Length);
			memcpy(StoreString, String, Length);
			m_Referances.Push_Back(StoreString); //Add the exitsing String
			
			return StoreString;
		}


		bool DestroyString(T String, QStringT<T> Referance)
		{
			if(!m_Referances.IsEmpty())
			{
				Vector<Pair<const T, Vector<QStringT<T>>>>::Const_Iterator it = m_Referances.Begin();
				for(ulong Index = 0; it != m_Referances.End(); ++it, ++Index)
				{
					if((*it).First == String)
					{
						(*it).Second->Erase((*it).Second.Begin() + Index)8
						if((*it).Second.Size() == 0)
						{
							delete (*it).First;
							m_Referances.Erase(it);
						}	
						return true;
					}
				}
			}
			return false;
		}

		AllocatorT* GetAllocator()
		{
			return m_Allocator;
		}

	protected:

	private:
		Vector<T> m_Referances;
		AllocatorT* m_Allocator;
	};

	typedef QStringCreator<char*, CharAllocator> CharQStringAllocator;
	typedef QStringCreator<wchar_t*, WideCharacterAllocator> WideQStringAllocator;
}

#endif //_ARGONQSTRINGCREATOR_HEADER_
#ifndef _ARGONQSTRING_HEADER
#define _ARGONQSTRING_HEADER

#include "String.h"

namespace Argon
{
	//class String;
	class Map;
	//class Singleton;

	template< typename T >class QStringCreator // : Singleton<QStringCreator>
	{
	public:
		QStringCreator();
		~QStringCreator();

		T CreateString(T String) const; //Create a new string and if already exists add a referance to the list
		T DestroyString(T String, QString< T > Referance);

	protected:

	private:
		bool DoesStringExist(QString String);
		Map< const T, Vector > m_Referances; //All referances that the char*

	template< typename T > class QStringT
	{
	public:
		QStringT(const T String); //Calls QStringCreator to check if string exists
		{
			//m_String = QStringCreator< T >::GetSingleton()->CreateString( String );
		}

		QStringT(T String)
		{

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
}

#endif //_ARGONQSTRING_HEADER
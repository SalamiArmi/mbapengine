#ifndef _ARGONQSTRING_HEADER
#define _ARGONQSTRING_HEADER

namespace Argon
{
	class String;
	class Map;
	class Singleton;

	class QStringCreator : Singleton<QStringCreator>
	{
	public:
		QStringCreator();
		~QStringCreator();

		const char* CreateString( const char* String ) const; //Create a new string and if already exists add a referance to the list

	protected:

	private:
		bool DoesStringExist(QString String);
		Map< const char*, Vector > m_Referances; //All referances that the char*

	class QString
	{
	public:
		QString(const char* String); //Calls QStringCreator to check if string exists
		QString(String aString);
		~QString();

	protected:
		char* m_String;
	};
}

#endif //_ARGONQSTRING_HEADER
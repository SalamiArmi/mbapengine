#ifndef _ARGONLOG_HEADER_
#define _ARGONLOG_HEADER_

#include <fstream>

#include "ArgonQString.h"
#include "ArgonVector.h"
#include "ArgonStandard.h"

#include <stdio.h>

#pragma warning(disable: 4251) //Disable any Standard linking warnings

namespace Argon
{
	class ArgonStandard Log 
	{
	public:
		enum LogType
		{
			LOGTYPE_File	= 1 << 0,	//Stream to File
			LOGTYPE_CMD		= 1 << 1,	//Stream to Cmd prompt window
		};

		enum LogLevel
		{
			LOGLEVEL_Error = 0,		//Errors this can cause the program to bebug break
			LOGLEVEL_Warning,		//Any warnings that must be addressed
			LOGLEVEL_Debug,			//Any information that could be useful to view for trouble shooting
			LOGLEVEL_Preformance,	//Any preformance information
			LOGLEVEL_Internal,		//All Internal being Render Systems and Platform
		};

	public:
		///LOG(CONSTRUCTOR)
		///
		///Create a new log
		///
		///Param Name: The name of this log file also used as the file
		///Param Type: The Type of logging system this will be, Default = File
		Log(QString Name, LogType Type = LOGTYPE_File);

		///LOG(DESTRUCTOR)
		///
		///Destory the Log
		///
		///No Params:
		~Log();

		///LOAD(BOOL)
		///
		///Load the Log file this will create any needed streams
		///
		///No Params:
		bool Load();

		///UNLOAD(BOOL)
		///
		///Cleanup any Streams
		///
		///No Params:
		bool Unload();

		///SETOUTPUTTYPE(VOID)
		///
		///Set the type of output the application will show
		///
		///
		///Param Type: What type of log will be used, by default set to file
 		void SetOuputType(LogType Type);

		///GETOUTPUTTYPE(LOGTYPE)
		///
		///Get the current log type
		///
		///
		///No Params:
		LogType GetOutputType() const;

		///LOGMESSAGE(VOID)
		///
		///Log the desired message to the desired output
		///
		///Param Message:
		void LogMessage(String& Message);

		///LOGMESSAGE(VOID)
		///
		///Log the message to the desired log type
		///
		///Param Message: 
		void LogMessage(const char* Message);

		///LOGMESSAGE(VOID)
		///
		///Log a message used for advanced message logging
		///
		///Param Level: The level of the log information
		///Param Message: The Message that will be logged
		///Param FileName: Internal use, to display the filename that the error occured in
		///Param Function: Internal use, to display the function the message occured in
		///Param Line: The line of code the error occured in
		void LogMessage(LogLevel Level, String Message, const char* FileName, const char* Function);

		///OPERATOR<<(LOG*)
		///
		///Log the message to the desired log type
		/// 
		///Param Message: The message that will be loged once operator has been called
		Log* operator<<(String Message);
		
		///OPERATOR<<(LOG*)
		///
		///Log a message to the log using the shift operators
		///
		///Param Message: Log the message to the designated type
		Log* operator<<(const char* Message);

		///GETLOG(LOG)
		///
		///Get a log, all logs are stored once it is created
		///
		///Param Name: The name of the log
		///Param Create: Create a new log if not found
		static Log* GetLog(QString Name, bool Create = false);

	protected:
		QString					m_Name;			//The name of this Log Messager
		LogType					m_LogType;		//LogType
		HWND					m_Cmd;			//Comand Window
		std::fstream			m_FileStream;	//The file that will be used for logging to a file

		static Vector<Log*>		m_LogList;		//All the currently created logs
	};
#if defined _DEBUG
#	define ARGONERROR(LogName, Message) Log* Log = Log::GetLog(LogName); \
		if(Log) Log->LogMessage(Log::LOGLEVEL_Error, Message, __FILE__, __FUNCTION__);
#else
#	define ARGONERROR(LogName, Message)
#endif
} //Namespace
#endif //_ARGONLOG_HEADER_
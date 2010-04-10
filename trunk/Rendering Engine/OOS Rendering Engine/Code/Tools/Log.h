#ifndef _LOG_HEADER
#define _LOG_HEADER

#include <fstream>
#include <string>
#include "Stream.h"


namespace OOS
{
	enum LogFormat
	{
		Date_Time_Message = 0,
		Date_Time_Type_Message,
		Type_Message,
		Message,
	};

	enum LogType
	{
		None = 0,
		Error,
		Completed,
		CallBack
	};


	class Log
	{
	public:

		///(VOID)
		///
		///
		///
		///
		///No Params:
		Log(const std::string &name, LogFormat format = Date_Time_Message, bool debugOutput = true);

		///(VOID)
		///
		///
		///
		///No Params:
		~Log();

		///LOGMESSAGE(VOID)
		///
		///Log a message to the log file
		///
		///Param message: The message to be loged to the file
		///Param messageLevel: The heigher the log instance
		void LogMessage(const std::string& message, OOS::LogMessageLevel messageLevel = Medium, bool outputDebugData = true, LogType Type = None);

		///SETDEBUGOUTPUTENABLED(VOID)
		///
		///Set if log is sent to the debug window
		///
		///Param debugOutput: The enable streaming to the console window
		void setDebugOutputEnabled(bool debugOutput);

		///SETLOGFORMAT(VOID)
		///
		///Set the type of format this log file is written with
		///
		///Param format: The type of format the log is written with
		void setLogFormat(LogFormat format);

		///GETLOGFORMAT(LOGFORMAT)
		///
		///Get the current status of the log file that the file is written with
		///
		///No Params:
		LogFormat getLogFormat();

		///GETDEBUGOUTPUTENABLED(BOOLEAN)
		///
		///Get if the log outputs to the console window
		///
		///No Params:
		bool getDebugOutputEnabled();

		template < typename T >	Log* operator << (const T& rhs)
		{
			m_Stream->getCache() << rhs;
			return this;
		}


	private:

		std::string ConvertType(OOS::LogType Type);

	protected:

		std::ofstream 	m_FPLog;

		Stream 			*m_Stream;

		std::string 	m_LogName;
		LogFormat 		m_Format;
		bool 			m_DebugOutput;

	};

}

#endif //_LOG_HEADER
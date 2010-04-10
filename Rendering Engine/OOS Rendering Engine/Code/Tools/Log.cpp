#include "Log.h"
#include <Windows.h>
#include <time.h>
#include <iostream>

namespace OOS
{

	Log::Log(const std::string &name, LogFormat format, bool debugOutput) : m_LogName(name), m_Format(format), m_DebugOutput(debugOutput)
	{
		m_FPLog.open(name.c_str());
		m_Stream = new Stream(this);
	}

	void Log::LogMessage(const std::string& message, OOS::LogMessageLevel messageLevel, bool outputDebugData, LogType Type)
	{
		//Get any Format Data needed before Writing the log
		//TIME and DATE
		time_t rawtime;
		struct tm * timeinfo;

		time ( &rawtime );
		timeinfo = localtime ( &rawtime );

		std::string messageType;

		switch ( m_Format )
		{
		case Date_Time_Message:

			//Write the time and Date
			m_FPLog.write( asctime (timeinfo), strlen( asctime (timeinfo) ) );

			if ( outputDebugData )
			{
				std::cout << asctime (timeinfo) << std::endl;
			}

			break;

		case Date_Time_Type_Message:

			//Write the time and Date
			m_FPLog.write( asctime (timeinfo), strlen( asctime (timeinfo) ) );

			//Type String
			messageType = ConvertType(Type);

			//Write the type to the log
			m_FPLog.write(messageType.c_str(), messageType.length());

			if ( outputDebugData )
			{
				std::cout << asctime (timeinfo) << std::endl;
			}

			break;

		case Type_Message:

			//Type String
			messageType = ConvertType(Type);

			//Write the type to the log
			m_FPLog.write(messageType.c_str(), messageType.length());

			if ( outputDebugData )
			{
				std::cout << messageType << std::endl;
			}

			break;

		}

		//Write the log message
		m_FPLog.write(message.c_str(), message.length());

		if ( outputDebugData )
		{
			std::cout << message << std::endl;
		}

		//Finally write the new line
		m_FPLog.write("\n", strlen("\n"));
	}

	std::string Log::ConvertType(OOS::LogType Type)
	{
		//The type of message being logged
		switch ( Type )
		{
		case None:
			return " [NONE] ";
		case Error:
			return " [ERROR] ";
		case Completed:
			return " [COMPLETE] ";
		case CallBack:
			return " [CALLBACK] ";
		}
		return "";
	}
}
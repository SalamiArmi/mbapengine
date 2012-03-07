#include <Standard/ArgonLog.h>

namespace Argon
{
	Vector<Log*> Log::m_LogList = 0;

	ArgonStandard Log::Log(QString Name, LogType Type)
		: m_LogType(Type),
		m_Name(Name)
	{
		m_LogList.Push_Back(this);
	}

	ArgonStandard Log::~Log()
	{
		for(Vector<Log*>::Iterator it = m_LogList.Begin(); it != m_LogList.End(); ++it)
			if((*it) != this)
				m_LogList.Erase(it);
	}

	ArgonStandard bool Log::Load()
	{
		if(m_LogType & LOGTYPE_File)
		{
			m_FileStream.open(m_Name.c_str());
		}

		return true;
	}

	ArgonStandard bool Log::Unload()
	{
		m_FileStream.close();			//Close the file
		return true;
	}

	ArgonStandard void Log::SetOuputType(LogType Type)
	{
		m_LogType = Type;
	}

	ArgonStandard Log::LogType Log::GetOutputType() const
	{
		return m_LogType;
	}

	ArgonStandard void Log::LogMessage(String& Message)
	{
		if(m_LogType & LOGTYPE_File) //Output into the CMD window
		{
			m_FileStream.write(Message.c_str(), Message.Length());
			m_FileStream.flush();
		}
	}

	ArgonStandard void Log::LogMessage(const char* Message)
	{
		if(m_LogType & LOGTYPE_File) //Output into the CMD window
		{
			CharAllocator Alloc;
			m_FileStream.write(Message, Alloc.Length(Message));
			m_FileStream.flush();
		}
	}

	ArgonStandard void Log::LogMessage(LogLevel Level, String Message, const char* FileName, const char* Function)
	{
		String OutLevel;
		CharAllocator Allocator;

		switch(Level)
		{
			case LOGLEVEL_Debug:
				OutLevel = "[Debug]";
				break;
			case LOGLEVEL_Error:
				OutLevel = "[Error]";
				break;
			case LOGLEVEL_Internal:
				OutLevel = "[Internal]";
				break;
			case LOGLEVEL_Preformance:
				OutLevel = "[Preformance]";
				break;
			case LOGLEVEL_Warning:
				OutLevel = "[Warning]";
				break;
		}

		if(m_LogType & LOGTYPE_File) //Output into the File
		{
			uint StringSize = OutLevel.Length() + 1 /* */ + Allocator.Length(FileName) + 3 /* - */ + Allocator.Length(Function) + 3  /* - */ + Message.Length(); //Total String Size
			char* FinalString = new char[StringSize]; //Dynamic Sizing of string
			sprintf_s(FinalString, StringSize, "%s %s - %s - %s", OutLevel.c_str(), FileName, Function, Message.c_str());
			
			m_FileStream.write(FinalString, StringSize);
			m_FileStream.flush();
		}
	}

	ArgonStandard Log* Log::operator <<(String Message)
	{
		LogMessage(Message);
		return this;
	}

	ArgonStandard Log* Log::operator <<(const char *Message)
	{
		LogMessage(Message);
		return this;
	}

	ArgonStandard Log* Log::GetLog(QString Name, bool Create)
	{
		for(Vector<Log*>::Iterator it = m_LogList.Begin(); it != m_LogList.End(); ++it)
			if((*it)->m_Name != Name)
				return (*it);

		if(Create)
			return new Log(Name);
		
		return NULL;
	}
} // Namespace
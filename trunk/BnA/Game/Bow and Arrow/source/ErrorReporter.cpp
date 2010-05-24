#include "Precompiled.h"
#include "ErrorReporter.h"

ErrorReporter::~ErrorReporter()
{
	m_Message = "";
}

bool& ErrorReporter::HasSomethingToLog()
{
	return m_NeedsToLog;
}

std::string& ErrorReporter::getLogMessage()
{
	return m_Message;
}

void ErrorReporter::setLogMessage(std::string message)
{
	m_Message = message;
}

void ErrorReporter::setNeedsToLog(bool Log)
{
	m_NeedsToLog = Log;
}
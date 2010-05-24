#ifndef _ERRORREPORTER_HEADER_
#define _ERRORREPORTER_HEADER_

#include <string>

class ErrorReporter
{
public:

	virtual ~ErrorReporter();

	void setNeedsToLog(bool Log);
	bool& HasSomethingToLog();
	std::string &getLogMessage();

	void setLogMessage(std::string message);

protected:

	std::string m_Message;
	bool m_NeedsToLog;
	
};

#endif //_ERRORREPORTER_HEADER_
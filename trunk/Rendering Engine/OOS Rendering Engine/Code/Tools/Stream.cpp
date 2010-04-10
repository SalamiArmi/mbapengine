#include "Stream.h"
#include "Log.h"

namespace OOS
{

	Stream::Stream(Log* Target) : m_TargetLog(Target)
	{
	}

	Stream::Stream(Log* Target, bool outputDebugData) :  m_TargetLog(Target), m_OutputDebugData(outputDebugData)
	{

	}

	Stream::Stream(Log* Target, LogMessageLevel level, bool outputDebugData) : m_TargetLog(Target), m_OutputDebugData(outputDebugData), m_Level(level)
	{

	}

	std::ostringstream &Stream::getCache()
	{
		return m_Cache;
	}

	Stream::~Stream()
	{
		if ( m_Cache.tellp() > 0 )
		{
			m_TargetLog->LogMessage(m_Cache.str());
		}
	}
}
#ifndef _STREAM_HEADER_
#define _STREAM_HEADER_

#include <sstream>

namespace OOS
{
	class Log;

	enum LogMessageLevel
	{
		Low = 0,
		Medium,
		High,
		Critical,
		LogMessage_Size
	};


	class Stream
	{
	public:

		Stream(OOS::Log* Target);
		Stream(OOS::Log* Target, bool outputDebugData);
		Stream(OOS::Log* Target, LogMessageLevel level, bool outputDebugData);

		~Stream();

		std::ostringstream &getCache();

		template < typename T >	Stream& operator << (const T& rhs)
		{
			m_Cache << value;
			return *this;
		}

	protected:

		std::ostringstream m_Cache;

		Log* m_TargetLog;

		LogMessageLevel m_Level;

		bool m_OutputDebugData;

	};

}

#endif //_STREAM_HEADER_
#ifndef _ARGONEXCEPTION_HEADER_
#define _ARGONEXCEPTION_HEADER_

#include <iostream>

namespace Argon
{
	class Exception : public std::exception
	{
	public:

		enum ExcpetionType
		{
			EXCEPTIONTYPE_Critical,
			EXCEPTIONTYPE_Rendering,
			EXCEPTIONTYPE_Logic,
			EXCEPTIONTYPE_Unknown,
		};

		Exception() throw()
			: m_Reason(""),
			m_Line(0),
			m_Function(""),
			m_Source("")
		{
		}

		Exception(const Exception& exp) throw()
			: m_Reason(exp.m_Reason),
			m_Line(exp.m_Line),
			m_Function(exp.m_Function),
			m_Source(exp.m_Source)
		{
		}

		Exception(int Line, char* Function, char* Reason, char* Source, ExcpetionType Type = EXCEPTIONTYPE_Unknown) throw()
			: m_Reason(Reason),
			m_Line(Line),
			m_Function(Function),
			m_Source(Source),
			m_Type(Type)
		{
		}

		~Exception() throw()
		{
		}

		const char* Reason() const throw()
		{
			return m_Reason;
		}

		ExcpetionType Type() const throw()
		{
			return m_Type;
		}

		int Line() const
		{
			return m_Line;
		}

		const char* Function() const
		{
			return m_Function;
		}

		const char* Source() const
		{
			return m_Source;
		}

	protected:
		int				m_Line;
		char*			m_Function;
		char*			m_Source;
		char*			m_Reason;
		ExcpetionType	m_Type;
	};

} //Namespace

#endif //_ARGONEXCEPTION_HEADER_
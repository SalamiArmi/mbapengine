#ifndef _ARGONSHARED_HEADER_
#define _ARGONSHARED_HEADER_

namespace Argon
{
	class Shared
	{	
	public:
		long GetReferenceCount() const
		{
			return (m_ReferenceCount);
		}

		long AddReference()
		{
			return (++m_ReferenceCount);
		}

		virtual bool UnLoad()
		{ 
			long Count = --m_ReferenceCount; 
			if (Count == 0) delete this; 
			return (Count == 0);
		}

	private:
		long	m_ReferenceCount;

	protected:
		Shared()
		{
			m_ReferenceCount = 1;
		}

		virtual ~Shared() {}
	};

	template <class Type> class AutoUnLoad
	{		
	public:
		explicit AutoUnLoad(Type *Ptr)
		{
			m_Reference = Ptr;
		}

		AutoUnLoad(const AutoUnLoad& UnLoad)
		{
			m_Reference = AddReference.m_Reference;
			m_Reference->AddReference();
		}

		~AutoRelease()
		{
			m_Reference->UnLoad();
		}

		operator Type*() const
		{
			return (m_Reference);
		}

		Type *const *operator &() const
		{
			return (&m_Reference);
		}

		Type *operator ->() const
		{
			return (m_Reference);
		}

	private:
		Type	*m_Reference;
	};

} //Namespace

#endif //_ARGONSHARED_HEADER_
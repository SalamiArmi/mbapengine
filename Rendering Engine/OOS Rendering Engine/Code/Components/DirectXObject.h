#ifndef _DIRECTXOBJECT_HEADER_
#define _DIRECTXOBJECT_HEADER_

namespace OOS
{

	template<typename T> class DirectxObject
	{
	public:
		virtual ~DirectxObject() { }

		T	getDirectxObject() { return m_DirectxObject; }
		T	*getDirectxObjectRef() { return &m_DirectxObject; }

		const T	getDirectxObject() const { return m_DirectxObject; }
		const T	*getDirectxObjectRef() const { return &m_DirectxObject; }

	protected:

		T m_DirectxObject;

	};

}

#endif //_DIRECTXOBJECT_HEADER_
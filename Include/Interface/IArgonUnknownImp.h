///////////////////////////////////////////////////////////////////////////////////
//
//									Argon Engine
//
//		IArgonUnknownImp.h
//
//		Description: Used to implement one or multiple interfaces to a class
//
//
///////////////////////////////////////////////////////////////////////////////////

#ifndef _IARGONUNKNOWNIMPL_HEADER_
#define _IARGONUNKNOWNIMPL_HEADER_

#include "ArgonInterface.h"

namespace Argon
{
	template<class Class, GUID Type> class IArgonUnknownImp : public Class, public IArgonUnknown
	{
	public:
		///IArgonUnknownImp(VOID)
		///
		///Deletion of this object
		///
		///No Params:
		virtual ~IArgonUnknownImp()
		{
		}

		///QUERYINTERFACE(BOOL)
		///
		///Query a interface and check the types that are implementated on that class if success return true
		///
		///Param GUIDType: The type of interface to compare against
		///Param Out: The object that will be returned
		inline bool QueryInterface(GUID GUIDType, void** Out)
		{
			switch(GUIDType)
			{
			case GUID_IArgonUnknown:
				++m_RefCount;
				*Out = (IArgonUnknown*)this;
				return true;
			case Type:
				++m_RefCount;
				*Out = (Class*)this;
				return true;
			}
			return false;
		}

		///UNLOAD(BOOL)
		///
		///Attempt to release a reference
		///Once the reference is zero automatically cleanup this object
		///If the instance was cleanedup because of zero references will return true else it will return false
		///
		///No Params:
		virtual bool UnLoad()
		{
			if(--m_RefCount == 0)
			{
				delete this;
				return true;
			}
			return false;
		}

		///GETREF(ULONG)
		///
		///Get the current amount of references of this object
		///
		///No Params:
		inline ulong GetRef()
		{
			return m_RefCount;
		}

		///ADDREF(ULONG)
		///
		///Add a reference to this object
		///
		///No Params:
		inline ulong AddRef()
		{
			return ++m_RefCount;
		}

	protected:
		ulong m_RefCount;	//The total amount of references of this object
	};

	template<typename Class, GUID Type, typename Class2, GUID Type2> class IArgonUnknownImp2 : public Class, public Class2, public IArgonUnknown
	{
	public:
		///IArgonUnknownImp(VOID)
		///
		///Deletion of this object
		///
		///No Params:
		virtual ~IArgonUnknownImp2()
		{
		}

		///QUERYINTERFACE(BOOL)
		///
		///Query a interface and check the types that are implementated on that class if success return true
		///
		///Param GUIDType: The type of interface to compare against
		///Param Out: The object that will be returned
		inline bool QueryInterface(GUID GUIDType, void** Out)
		{
			switch(GUIDType)
			{
			case GUID_IArgonUnknown:
				++m_RefCount;
				*Out = (IArgonUnknown*)this;
				return true;
			case Type:
				++m_RefCount;
				*Out = (Class*)this;
				return true;
			case Type2:
				++m_RefCount;
				*Out = (Class2*)this;
				return true;
			}
			return false;
		}

		///UNLOAD(BOOL)
		///
		///Attempt to release a reference
		///Once the reference is zero automatically cleanup this object
		///If the instance was cleanedup because of zero references will return true else it will return false
		///
		///No Params:
		virtual bool Unload()
		{
			if(--m_RefCount == 0)
			{
				delete this;
				return true;
			}
			return false;
		}

		///GETREF(ULONG)
		///
		///Get the current amount of references of this object
		///
		///No Params:
		inline ulong GetRef()
		{
			return m_RefCount;
		}

		///ADDREF(ULONG)
		///
		///Add a reference to this object
		///
		///No Params:
		inline ulong AddRef()
		{
			return ++m_RefCount;
		}

	private:
		
	protected:
		ulong m_RefCount;	//The total amount of references of this object
	};

	template< typename Class, GUID Type, typename Class2, GUID Type2, typename Class3, GUID Type3 > class IArgonUnknownImp3  : public Class, public Class2, public Class3, public IArgonUnknown
	{
	public:
		///IArgonUnknownImp(VOID)
		///
		///Deletion of this object
		///
		///No Params:
		virtual ~IArgonUnknownImp3()
		{
		}

		///QUERYINTERFACE(BOOL)
		///
		///Query a interface and check the types that are implementated on that class if success return true
		///
		///Param GUIDType: The type of interface to compare against
		///Param Out: The object that will be returned
		inline bool QueryInterface(GUID GUIDType, void** Out)
		{
			switch(GUIDType)
			{
			case GUID_IArgonUnknown:
				++m_RefCount;
				*Out = (IArgonUnknown*)this;
				return true;
			case Type:
				++m_RefCount;
				*Out = (Class*)this;
				return true;
			case Type2:
				++m_RefCount;
				*Out = (Class2*)this;
				return true;
			case Type3:
				++m_RefCount;
				*Out = (Class3*)this;
				return true;
			}
			return false;
		}

		///UNLOAD(BOOL)
		///
		///Attempt to release a reference
		///Once the reference is zero automatically cleanup this object
		///If the instance was cleanedup because of zero references will return true else it will return false
		///
		///No Params:
		virtual bool UnLoad()
		{
			if(--m_RefCount == 0)
			{
				delete this;
				return true;
			}
			return false;
		}

		///GETREF(ULONG)
		///
		///Get the current amount of references of this object
		///
		///No Params:
		inline ulong GetRef()
		{
			return m_RefCount;
		}

		///ADDREF(ULONG)
		///
		///Add a reference to this object
		///
		///No Params:
		inline ulong AddRef()
		{
			return ++m_RefCount;
		}

	private:
		
	protected:
		ulong m_RefCount;	//The total amount of references of this object
	};

	template<typename Class, GUID Type, typename Class2, GUID Type2, typename Class3, GUID Type3, typename Class4, GUID Type4> class IArgonUnknownImp4 : public Class, public Class2, public Class3, public Class4, public IArgonUnknown
	{
	public:
		///IArgonUnknownImp(VOID)
		///
		///Deletion of this object
		///
		///No Params:
		virtual ~IArgonUnknownImp4()
		{
		}

		///QUERYINTERFACE(BOOL)
		///
		///Query a interface and check the types that are implementated on that class if success return true
		///
		///Param GUIDType: The type of interface to compare against
		///Param Out: The object that will be returned
		inline bool QueryInterface(GUID GUIDType, void** Out)
		{
			switch(GUIDType)
			{
			case GUID_IArgonUnknown:
				++m_RefCount;
				*Out = (IArgonUnknown*)this;
				return true;
			case Type:
				++m_RefCount;
				*Out = (Class*)this;
				return true;
			case Type2:
				++m_RefCount;
				*Out = (Class2*)this;
				return true;
			case Type3:
				++m_RefCount;
				*Out = (Class3*)this;
				return true;
			case Type4:
				++m_RefCount;
				*Out = (Class4*)this;
				return true;
			}
			return false;
		}

		///UNLOAD(BOOL)
		///
		///Attempt to release a reference
		///Once the reference is zero automatically cleanup this object
		///If the instance was cleanedup because of zero references will return true else it will return false
		///
		///No Params:
		virtual bool UnLoad()
		{
			if(--m_RefCount == 0)
			{
				delete this;
				return true;
			}
			return false;
		}

		///GETREF(ULONG)
		///
		///Get the current amount of references of this object
		///
		///No Params:
		inline ulong GetRef()
		{
			return m_RefCount;
		}

		///ADDREF(ULONG)
		///
		///Add a reference to this object
		///
		///No Params:
		inline ulong AddRef()
		{
			return ++m_RefCount;
		}

	private:
		
	protected:
		ulong m_RefCount;	//The total amount of references of this object
	};
}

#endif //_IARGONUNKNOWNIMPL_HEADER_
#ifndef _ARGONMANAGER_HEADER_
#define _ARGONMANAGER_HEADER_

#include <Standard/ArgonStandard.h>
#include <Standard/ArgonVector.h>
#include <Standard/ArgonString.h>

namespace Argon
{
	template<typename Resource> class Manager
	{
	public:
		virtual ~Manager();

		///GETRESOURCE(RESOURCE)
		///
		///Attempt to get the resource at the desired index
		///
		///Param Index: The Index of the Resource trying to be retrieved
		Resource* GetResource(size_t Index);

		///GETRESOURCE(RESOURCE)
		///
		///Attempt to get the resource at the desired Name
		///
		///Param Index: The name of the Resource trying to be retrieved
		///Param Create: If no resource is found with this Name create it
		Resource* GetResource(String Name, bool Create = false);

		///GETRESOURCECOUNT(SIZE_T)
		///
		///Get how many resources are contained within this manager
		///
		///No Params:
		size_t GetResourceCount();

		///GETRESOURCEINDEX(INTEGER)
		///
		///Attempt to get the Resource's Index with the Name
		///
		///Param Name: The Name of the Resource trying to be retrieved
		int GetResourceIndex(String Name);

		///CONTAINSRESOURCE(BOOL)
		///
		///Does this Manager contain a specific Resource
		///
		///Param Index: The Name of the Resource trying to compare against
		bool ContainsResource(String Name);

		///REMOVERESOURCE(BOOL)
		///
		///Attempt to erase a Resource from this Manager
		///
		///Param Index: The Index of the Resource trying to be removed
		bool RemoveResource(size_t Index);

		///REMOVERESOURCE(BOOL)
		///
		///Attempt to erase a Resource from this Manager
		///
		///Param Index: The Name of the Resource trying to be removed
		bool RemoveResource(String Name);

		///REMOVERESOURCE(BOOL)
		///
		///Attempt to erase a Resource from this Manager
		///
		///Param Index: The Ptr of the Resource trying to be removed
		bool RemoveResource(Resource* Remove);

		///CREATERESOURCE(RESOURCE)
		///
		///Becasue each resource is different no way of knowing how to implement a specific resource
		///so this can be overriden and each manager can now how to create a specific Resource
		///
		///Param Name: The new name of the Resource attempting to be created
		virtual Resource* CreateResource(String Name);

	private:
		Vector<Resource*>	m_Resources;
	}; //Class

#include "ArgonManager.inl"
} //Namespace

#endif //_ARGONMANAGER_HEADER_
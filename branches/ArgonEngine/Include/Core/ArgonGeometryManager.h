#ifndef _ARGONGEOMETRYMANAGER_HEADER_
#define _ARGONGEOMETRYMANAGER_HEADER_

#include <Interface/IComponent.h>

#include "ArgonManager.h"
#include "ArgonGeometryResource.h"

namespace Argon
{
	class GeometryManager : public IArgonUnknownImp2<Manager<GeometryResource>, GUID_IManager, IComponent, GUID_IComponent>
	{
	public:
		GeometryManager();
		~GeometryManager();
		
		///GETNAME(QSTRING)
		///
		///Get the name of the component
		///
		///No Params:
		QString		GetName();

		///CREATERESOURCE(RESOURCE)
		///
		///Because each resource is different no way of knowing how to implement a specific resource
		///so this can be overriden and each manager can now how to create a specific Resource
		///
		///Param Name: The new name of the Resource attempting to be created
		GeometryResource* CreateResource(String Name);

	private:

	}; //Class
} //Namespace

#endif //_ARGONGEOMETRYMANAGER_HEADER_
#ifndef _ARGONGEOMETRYMANAGER_HEADER_
#define _ARGONGEOMETRYMANAGER_HEADER_

#include <Interface/IComponent.h>

#include "ArgonManager.h"
#include "ArgonGeometryResource.h"

namespace Argon
{
	class GeometryManager : public IArgonUnknownImp3<Manager<GeometryResource>, GUID_IManager, IComponent, GUID_IComponent, IFrameListner, GUID_IFrameListner>
	{
	public:
		GeometryManager();
		~GeometryManager();
		
		///LOAD(BOOL)
		///
		///Load the Interface
		///
		///No Params:
		bool Load();

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

		///DRAW(BOOL)
		///
		///Draw the Graphical object
		///
		///Param Pass: The pass that will be preformed
		bool FrameDraw(RenderPass Pass);

		///SUPPORTEDPASS(BOOL)
		///
		///Does the Graphics Support this pass if so make an attempt to render
		///
		///Param Pass: The Pass that will be checked against
		bool SupportsPass(RenderPass Pass);

	private:

	}; //Class
} //Namespace

#endif //_ARGONGEOMETRYMANAGER_HEADER_
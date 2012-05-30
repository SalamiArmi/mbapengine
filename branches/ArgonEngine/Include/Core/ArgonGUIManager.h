#ifndef _ARGONGUIMANAGER_HEADER_
#define _ARGONGUIMANAGER_HEADER_

#include <Interface/IComponent.h>
#include <Interface/ISprite.h>

#include "ArgonManager.h"
#include "ArgonGUIResource.h"

namespace Argon
{
	class GUIManager : public IArgonUnknownImp3<Manager<GUIResource>, GUID_IManager, IComponent, GUID_IComponent, IFrameListner, GUID_IFrameListner>
	{
	public:
		GUIManager();
		~GUIManager();
		
		///GETNAME(QSTRING)
		///
		///Get the name of the component
		///
		///No Params:
		QString GetName();

		///CREATERESOURCE(RESOURCE)
		///
		///Because each resource is different no way of knowing how to implement a specific resource
		///so this can be overriden and each manager can now how to create a specific Resource
		///
		///Param Name: The new name of the Resource attempting to be created
		GUIResource* CreateResource(String Name);

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
		uint		m_MaxSprites;
		ISprite*	m_Sprite;
	}; //Class
} //Namespace

#endif //_ARGONGUIMANAGER_HEADER_
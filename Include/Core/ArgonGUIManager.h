#ifndef _ARGONGUIMANAGER_HEADER_
#define _ARGONGUIMANAGER_HEADER_


#include <Interface/IArgonUnknownImp.h>
#include <Interface/IComponent.h>
#include <Interface/ISprite.h>
#include <Interface/IFrameListner.h>

#include "ArgonManager.h"
#include "ArgonGUIResource.h"

namespace Argon
{
	class GUIManager : public IArgonUnknownImp2<Manager<GUIResource>, GUID_IManager, IComponent, GUID_IComponent>
	{
	public:
		GUIManager();
		~GUIManager();

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
		QString GetName();

		///CREATERESOURCE(RESOURCE)
		///
		///Because each resource is different no way of knowing how to implement a specific resource
		///so this can be overriden and each manager can now how to create a specific Resource
		///
		///Param Name: The new name of the Resource attempting to be created
		GUIResource* CreateResource(String Name);

		///ADDSPRITEINSTANCE(VOID)
		///
		///Add a Sprite instance to this Manager
		///
		///Param Resource: The $GUIResource$ that will be buffered to the RenderQueue
		void AddSpriteInstance(GUIResource* Resource);

		///DRAWBUFFEREDINSTANCES(VOID)
		///
		///Draw all the buffered sprites to the current render target
		///
		///Param Clear: After the sprites have been drawn to the RenderTarget does the buffer clear
		bool DrawBufferedInstances(bool Clear);

	private:

		///REFRESH(VOID)
		///
		///When the renderorder is out of date or a new Resource has been created.
		///
		///No Params:
		void Refresh();

		///QUICKSORT(VOID)
		///
		///Sort all the $GUIResource$'s so that they are drawn in the correct order
		///
		///No Params:
		void QuickSort();

		///SORTPARTITION(INT)
		///
		///Sorts from smallest to largest, so smallest order will be drawn first
		///
		///Param Start:
		///Param End:
		int SortPartition(int Start, int End);

		uint					m_MaxSprites;
		ISprite*				m_Sprite;
		Vector<GUIResource*>	m_SpriteInstances;
	}; //Class
} //Namespace

#endif //_ARGONGUIMANAGER_HEADER_
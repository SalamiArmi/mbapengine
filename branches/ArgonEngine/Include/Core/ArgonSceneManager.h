#ifndef	_SCENEMANAGER_HEADER_
#define _SCENEMANAGER_HEADER_

#include <Interface/IFrameListner.h>
#include <Interface/IComponent.h>
#include <Interface/IArgonUnknownImp.h>
#include <Interface/IDrawable.h>

#include <Standard/ArgonVector.h>

#include <Core/ArgonText.h>
#include <Core/ArgonCamera.h>

namespace Argon
{
	class Root;
	class Entity;
	class GUIResource;

	class SceneManager : public IArgonUnknownImp2<IComponent, GUID_IComponent, IFrameListner, GUID_IFrameListner>
	{
	public:
		SceneManager(QString Name, Root* Creator);
		~SceneManager();

		///LOAD(BOOL)
		///
		/// Load and Initalise all components of this scenemanager
		///
		///No Params:
		bool Load();

		///GETCREATOR(ROOT)
		///
		/// Get the Root whom Created this object
		///
		///No Params:
		Root* GetCreator();

		///GETNAME(QSTRING)
		///
		///Get the name of the component
		///
		///No Params:
		QString GetName();

		///FRAMEUPDATE(VOID)
		///
		/// The frame needs to be updated so that objects are not in the same
		/// Positioin all the Time.
		///
		///Param DeltaT: Time since Last Frame
		bool FrameUpdate(float DeltaT);

		///DRAW(BOOL)
		///
		/// Draw the Graphical object
		///
		///Param Pass: The pass that will be preformed
		bool FrameDraw(RenderPass Pass);

		///SUPPORTEDPASS(BOOL)
		///
		/// Does the Graphics Support this pass if so make an attempt to render
		///
		///Param Pass: The Pass that will be checked against
		bool SupportsPass(RenderPass Pass);

		///CREATECAMERA(CAMERA)
		///
		/// Create a new camera that will contain all required transform information
		///
		///No Params:
		Camera* CreateCamera(String Name);

		///CREATETEXT(CAMERA)
		///
		/// Create a new Text Entity
		///
		///Param Name: The Name of the Text Entity to create
		Text* CreateText(String Name);

		///CREATEGUI(GUIRESOURCE)
		///
		/// Create a new GUI Entity
		///
		///Param Name: The Name of the GUI Entity to create
		GUIResource* CreateGUI(String Name);

		///GETENTITY(ENTITY)
		///
		/// Get any entity that this $SceneManager$ contains
		///
		///Param Name: The Name of the Entity to retreive
		Entity* GetEntity(String EntityName);

	protected:
		Vector<Entity*>			m_Entities;
		Vector<IDrawable*>		m_Renderable;

		Root*					m_Creator;	//The Root which created this Manager
		Entity*					m_RootEntity;
		QString					m_Name;		//The name of the Component
	};

} //Namespace

#endif //_SCENEMANAGER_HEADER_
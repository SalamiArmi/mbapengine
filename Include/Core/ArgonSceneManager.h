#ifndef	_SCENEMANAGER_HEADER_
#define _SCENEMANAGER_HEADER_

#include <Interface/IFrameListner.h>
#include <Interface/IComponent.h>
#include <Interface/IArgonUnknownImp.h>
#include <Interface/IRenderable.h>

#include <Standard/ArgonVector.h>

#include <Core/ArgonRoot.h>
#include <Core/ArgonText.h>
#include <Core/ArgonSceneNode.h>
#include <Core/ArgonCamera.h>


namespace Argon
{
	class Root;
	class SceneNode;

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
		bool			Load();

		///GETCREATOR(ROOT)
		///
		/// Get the Root whom Created this object
		///
		///No Params:
		Root*			GetCreator();

		///GETNAME(QSTRING)
		///
		///Get the name of the component
		///
		///No Params:
		QString			GetName();

		///FRAMEUPDATE(VOID)
		///
		/// The frame needs to be updated so that objects are not in the same
		/// Positioin all the Time.
		///
		///Param DeltaT: Time since Last Frame
		bool			FrameUpdate(float DeltaT);

		///DRAW(BOOL)
		///
		/// Draw the Graphical object
		///
		///Param Pass: The pass that will be preformed
		bool			FrameDraw(RenderPass Pass);

		///SUPPORTEDPASS(BOOL)
		///
		/// Does the Graphics Support this pass if so make an attempt to render
		///
		///Param Pass: The Pass that will be checked against
		bool			SupportsPass(RenderPass Pass);

		///CREATESCENENODE(SCENENODE)
		///
		/// Create a new scene node that will contain all required transform information
		///
		///No Params:
		SceneNode*		CreateSceneNode(QString Name);

		///CREATECAMERA(CAMERA)
		///
		/// Create a new camera that will contain all required transform information
		///
		///No Params:
		Camera*		CreateCamera(QString Name);

		///GETCAMERA(CAMERA)
		///
		/// Get a Camera from the Name
		///
		///No Params:
		Camera*		GetCamera(QString Name);

		///CREATETEXT(CAMERA)
		///
		/// Create a new Text Entity
		///
		///Param Name: The Name of the Text Entity to create
		Text*		CreateText(QString Name);

		///GETTEXT(CAMERA)
		///
		/// Create a new Text Entity
		///
		///Param Name: The Name of the Text Entity to create
		Text*		GetText(QString Name);

	protected:
		Vector<SceneNode*>		m_SceneNodes;
		Vector<Camera*>			m_Cameras;

		Root*					m_Creator;	//The Root which created this Manager
		SceneNode*				m_RootNode;
		QString					m_Name;		//The name of the Component
	};

} //Namespace

#endif //_SCENEMANAGER_HEADER_
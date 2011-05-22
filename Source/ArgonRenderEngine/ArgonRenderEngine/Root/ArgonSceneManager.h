#ifndef	_SCENEMANAGER_HEADER_
#define _SCENEMANAGER_HEADER_

#include <Interface/IFrameListner.h>
#include <Interface/IComponent.h>
#include <Interface/IArgonUnknownImp.h>
#include <Interface/ISceneNode.h>

#include <Standard/ArgonVector.h>

#include "ArgonRoot.h"

namespace Argon
{
	ArgonAPI class SceneManager : public IArgonUnknownImp3<IComponent, GUID_IComponent, IFrameListner, GUID_IFrameListner, ISceneManager, GUID_ISeneManager>
	{
	public:
		SceneManager(QString Name, Root* Creator);
		~SceneManager();

		///(VOID)
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
		IRoot*			GetCreator();

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

		///CREATESCENENODE(ISCENENODE)
		///
		/// Create a new scene node that will contain all required transform information
		///
		///No Params:
		ISceneNode*		CreateSceneNode(QString Name);

	protected:
		Vector<ISceneNode*>	m_SceneNodes;
		

		Root*				m_Creator;	//The Root which created this Manager
		QString				m_Name;		//The name of the Component
	};
} //Namespace

#endif //_SCENEMANAGER_HEADER_
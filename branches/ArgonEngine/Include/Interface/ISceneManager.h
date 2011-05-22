#ifndef _ISCENEMANAGER_HEADER_
#define _ISCENEMANAGER_HEADER_

#include <Standard/ArgonQString.h>

#include "IFrameListner.h"
#include "IArgonUnknown.h"
#include "ISceneNode.h"

namespace Argon
{
	class IRoot;

	DeclareBasedInterface(ISceneManager, IArgonUnknown)
		
		///GETCREATOR(ROOT)
		///
		///Get the Root whom Created this object
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
		///Draw the Graphical object
		///
		///Param Pass: The pass that will be preformed
		bool			FrameDraw(IFrameListner::RenderPass Pass);

		///SUPPORTEDPASS(BOOL)
		///
		///Does the Graphics Support this pass if so make an attempt to render
		///
		///Param Pass: The Pass that will be checked against
		bool			SupportsPass(IFrameListner::RenderPass Pass);

		///CREATESCENENODE(ISCENENODE)
		///
		/// Create a new scene node that will contain all required transform information
		///
		///No Params:
		ISceneNode*		CreateSceneNode(QString Name);

	EndInterface(ISceneManager)

} //Namespace

#endif //_ISCENEMANAGER_HEADER_
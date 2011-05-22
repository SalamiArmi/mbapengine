#ifndef _ISCENENODE_HEADER_
#define _ISCENENODE_HEADER_

#include <Interface/IArgonUnknown.h>
#include <Standard/ArgonVector3.h>
#include <Standard/ArgonQuaternion.h>

namespace Argon
{
	DeclareBasedInterface(ISceneNode, IArgonUnknown)

		///FRAMEDRAW(BOOL)
		///
		/// Draw a new Frame
		///
		///No Params:
		bool FrameDraw() = 0;

		///FRAMEUPDATE(BOOL)
		///
		/// Update the Frame before drawing
		///
		///Param DeltaT: The time between two frames
		bool FrameUpdate(float DeltaT) = 0;

		///(VOID)
		///
		///
		///
		///
		///No Params:
		void SetPosition(Vector3 &Position) = 0;
	
		///(VOID)
		///
		///
		///
		///
		///No Params:
		Vector3 GetPosition() = 0;

		///(VOID)
		///
		///
		///
		///
		///No Params:
		void SetRotation(Vector3 &Rotation) = 0;
		
		///(VOID)
		///
		///
		///
		///
		///No Params:
		Vector3 GetRotation() = 0;

		///(VOID)
		///
		///
		///
		///
		///No Params:
		void SetScale(Vector3 Scale) = 0;

		///(VOID)
		///
		///
		///
		///
		///No Params:
		Vector3 GetScale() = 0;

	EndInterface(ISceneNode)
} //Namespace

#endif //_ISCENENODE_HEADER_
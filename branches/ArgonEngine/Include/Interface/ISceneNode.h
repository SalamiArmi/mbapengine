#ifndef _ISCENENODE_HEADER_
#define _ISCENENODE_HEADER_

#include <Interface/IArgonUnknown.h>
#include <Standard/ArgonVector3.h>
#include <Standard/ArgonQuaternion.h>

namespace Argon
{
	DeclareBasedInterface(ISceneNode, IArgonUnknown)

		///(VOID)
		///
		///
		///
		///
		///No Params:
		void SetPosition(Vector3 &Position);
	
		///(VOID)
		///
		///
		///
		///
		///No Params:
		Vector3 GetPosition();

		///(VOID)
		///
		///
		///
		///
		///No Params:
		void SetRotation(Vector3 &Rotation)
		
		///(VOID)
		///
		///
		///
		///
		///No Params:
		Vector3 GetRotation();

		///(VOID)
		///
		///
		///
		///
		///No Params:
		void SetScale(Vector3 Scale);

		///(VOID)
		///
		///
		///
		///
		///No Params:
		Vector3 GetScale();

	EndInterface(ISceneNode)
} //Namespace

#endif //_ISCENENODE_HEADER_
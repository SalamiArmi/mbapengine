#ifndef _ISCENENODE_HEADER_
#define _ISCENENODE_HEADER_

#include <Interface/IArgonUnknown.h>

#include <Standard/ArgonVector3.h>
#include <Standard/ArgonQuaternion.h>
#include <Standard/ArgonVector.h>

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

		///SETPOSITION(VOID)
		///
		/// Set the Position of the scenenode in the world
		///
		///Params Position: The Position that the node will be moved to
		void SetPosition(Vector3 &Position) = 0;
	
		///GETPOSITION(VECTOR3)
		///
		/// Get the Current Rendering position of the Scenenode
		///
		///No Params:
		Vector3 GetPosition() = 0;

		///SETORIENTATION(VOID)
		///
		/// Set the rotation of the scenenode
		///
		///Params Orientation: The new Rotation in radians
		void SetOrientation(Vector3 &Orientation) = 0;
		
		///GETORIENTATION(VECTOR3)
		///
		/// Get the Orientation in Radians
		///
		///No Params:
		Vector3 GetOrientation() = 0;

		///ROLL(VOID)
		///
		/// A roll is a counterclockwise rotation of gamma about the x-axis
		///
		///Params Radians: The amount to rotate around the X-Axis by
		void Roll(const float& Radians);
		
		///PITCH(VOID)
		///
		/// A pitch is a counterclockwise rotation of Beta about the y-axis.
		///
		///Params Radians: The amount to rotate around the Y-Axis by
		void Picth(const float& Radians);
		
		///YAW(VOID)
		///
		/// A yaw is a counterclockwise rotation of Alpha about the z-axis
		///
		///Params Radians: The amount to rotate around the Z-Axis by
		void Yaw(const float& Radians);

		///SETSCALE(VOID)
		///
		/// Set the scale of the Scenenode
		///
		///Params Scale: The new scale
		void SetScale(Vector3 &Scale) = 0;

		///GETSCALE(VECTOR3)
		///
		/// Get the scale of the Scenenode
		///
		///No Params:
		Vector3 GetScale() = 0;

		///ATTACH(VOID)
		///
		/// Attach a new child scenenode
		///
		///Params Node: The node that will be attached to this node
		void Attach(actual_ISceneNode* Node) = 0;

		///DETACH(VOID)
		///
		/// Detach the desired node from this parent node
		///
		///Param Node: The desired node that will be detached
		void Detach(actual_ISceneNode* Node) = 0;

		///DETACH(VOID)
		///
		/// Detach the desired node from this parent node
		///
		///Params Index: The Index of the desired node that will be detached
		void Detach(size_t Index) = 0;

		///GETCHILDCOUNT(SIZE_T)
		///
		/// Get the total amount of children for this parent
		///
		///No Params:
		size_t GetChildCount() = 0;

		///REMOVEALLCHILDREN(VOID)
		///
		/// Remove all child nodes from this parent
		///
		///No Params:
		void RemoveAllChildren() = 0;

		///GETPARENT(ISCENENODE)
		///
		/// Get the current Parent of this node
		///
		///No Params:
		actual_ISceneNode* GetParent() const = 0;

	EndInterface(ISceneNode)
} //Namespace

#endif //_ISCENENODE_HEADER_
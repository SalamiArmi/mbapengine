#ifndef _SCENENODE_HEADER_
#define _SCENENODE_HEADER_

#include <Core/ArgonTransform.h>
#include <Core/ArgonUpdateTree.h>

#include <Standard/ArgonVector.h>
#include <Standard/ArgonQString.h>
#include <Standard/ArgonQuaternion.h>

#pragma warning(disable : 4251)

namespace Argon
{
	class SceneNode : public Transform, public UpdatableTree<SceneNode>
	{
	public:

		enum NodeFlags
		{
			UpdateTransform			= 1 << 0,
			UpdateBoundingSphere	= 1 << 1,
			UpdateVisibility		= 1 << 3,

			InitialUpdateFlags		= UpdateTransform | UpdateBoundingSphere,

		}; //Enum

		SceneNode(QString Name);
		virtual ~SceneNode();
		
		///GETNAME(QSTRING)
		///
		/// Get the name of the Node or concrete class type
		///
		///No Params:
		QString GetName();

		///FRAMEUPDATE(BOOL)
		///
		/// Update the Frame before drawing
		///
		///Param DeltaT: The time between two frames
		bool FrameUpdate(float DeltaT);

		///SETORIENTATION(VOID)
		///
		/// Set the rotation of the scenenode
		///
		///Params Orientation: The new Rotation in radians
		void SetOrientation(Quaternion &Orientation);
		
		///GETORIENTATION(QUATERNION)
		///
		/// Get the Orientation in Radians
		///
		///No Params:
		Quaternion GetOrientation();

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
		void SetScale(Vector3 &Scale);

		///GETSCALE(VECTOR3)
		///
		/// Get the scale of the Scenenode
		///
		///No Params:
		Vector3 GetScale();

	protected:
		QString					m_Name;
	};
} //Namespace

#endif //_SCENENODE_HEADER_
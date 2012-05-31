#ifndef _ARGONENTITY_HEADER_
#define _ARGONENTITY_HEADER_

#include <Standard/ArgonString.h>
#include <Standard/ArgonQuaternion.h>

#include "ArgonTransform.h"
#include "ArgonUpdateTree.h"

namespace Argon
{
	class Manipulator;
	
	class Entity : public Transformable, public UpdatableTree<Entity>
	{
	public:

		enum NodeFlags
		{
			UpdateTransform			= 1 << 0,
			UpdateBoundingSphere	= 1 << 1,
			UpdateVisibility		= 1 << 3,

			InitialUpdateFlags		= UpdateTransform | UpdateBoundingSphere,

		}; //Enum

		enum Type
		{
			TYPE_Root		= 'ROOT',
			TYPE_Camera		= 'CAMR',
			TYPE_Light		= 'LITE',
			TYPE_Geometry	= 'GEOM',
			TYPE_Effect		= 'EFCT',
			TYPE_Skybox		= 'SKYB',
			TYPE_Animator	= 'ANIM',
			TYPE_GUI		= 'GUI',
			TYPE_Text		= 'TEXT',
		}; //Enum

		Entity(String Name, Type EntityType);
		virtual ~Entity();

		///GETNAME(STRING)
		///
		/// Get the name of the $Entity$. Each name must be unique
		///
		///No Params:
		String GetName();

		///GETTYPE(TYPE)
		///
		/// Get the $Entity$ type
		///
		///No Params:
		Type GetType();

		///DETATCH(BOOL)
		///
		/// Detatch from the $Entity$ that is currently holding the Transformed information
		///
		///No Params:
		bool Detatch();

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

		///SETMANIPULATOR(VOID)
		///
		/// Set the Manipulator that will change the state of the current $Entity$
		///
		///Param Manip: The Manipulator that will change the state of this $Entity$
		void SetManipulator(Manipulator* Manip);

		///GETMANIPULATOR(MANIPULATOR)
		///
		/// Get the Manipulator that will change the state of the current $Entity$
		///
		///No Params:
		Manipulator* GetManipulator();

		///SETRENDERORDER(VOID)
		///
		/// Set the RenderOrder, this will change which $Entity$ will render first to last
		///
		///Param RenderOrder: The new Renderorder position
		void SetRenderOrder(int RenderOrder);

		///GETRENDERORDER(INT)
		///
		/// Get the RenderOrder, this will change which $Entity$ will render first to last
		///
		///No Params:
		int GetRenderOrder();

	private:

		///FRAMEUPDATE(BOOL)
		///
		/// Update the Frame before drawing
		///
		///Param DeltaT: The time between two frames
		bool FrameUpdate(float DeltaT);

		Type					m_Type;
		String					m_Name;
		Manipulator*			m_Manipulator;
		int						m_RenderOrder;
	};
} //Namespace

#endif //_ARGONENTITY_HEADER_
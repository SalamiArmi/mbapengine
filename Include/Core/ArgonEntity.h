#ifndef _ARGONENTITY_HEADER_
#define _ARGONENTITY_HEADER_

namespace Argon
{
	class SceneNode;
	class Manipulator;
	
	class Entity
	{
	public:
		enum Type
		{
			TYPE_Camera		= 'CAMR',
			TYPE_Light		= 'LITE',
			TYPE_Geometry	= 'GEOM',
			TYPE_Effect		= 'EFCT',
			TYPE_Skybox		= 'SKYB',
			TYPE_Animator	= 'ANIM',
		}; //Enum

		Entity(String ResourceName, Type EntityType);

		///DRAW(BOOL)
		///
		///
		///
		///No Params:
		bool Draw();

		///GETTYPE(TYPE)
		///
		/// Get the $SceneNode$ type
		///
		///No Params:
		Type GetType();

		///ATTATCH(BOOL)
		///
		/// Attatch a $Scenenode$ which will allow the entity to have a transform
		///
		///Param Node: The node which will hold all the transformed information
		bool Attatch(SceneNode* Node);

		///DETATCH(BOOL)
		///
		/// Detatch the $Scenenode$ that is currently holding the Transformed information
		///
		///No Params:
		bool Detatch();

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

	private:
		String			m_ResourceName;
		Type			m_Type;
		SceneNode*		m_SceneNode;
		Manipulator*	m_Manipulator;
	};
} //Namespace

#endif //_ARGONENTITY_HEADER_
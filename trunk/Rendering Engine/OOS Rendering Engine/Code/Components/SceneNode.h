#ifndef _SCENENODE_HEADER_
#define _SCENENODE_HEADER_

#include "MovableObject.h"
#include "Quaternion.h"
#include "Matrix4.h"
#include "Vector.h"

namespace OOS
{
	class SceneNode : public MovableObject
	{
	public:
		SceneNode(std::string Name, Vector3 Position);
		SceneNode(std::string Name, MovableObject* Visual, Vector3 Position, Vector3 Scale = Vector3( 1, 1, 1 ) );

		void createChildSceneNode(std::string Name);
		void createChildSceneNode(std::string Name, Vector3 Position);

		void addChild(SceneNode* Node);
		unsigned int getNumChildren() const;
		SceneNode* getChild(unsigned int Index) const;

		void attachMovableObject(MovableObject* attachableObject);
		MovableObject* getAttachedVisual() const;

		void setPosition(Vector3 Position);
		Vector3 getPosition() const;

		void setRotation(Quaternion Rotation);
		Vector3 getRotation() const;

	protected:
		std::string m_Name;

		Matrix4 m_WorldMatrix;

		SceneNode* m_Parent;

		Vector<MovableObject*> m_AttachedObjects;
		Vector<SceneNode*> m_Children;
	};
}

#endif //_SCENENODE_HEADER_
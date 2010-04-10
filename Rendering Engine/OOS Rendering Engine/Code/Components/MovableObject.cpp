#include "SceneNode.h"

namespace OOS
{
	MovableObject::~MovableObject()
	{

	}

	void MovableObject::update(float DeltaT)
	{

	}

	void MovableObject::setName(std::string Name)
	{
		m_Name = Name;
	}

	std::string MovableObject::getName() const
	{
		return m_Name;
	}
	
	SceneNode* MovableObject::getParentSceneNode() const
	{
		return m_ParentSceneNode;
	}
	
	void MovableObject::detachFromParent()
	{
		//Detatch the parent node
	}

	bool MovableObject::isAttached() const
	{
		if ( m_ParentSceneNode )
			return true;
		else
			return false;
	}

	void MovableObject::setVisible(bool Visible)
	{
		m_Visible = Visible;
	}

	bool MovableObject::getVisible() const
	{
		return m_Visible;
	}
}
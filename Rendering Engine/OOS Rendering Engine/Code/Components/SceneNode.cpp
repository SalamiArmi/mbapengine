#include "SceneNode.h"

namespace OOS
{
	SceneNode::SceneNode(std::string Name, OOS::Vector3 Position)
	{
		m_Name = Name;
		m_WorldMatrix.setTrans(Position);
	}
}
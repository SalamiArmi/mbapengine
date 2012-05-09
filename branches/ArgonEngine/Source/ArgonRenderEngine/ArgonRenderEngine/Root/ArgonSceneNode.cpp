#include "ArgonSceneNode.h"

namespace Argon
{
	SceneNode::SceneNode(QString Name)
		: m_Name(Name)
	{
	}

	SceneNode::~SceneNode()
	{
	}

	QString SceneNode::GetName()
	{
		return m_Name;
	}

	bool SceneNode::FrameUpdate(float DeltaT)
	{
		return false;
	}

	void SceneNode::SetOrientation(Quaternion &Orientation)
	{
		m_WorldTransform = m_WorldTransform * Orientation.GetRotationMatrix();
		m_InverseWorldTransform = Inverse(m_WorldTransform);
	}

	Quaternion SceneNode::GetOrientation()
	{
		Quaternion Orientation;
		Orientation.SetRotationMatrix(m_WorldTransform);
		return Orientation;
	}

	void SceneNode::SetScale(Vector3 &Scale)
	{
		m_WorldTransform.SetScale(Scale.x, Scale.y, Scale.z);
	}

	Vector3 SceneNode::GetScale()
	{
		return m_WorldTransform.GetScale();
	}

} //Namespace
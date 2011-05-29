#include <Core/ArgonSceneNode.h>

namespace Argon
{
	SceneNode::SceneNode()
	{
	}

	SceneNode::~SceneNode()
	{
	}

	bool SceneNode::FrameDraw()
	{
		return false;
	}

	bool SceneNode::FrameUpdate(float DeltaT)
	{
		return false;
	}

	void SceneNode::SetPosition(Vector3 &Position)
	{
		m_Transformation[12] = Position.x;
		m_Transformation[13] = Position.y;
		m_Transformation[14] = Position.z;
	}

	Vector3 SceneNode::GetPosition()
	{
		return Vector3(m_Transformation.m_Single[12], m_Transformation.m_Single[13], m_Transformation.m_Single[14]);
	}

	void SceneNode::SetOrientation(Vector3 &Orientation)
	{
	}

	Vector3 SceneNode::GetOrientation()
	{
		return Vector3(0.0f, 0.0f, 0.0f);
	}

	void SceneNode::Roll(const float& Radians)
	{
		m_Transformation.RotateZ(Radians);
	}

	void SceneNode::Picth(const float& Radians)
	{
		m_Transformation.RotateX(Radians);
	}

	void SceneNode::Yaw(const float& Radians)
	{
		m_Transformation.RotateY(Radians);
	}

	void SceneNode::SetScale(Vector3 &Scale)
	{
		m_Transformation.m_RowCol[0][0] = Scale.x;
		m_Transformation.m_RowCol[1][1] = Scale.y;
		m_Transformation.m_RowCol[2][2] = Scale.z;
	}

	Vector3 SceneNode::GetScale()
	{
		return Vector3(m_Transformation.m_RowCol[0][0], m_Transformation.m_RowCol[1][1], m_Transformation.m_RowCol[2][2]);
	}

	void SceneNode::Attach(SceneNode* Node)
	{
		Node->m_Parent = this;
		m_Children.Push_Back(Node);
	}

	void SceneNode::Detach(SceneNode* Node)
	{
		m_Children.EraseObject(Node);
	}

	void SceneNode::Detach(size_t Index)
	{
		m_Children.Erase(m_Children.Begin() + Index);
	}

	size_t SceneNode::GetChildCount()
	{
		return m_Children.Size();
	}

	void SceneNode::RemoveAllChildren()
	{
		m_Children.Clear();
	}

	SceneNode* SceneNode::GetParent() const
	{
		return m_Parent;
	}

} //Namespace
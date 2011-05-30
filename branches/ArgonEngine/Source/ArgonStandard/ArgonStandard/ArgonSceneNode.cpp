#include <Core/ArgonSceneNode.h>

namespace Argon
{
	ArgonStandard SceneNode::SceneNode(QString Name)
		: m_Name(Name)
	{
	}

	ArgonStandard SceneNode::~SceneNode()
	{
	}

	ArgonStandard QString SceneNode::GetName()
	{
		return m_Name;
	}

	ArgonStandard bool SceneNode::FrameDraw()
	{
		return false;
	}

	ArgonStandard bool SceneNode::FrameUpdate(float DeltaT)
	{
		return false;
	}

	ArgonStandard void SceneNode::SetPosition(Vector3 &Position)
	{
		m_Transformation[12] = Position.x;
		m_Transformation[13] = Position.y;
		m_Transformation[14] = Position.z;
	}

	ArgonStandard Vector3 SceneNode::GetPosition()
	{
		return Vector3(m_Transformation.m_Single[12], m_Transformation.m_Single[13], m_Transformation.m_Single[14]);
	}

	ArgonStandard void SceneNode::SetOrientation(Vector3 &Orientation)
	{
	}

	ArgonStandard Vector3 SceneNode::GetOrientation()
	{
		return Vector3(0.0f, 0.0f, 0.0f);
	}

	ArgonStandard void SceneNode::Roll(const float& Radians)
	{
		m_Transformation.RotateZ(Radians);
	}

	ArgonStandard void SceneNode::Picth(const float& Radians)
	{
		m_Transformation.RotateX(Radians);
	}

	ArgonStandard void SceneNode::Yaw(const float& Radians)
	{
		m_Transformation.RotateY(Radians);
	}

	ArgonStandard void SceneNode::SetScale(Vector3 &Scale)
	{
		m_Transformation.m_RowCol[0][0] = Scale.x;
		m_Transformation.m_RowCol[1][1] = Scale.y;
		m_Transformation.m_RowCol[2][2] = Scale.z;
	}

	ArgonStandard Vector3 SceneNode::GetScale()
	{
		return Vector3(m_Transformation.m_RowCol[0][0], m_Transformation.m_RowCol[1][1], m_Transformation.m_RowCol[2][2]);
	}

	ArgonStandard void SceneNode::Attach(SceneNode* Node)
	{
		Node->m_Parent = this;
		m_Children.Push_Back(Node);
	}

	ArgonStandard void SceneNode::Detach(SceneNode* Node)
	{
		m_Children.EraseObject(Node);
	}

	ArgonStandard void SceneNode::Detach(size_t Index)
	{
		m_Children.Erase(m_Children.Begin() + Index);
	}

	ArgonStandard size_t SceneNode::GetChildCount()
	{
		return m_Children.Size();
	}

	ArgonStandard void SceneNode::RemoveAllChildren()
	{
		m_Children.Clear();
	}

	ArgonStandard SceneNode* SceneNode::GetParent() const
	{
		return m_Parent;
	}

} //Namespace
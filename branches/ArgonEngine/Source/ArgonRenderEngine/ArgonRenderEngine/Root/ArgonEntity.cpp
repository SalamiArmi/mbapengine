#include "ArgonEntity.h"

namespace Argon
{
	Entity::Entity(String Name, Entity::Type EntityType)
		: m_Name(Name),
		m_Type(EntityType),
		m_Manipulator(NULL),
		m_RenderOrder(0)
	{
	}

	Entity::~Entity()
	{
	}

	String Entity::GetName()
	{
		return m_Name;
	}

	bool Entity::FrameUpdate(float DeltaT)
	{
		return false;
	}

	void Entity::SetOrientation(Quaternion &Orientation)
	{
		m_WorldTransform = m_WorldTransform * Orientation.GetRotationMatrix();
		m_InverseWorldTransform = Inverse(m_WorldTransform);
	}

	Quaternion Entity::GetOrientation()
	{
		Quaternion Orientation;
		Orientation.SetRotationMatrix(m_WorldTransform);
		return Orientation;
	}

	void Entity::SetScale(Vector3 &Scale)
	{
		m_WorldTransform.SetScale(Scale.x, Scale.y, Scale.z);
	}

	Vector3 Entity::GetScale()
	{
		return m_WorldTransform.GetScale();
	}

} //Namespace
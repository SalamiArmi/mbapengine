#include "ArgonEntity.h"

namespace Argon
{
	Entity::Entity(String Name, Entity::Type EntityType)
		: m_Name(Name),
		m_Type(EntityType),
		m_Manipulator(NULL),
		m_RenderOrder(0),
		m_Flags(Entity::FLAG_None)
	{
		m_LocalTranslation.SetScale(1.0f);
	}

	Entity::~Entity()
	{
	}

	String Entity::GetName()
	{
		return m_Name;
	}

	Entity::Type Entity::GetType()
	{
		return m_Type;
	}

	void Entity::FrameUpdate(float DeltaT)
	{
		Entity* Parent = (Entity*)UpdatableTree<Entity>::GetPreviousNode(this);
		if(Parent)
		{
			ArgonAssert(false);
		}

		UpdatableTree<Entity>::FrameUpdate(DeltaT);
	}

	void Entity::SetOrientation(Quaternion &Orientation)
	{
		m_LocalTranslation = m_LocalTranslation * Orientation.GetRotationMatrix();
	}

	Quaternion Entity::GetOrientation()
	{
		Quaternion Orientation;
		Orientation.SetRotationMatrix(m_LocalTranslation);
		return Orientation;
	}

	void Entity::Roll(const float& Radians)
	{
		m_LocalTranslation.Roll(Radians);
	}

	void Entity::Picth(const float& Radians)
	{
		m_LocalTranslation.Pitch(Radians);
	}

	void Entity::Yaw(const float& Radians)
	{
		m_LocalTranslation.Yaw(Radians);
	}

	void Entity::SetScale(Vector3 &Scale)
	{
		m_LocalTranslation.SetScale(Scale.x, Scale.y, Scale.z);
	}

	Vector3 Entity::GetScale()
	{
		return m_LocalTranslation.GetScale();
	}

	Transform4 Entity::GetLocalTranslation()
	{
		return m_LocalTranslation;
	}

	void Entity::SetVisible(bool Visible)
	{
		if(Visible)
		{
			m_Flags = (Entity::NodeFlags)(m_Flags | Entity::FLAG_Visible);
		}
		else
		{
			m_Flags = (Entity::NodeFlags)(m_Flags & ~Entity::FLAG_Visible);
		}
	}

	bool Entity::GetVisible()
	{
		return (Entity::FLAG_Visible == (m_Flags & Entity::FLAG_Visible));
	}

	void Entity::SetCollidable(bool Collidable)
	{
		if(Collidable)
		{
			m_Flags = (Entity::NodeFlags)(m_Flags | Entity::FLAG_Collidable);
		}
		else
		{
			m_Flags = (Entity::NodeFlags)(m_Flags & ~Entity::FLAG_Collidable);
		}
	}

	bool Entity::GetCollidable()
	{
		return (Entity::FLAG_Collidable == (m_Flags & Entity::FLAG_Collidable));
	}

	void Entity::SetManipulator(Manipulator* Manip)
	{
		if(m_Manipulator)
		{
			//delete m_Manipulator;
		}

		m_Manipulator = Manip;
	}

	Manipulator* Entity::GetManipulator()
	{
		return m_Manipulator;
	}

	void Entity::SetRenderOrder(int RenderOrder)
	{
		m_RenderOrder = RenderOrder;
	}

	int Entity::GetRenderOrder()
	{
		return m_RenderOrder;
	}

} //Namespace
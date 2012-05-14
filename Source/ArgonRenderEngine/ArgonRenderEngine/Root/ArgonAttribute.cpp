#include "ArgonAttribute.h"

namespace Argon
{
	Attribute::Attribute(String Name, AttributeType Type)
		: m_Name(Name),
		m_Type(Type)
	{
	}

	Attribute::Attribute(String Name, AttributeType Type, Any Value)
		: m_Name(Name),
		m_Type(Type),
		m_Value(Value)
	{
	}

	Attribute::~Attribute()
	{
	}

	String Attribute::GetName()
	{
		return m_Name;
	}

	bool Attribute::GetAsBoolean()
	{
		return AnyCast<bool>(m_Value);
	}

	int Attribute::GetAsInteger()
	{
		return AnyCast<int>(m_Value);
	}

	float Attribute::GetAsFloat()
	{
		return AnyCast<float>(m_Value);
	}

	Vector2 Attribute::GetAsVector2()
	{
		return AnyCast<Vector2>(m_Value);
	}

	Vector3 Attribute::GetAsVector3()
	{
		return AnyCast<Vector3>(m_Value);
	}

	Vector4 Attribute::GetAsVector4()
	{
		return AnyCast<Vector4>(m_Value);
	}

	Matrix3 Attribute::GetAsMatrix3()
	{
		return AnyCast<Matrix3>(m_Value);
	}

	Matrix4 Attribute::GetAsMatrix4()
	{
		return AnyCast<Matrix4>(m_Value);
	}

	String Attribute::GetAsString()
	{
		return AnyCast<String>(m_Value);
	}

	void Attribute::SetValue(Any& Value)
	{
		m_Value = Value;
	}


	void Attribute::SetValueFromString(String Value)
	{
	}

	uint Attribute::GetType()
	{
		return m_Type;
	}

	void Attribute::AddListner(Attribute::Listner* Add)
	{
		m_Listners.Push_Back(Add);
	}

	void Attribute::RemoveListner(Attribute::Listner* Remove)
	{
	}

	Attribute::Listner::Listner()
	{
	}

	Attribute::Listner::~Listner()
	{
	}

	void Attribute::Listner::ValueChanged(Attribute* Changed)
	{
	}
} //namespace
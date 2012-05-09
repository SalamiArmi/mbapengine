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

inline String Attribute::GetName()
{
	return m_Name;
}

inline bool Attribute::GetAsBoolean()
{
	return AnyCast<bool>(m_Value);
}

inline int Attribute::GetAsInteger()
{
	return AnyCast<int>(m_Value);
}

inline float Attribute::GetAsFloat()
{
	return AnyCast<float>(m_Value);
}

inline Vector2 Attribute::GetAsVector2()
{
	return AnyCast<Vector2>(m_Value);
}

inline Vector3 Attribute::GetAsVector3()
{
	return AnyCast<Vector3>(m_Value);
}

inline Vector4 Attribute::GetAsVector4()
{
	return AnyCast<Vector4>(m_Value);
}

inline Matrix3 Attribute::GetAsMatrix3()
{
	return AnyCast<Matrix3>(m_Value);
}

inline Matrix4 Attribute::GetAsMatrix4()
{
	return AnyCast<Matrix4>(m_Value);
}

inline String Attribute::GetAsString()
{
	return AnyCast<String>(m_Value);
}

inline void Attribute::SetValue(Any& Value)
{
	m_Value = Value;
}


inline void Attribute::SetValueFromString(String Value)
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
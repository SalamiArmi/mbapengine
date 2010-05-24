#include "Precompiled.h"
#include "JumpAbilities.h"

JumpAbilities::JumpAbilities(std::string Name, GameObject* OwnerObject)
{
	m_Name = Name;
		m_OwnerObject = OwnerObject;
}

JumpAbilities::~JumpAbilities()
{

}

void JumpAbilities::Update(Ogre::Real DeltaT)
{

}

void JumpAbilities::Exit()
{

}

std::string JumpAbilities::getType()
{
	return "Jump Abilities";
}

void JumpAbilities::setName(std::string Name)
{
	m_Name = Name;
}

std::string JumpAbilities::getName()
{
	return m_Name;
}
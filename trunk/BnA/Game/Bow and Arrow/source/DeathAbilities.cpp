#include "Precompiled.h"
#include "DeathAbilities.h"


DeathAbilities::DeathAbilities(std::string Name, GameObject* OwnerObject)
{
	m_Name = Name;
		m_OwnerObject = OwnerObject;
}

DeathAbilities::~DeathAbilities()
{
}

void DeathAbilities::Update(Ogre::Real DeltaT)
{

}

void DeathAbilities::Exit()
{

}

std::string DeathAbilities::getType()
{
	return "Jump Abilities";
}

void DeathAbilities::setName(std::string Name)
{
	m_Name = Name;
}

std::string DeathAbilities::getName()
{
	return m_Name;
}
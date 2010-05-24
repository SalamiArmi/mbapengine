#include "Precompiled.h"
#include "ShootAbilities.h"

ShootAbilities::ShootAbilities(std::string Name, GameObject* OwnerObject)
{
	m_Name = Name;
	m_OwnerObject = OwnerObject;
}

ShootAbilities::~ShootAbilities()
{
}

void ShootAbilities::Update(Ogre::Real DeltaT)
{

}

void ShootAbilities::Exit()
{

}

std::string ShootAbilities::getType()
{
	return "Jump Abilities";
}

void ShootAbilities::setName(std::string Name)
{
	m_Name = Name;
}

std::string ShootAbilities::getName()
{
	return m_Name;
}
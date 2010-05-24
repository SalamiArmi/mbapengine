#include "Precompiled.h"
#include "LookAbilities.h"

LookAbilities::LookAbilities(std::string Name, GameObject* OwnerObject)
{
	m_Name = Name;
		m_OwnerObject = OwnerObject;
}

LookAbilities::~LookAbilities()
{

}

void LookAbilities::Update(Ogre::Real DeltaT)
{

}

void LookAbilities::Exit()
{

}

std::string LookAbilities::getType()
{
	return "Jump Abilities";
}

void LookAbilities::setName(std::string Name)
{
	m_Name = Name;
}

std::string LookAbilities::getName()
{
	return m_Name;
}
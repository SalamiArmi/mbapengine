#include "Precompiled.h"
#include "BaseAbilities.h"
#include "JumpAbilities.h"
#include "LookAbilities.h"
#include "MoveAbilities.h"
#include "ShootAbilities.h"
#include "DeathAbilities.h"

AbilityManager::AbilityManager()
{
	//Create the Log for the Abilities
	m_OgreLog = new Ogre::Log("Ability Log", true);
}

AbilityManager::~AbilityManager()
{

}

void AbilityManager::Update(Ogre::Real DeltaT)
{
	for ( unsigned int Index = 0; Index < m_Abilities.size(); ++Index )
	{
		//Update the ability
		m_Abilities.at(Index)->Update(DeltaT);

		if ( m_Abilities.at(Index)->HasSomethingToLog() )
		{
			m_OgreLog->logMessage( m_Abilities.at( Index )->getLogMessage() );
			m_Abilities.at( Index )->setLogMessage( "" );
		}
	}
}

BaseAbilities* AbilityManager::CreateAbility(AbilityType Ability, std::string Name, GameObject* AttachAbilityTo)
{

	BaseAbilities *t_Ability = NULL;

	switch ( Ability )
	{
	case eJumpAbilities:
		t_Ability = new JumpAbilities(Name, AttachAbilityTo);
		break;

	case eLookAbilities:
		t_Ability = new LookAbilities(Name, AttachAbilityTo);
		break;

	case eMoveAbilities:
		t_Ability = new MoveAbilities(Name, AttachAbilityTo);
		break;

	case eShootAbilities:
		t_Ability = new ShootAbilities(Name, AttachAbilityTo);
		break;

	case eDeathAbilities:
		t_Ability = new DeathAbilities(Name, AttachAbilityTo);
		break;
	}

	m_Abilities.push_back(t_Ability);
	return t_Ability;
}

void AbilityManager::DestroyAbility(BaseAbilities* Ability)
{
	for ( unsigned int Index = 0; Index < m_Abilities.size(); ++Index )
	{
		if ( m_Abilities.at(Index) == Ability )
		{
			m_Message = "Destroyed: " + m_Abilities.at(Index)->getType();
			delete m_Abilities.at(Index);
			m_Abilities.erase(m_Abilities.begin() + Index);
		}
	}
}

void AbilityManager::DestroyAbility(std::string &AbilityName)
{
	for ( unsigned int Index = 0; Index < m_Abilities.size(); ++Index )
	{
		if ( m_Abilities.at(Index)->getName() == AbilityName )
		{
			m_Message = "Destroyed: " + m_Abilities.at(Index)->getName();
			delete m_Abilities.at(Index);
			m_Abilities.erase(m_Abilities.begin() + Index);
		}
	}
}


void AbilityManager::DestroyAbility(int Index)
{
	m_Message = "Destroyed: " + m_Abilities.at(Index)->getType();
	delete m_Abilities.at(Index);
	m_Abilities.erase(m_Abilities.begin() + Index);
}

int AbilityManager::getAbilityCount()
{
	return m_Abilities.size();
}
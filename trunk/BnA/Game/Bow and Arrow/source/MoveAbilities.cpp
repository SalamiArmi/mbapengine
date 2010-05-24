#include "Precompiled.h"
#include "MoveAbilities.h"

MoveAbilities::MoveAbilities(std::string Name, GameObject* OwnerObject)
{
	m_Name = Name;
	m_OwnerObject = OwnerObject;
	m_MoveScale = 0.3f;
}

MoveAbilities::~MoveAbilities()
{

}

void MoveAbilities::Update(Ogre::Real DeltaT)
{
	updateInput(DeltaT);
}

void MoveAbilities::Exit()
{
}

void MoveAbilities::updateInput(Ogre::Real DeltaT)
{
	switch ( m_OwnerObject->getInputSystem() )
	{
	case Controller:
		{
			//Xbox input for looking needs tweeking
			if ( !XInputManager::instance()->GetState( 0 ).error )
			{
				Ogre::Vector3 t_FowardDirection = m_OwnerObject->getSceneNode()->_getDerivedOrientation() * Ogre::Vector3::NEGATIVE_UNIT_Z;

				if ( XInputManager::instance()->GetState(0).LeftStick.Y )
				{
					Ogre::Vector3 Force = Ogre::Vector3( XInputManager::instance()->GetState(0).LeftStick.Y * m_MoveScale * t_FowardDirection * 128 );
					m_OwnerObject->getNxActor()->addForce( NxVec3( Force.x, Force.y, Force.z ), NX_ACCELERATION );

#if _DEBUG
					m_Message = Ogre::StringConverter::toString(m_OwnerObject->getNxActor()->getGlobalPosition().x) + " " + Ogre::StringConverter::toString(m_OwnerObject->getNxActor()->getGlobalPosition().y) + " " + Ogre::StringConverter::toString(m_OwnerObject->getNxActor()->getGlobalPosition().z);
					m_NeedsToLog = true;
#endif
 
				}

				if ( XInputManager::instance()->GetState(0).LeftStick.X )
				{
					Ogre::Vector3 Force = Ogre::Vector3( XInputManager::instance()->GetState(0).LeftStick.X * m_MoveScale * t_FowardDirection * 128 );
					m_OwnerObject->getNxActor()->addForce( NxVec3( Force.x, Force.y, Force.z ), NX_ACCELERATION );

#if _DEBUG
					m_Message = Ogre::StringConverter::toString(m_OwnerObject->getNxActor()->getGlobalPosition().x) + " " + Ogre::StringConverter::toString(m_OwnerObject->getNxActor()->getGlobalPosition().y) + " " + Ogre::StringConverter::toString(m_OwnerObject->getNxActor()->getGlobalPosition().z);
					m_NeedsToLog = true;
#endif
 
				}
			}
			else
			{
				m_Message = "An error occured with controller Input";
				m_NeedsToLog = true;
			}
		}
	}
}

std::string MoveAbilities::getType()
{
	return "Jump Abilities";
}

void MoveAbilities::setName(std::string Name)
{
	m_Name = Name;
}

std::string MoveAbilities::getName()
{
	return m_Name;
}
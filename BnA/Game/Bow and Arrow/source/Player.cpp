#include "Precompiled.h"
#include "Player.h"
#include "SceneManager.h"
#include "PCInputManager.h"
#include "MoveAbilities.h"

Player::Player(std::string PlayerName, Ogre::Vector3 spawnPosition, InputSystem inputSystem, Ogre::SceneManager* SceneManager)
{
	//Set the Matrix
	mWorldMatrix.setTrans(spawnPosition);

	//Create the player - Scenenode and Entity
	mEntity = SceneManager->createEntity("Player Character", "__unnamed.mesh");
	mSceneNode = SceneManager->getRootSceneNode()->createChildSceneNode( "Player Character" );
	mSceneNode->attachObject( mEntity );
	mSceneNode->setPosition( mWorldMatrix.getTrans() );

	//Create Physcis
	NxCapsuleShapeDesc CapsuleDesc;
	CapsuleDesc.height = 2.5;
	CapsuleDesc.radius = 0.8;
	CapsuleDesc.mass = 2;
	CapsuleDesc.density = 1;

	m_NxActor = PhysicsManager::instance()->addActor(CapsuleDesc);
	m_NxActor->setGlobalPosition( NxVec3( mWorldMatrix.getTrans().x, mWorldMatrix.getTrans().y, mWorldMatrix.getTrans().z ) );

	//Create the player Camera
	m_Camera = SceneManager::getSingleton().getSceneManager()->createCamera("Player Camera");
	m_Camera->setPosition(mWorldMatrix.getTrans());
	m_Camera->lookAt(0,-1,0);
	m_Camera->setFarClipDistance(1000);
	m_Camera->setNearClipDistance(0.1);
	Ogre::Viewport* viewport = SceneManager::getSingleton().getRenderWindow()->addViewport(m_Camera);
	viewport->setBackgroundColour(Ogre::ColourValue(0.6, 0.7, 0.8));
	viewport->setCamera(m_Camera);

	m_InputSystem = inputSystem;

	//Create Needed abilities
	m_MoveAbilities = static_cast<MoveAbilities*>(m_AbilityManager->CreateAbility(eMoveAbilities, "Player Move Ability", this));
}

Player::~Player()
{

}

void Player::update(Ogre::Real deltaT)
{

	m_AbilityManager->Update(deltaT);

	mWorldMatrix.setTrans( Ogre::Vector3( m_NxActor->getGlobalPosition().x, m_NxActor->getGlobalPosition().y, m_NxActor->getGlobalPosition().z ) );

	m_Camera->pitch(Ogre::Radian(PCInputManager::instance()->getInputData()->getMouseDelta().y * deltaT * -1.0f));
	m_Camera->yaw(Ogre::Radian(PCInputManager::instance()->getInputData()->getMouseDelta().x * deltaT * -1.0f));
	m_Camera->moveRelative(Ogre::Vector3(
		PCInputManager::instance()->getInputData()->isKeyDown(OIS::KC_D) - PCInputManager::instance()->getInputData()->isKeyDown(OIS::KC_A),
		0,
		PCInputManager::instance()->getInputData()->isKeyDown(OIS::KC_S) - PCInputManager::instance()->getInputData()->isKeyDown(OIS::KC_W)) * deltaT);

	m_Camera->setPosition( mWorldMatrix.getTrans() );

	XInputManager::instance()->Update();

}

void Player::exit()
{

}
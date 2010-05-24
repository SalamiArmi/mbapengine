#include "Precompiled.h"
#include "GameObject.h"
#include "SceneManager.h"

GameObject::GameObject()
:
mSceneNode(0),
mWorldMatrix(Ogre::Matrix4::IDENTITY)
{
	SceneManager::getSingleton().addGameObject(this);
	m_AbilityManager = new AbilityManager();
}

GameObject::~GameObject()
{
	
}

void GameObject::update(Ogre::Real DeltaT)
{
}

void GameObject::cleanUp()
{
	mDeleteMe = true;
}

void GameObject::setPosition(const Ogre::Vector3 &newPosition)
{
	mWorldMatrix.setTrans(newPosition);
	mSceneNode->setPosition(newPosition);
}

const Ogre::Vector3 GameObject::getPosition() const
{
	return mWorldMatrix.getTrans();
}

const Ogre::Matrix4 &GameObject::getWorldMatrix() const
{
	return mWorldMatrix;
}

Ogre::SceneNode* GameObject::getSceneNode()
{
	return mSceneNode;
}

Ogre::Entity* GameObject::getEntity()
{
	return mEntity;
}

bool &GameObject::PleaseDeleteMe()
{
	return mDeleteMe;
}

InputSystem& GameObject::getInputSystem()
{
	return m_InputSystem;
}

NxActor* GameObject::getNxActor()
{
	return m_NxActor;
}
#ifndef _GAMEOBJECT_HEADER_
#define _GAMEOBJECT_HEADER_

#include "BaseAbilities.h"
#include "AbilityManager.h"

enum InputSystem
{
	Controller = 0,
	MouseAndKeyboard,
	None
};

class GameObject
{
public:
	~GameObject();

	virtual void					update(Ogre::Real DeltaT);

	virtual void					cleanUp();

	const Ogre::Vector3		getPosition() const;
	void					setPosition(const Ogre::Vector3 &newPosition);

	const Ogre::Matrix4&	getWorldMatrix() const;

	Ogre::SceneNode*		getSceneNode();
	Ogre::Entity*			getEntity();

	InputSystem&			getInputSystem();

	bool&					PleaseDeleteMe();

	NxActor*				getNxActor();

protected:

	GameObject();

	Ogre::Real				m_TimeAlive;

	Ogre::SceneNode*		mSceneNode;
	Ogre::Entity*			mEntity;

	Ogre::String			mName;
	Ogre::String			mMeshName;
	Ogre::Quaternion		mRotation;

	Ogre::Real				mScale;
	Ogre::Real				mTimeAlive;
	Ogre::Matrix4			mWorldMatrix;

	bool 					mDeleteMe;

	NxActor*				m_NxActor;

	//Ability manager for this object
	AbilityManager* m_AbilityManager;

	//The input System for this Object
	InputSystem m_InputSystem;
};

#endif //_GAMEOBJECT_HEADER_
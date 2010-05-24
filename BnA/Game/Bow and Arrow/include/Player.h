#ifndef _HUMAN_HEADER_
#define _HUMAN_HEADER_

#include "GameObject.h"
#include "PhysicsManager.h"
#include "MoveAbilities.h"

class Player : public GameObject
{
public:
	Player(std::string PlayerName, Ogre::Vector3 spawnPosition, InputSystem inputSystem, Ogre::SceneManager* SceneManager);
	~Player();

	void			update(Ogre::Real deltaT);
	void			exit();

private:

	Ogre::Camera*	m_Camera;

	///MoveAbility
	MoveAbilities* m_MoveAbilities;

};

#endif //_HUMAN_HEADER_
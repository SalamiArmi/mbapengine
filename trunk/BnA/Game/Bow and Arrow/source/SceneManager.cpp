#include "Precompiled.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "LevelLoader.h"
#include "PCInputManager.h"
#include "PhysicsManager.h"
#include "Player.h"

template<> SceneManager* Ogre::Singleton<SceneManager>::ms_Singleton = 0;

SceneManager::SceneManager(Ogre::Root* root, Ogre::RenderWindow* renderwin)
{
	m_Root = root;
	m_RenderWindow = renderwin;
}

SceneManager::~SceneManager()
{

}

void SceneManager::init()
{
	m_SceneManager = m_Root->createSceneManager(Ogre::ST_GENERIC, "Bow and Arrow");

	NxPlaneShapeDesc groundPlaneDesc;
	PhysicsManager::instance()->getPlaneDesc(Ogre::Vector3(0,1,0),0,&groundPlaneDesc);
	NxActor* T = PhysicsManager::instance()->addActor(groundPlaneDesc);
	T->setGlobalPosition(NxVec3(0,0,0));

	//Create the level
	m_Level = new Level();
	m_Level->createLevel();
	m_Level->parseLevelFile("BloodGulch.scene","General", m_SceneManager);

	if ( PhysicsManager::instance()->loadPhysxCollection("../../Media/Level/LevelPhysicsScene.xml") )
	{
		m_Player = new Player("Test Player", Ogre::Vector3(0,0,-20), Controller, m_SceneManager);
	}

}

void SceneManager::update(Ogre::Real deltaT)
{
	PhysicsManager::instance()->update(deltaT);

	XInputManager::instance()->Update();

	for (std::vector<GameObject*>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); ++it)
	{
		(*it)->update(deltaT);
	}

	PCInputManager::instance()->update();

	PhysicsManager::instance()->endUpdate();
}

void SceneManager::xboxInput(Ogre::Real deltaT)
{

}

void SceneManager::exit()
{
	for (std::vector<GameObject*>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); ++it)
	{
		(*it)->cleanUp();
		delete (*it);
		(*it) = 0;
	}
	m_GameObjects.clear();
}

void SceneManager::addGameObject(GameObject* objectBeingAdded)
{
	m_GameObjects.push_back(objectBeingAdded);	
}

Ogre::SceneManager* SceneManager::getSceneManager()
{
	return m_SceneManager;
}

Ogre::RenderWindow* SceneManager::getRenderWindow()
{
	return m_RenderWindow;
}

SceneManager& SceneManager::getSingleton()
{
	assert( ms_Singleton );  return ( *ms_Singleton );  
}


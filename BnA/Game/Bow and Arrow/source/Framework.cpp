#include "Precompiled.h"
#include "Framework.h"
#include "SceneManager.h"

Framework::Framework() 
:	running(true), 
	mPause(false), 
	lastTime(timer.getMilliseconds()), 
	mRenderWnd(mRenderWnd)
{
	// Initialising Ogre Root 
	m_Root = new Ogre::Root();

	// Displays Ogre Config window
	running = m_Root->showConfigDialog();

	// Fails to Start Close
	if(!running) exit(0);

	// Initialising Render Window
	mRenderWnd = m_Root->initialise(true, "Bow and Arrow");
	Ogre::WindowEventUtilities::addWindowEventListener(mRenderWnd, this);

	// Loading Resources for the game
	loadResources();

	m_SceneManager = new SceneManager(m_Root, mRenderWnd);
	m_SceneManager->init();
}

Framework::~Framework()
{
	//Clean up LOL
	if(!mRenderWnd)
	{
		return;
	}

	if(m_SceneManager)
	{
		m_SceneManager->exit();
		delete m_SceneManager;
	}
	m_Root->shutdown();
}

void Framework::Update()
{
	// Gets Delta Time
	Ogre::Real deltaT = (timer.getMilliseconds() - lastTime) / 1000.0f;
	// Gets Time since last frame
	lastTime = timer.getMilliseconds();

	while (PeekMessage(&m_msg, 0, 0U, 0U, PM_REMOVE))
	{
		TranslateMessage(&m_msg);
		DispatchMessage(&m_msg);
	}

	m_SceneManager->update(deltaT);

	m_Root->renderOneFrame();
}

void Framework::Shutdown()
{
	running = false;
}

bool Framework::isRunning()
{
	return running;
}


// Loads Ogre Resources YAY!
void Framework::loadResources()
{
	Ogre::ConfigFile cf;
	cf.load("resources.cfg");
	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

	Ogre::String secName, typeName, archName;
	while(seci.hasMoreElements())
	{
		secName = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;
		for(i = settings->begin(); i != settings->end(); ++i)
		{
			typeName = i->first;
			archName = i->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
		}
	}
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void Framework::windowMoved(Ogre::RenderWindow* rw)
{
}

void Framework::windowResized(Ogre::RenderWindow* rw)
{

}

void Framework::windowClosed(Ogre::RenderWindow* rw)
{
	Shutdown();
}

void Framework::windowFocusChange(Ogre::RenderWindow* rw)
{
}

Ogre::RenderWindow* Framework::getRenderWindow() const
{
	return mRenderWnd;
}

Ogre::Timer Framework::getTimer()
{
	return timer;
}
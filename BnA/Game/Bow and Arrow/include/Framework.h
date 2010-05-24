#ifndef _FRAMEWORK_H_
#define _FRAMEWORK_H_

#include <OgrePrerequisites.h>
#include <OgreWindowEventUtilities.h>
#include <OgreTimer.h>

class SceneManager;

class Framework : public Ogre::WindowEventListener, public singleton<Framework>
{
	friend singleton;
public:
	// Constructor
	Framework();
	// DeConstructor 
	~Framework();

	// handles pending states and updates
	void						Update();

	// Shutdown framework
	void						Shutdown();

	// Current Ogre State
	bool						isRunning();

	Ogre::Timer					getTimer();

	// Resizing Window Functions
	void						windowMoved(Ogre::RenderWindow* rw);
	void						windowResized(Ogre::RenderWindow* rw);
	void						windowClosed(Ogre::RenderWindow* rw);
	void						windowFocusChange(Ogre::RenderWindow* rw);
	Ogre::RenderWindow*			getRenderWindow() const;

private:
	Ogre::Root*					m_Root;					// Ogre Root Node
	Ogre::RenderWindow*			mRenderWnd;				// Ogre RenderWindow

	SceneManager*	m_SceneManager;		// Current Active State

	Ogre::Timer					timer;					// Game Timer(to work out deltaTime)
	unsigned long				lastTime;				// Last Time passed since last frame rendered
	bool						running;				// Is Framework running?
	bool						mPause;


	void						loadResources();		// Load Game Resources

	MSG m_msg;
};

#endif //_FRAMEWORK_H_

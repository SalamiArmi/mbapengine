#include "precompiled.h"

#include "PCInputManager.h"

#include "Framework.h"

float PCInputManager::mouseZ = 0.0f;

PCInputManager::PCInputListener::PCInputListener()
{
}

bool PCInputManager::PCInputListener::keyPressed(const OIS::KeyEvent &arg)
{
	PCInputManager::instance()->m_inputData->m_previousHits[arg.key] = true;
	return true;
}

bool PCInputManager::PCInputListener::keyReleased(const OIS::KeyEvent &arg)
{
	PCInputManager::instance()->m_inputData->m_previousHits[arg.key] = true;
	return true;
}

bool PCInputManager::PCInputListener::mouseMoved(const OIS::MouseEvent &arg)
{
	PCInputManager::instance()->m_inputData->m_mouseDelta = Ogre::Vector3(arg.state.X.rel, arg.state.Y.rel, arg.state.Z.rel);
	return true;
}

bool PCInputManager::PCInputListener::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	PCInputManager::instance()->m_inputData->m_previousClicks[id] = true;
	return true;
}

bool PCInputManager::PCInputListener::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	PCInputManager::instance()->m_inputData->m_previousClicks[id] = true;
	return true;
}

PCInputManager::PCInputManager()
:
m_inputManager(0),
m_inputMouse(0),
m_inputKeyboard(0)
{
	load();
}

PCInputManager::~PCInputManager()
{
	unload();
}

void PCInputManager::load()
{
	// Create input system
	OIS::ParamList paramList;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;
	Framework::instance()->getRenderWindow()->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	paramList.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
	paramList.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND" )));
	paramList.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
	paramList.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
	paramList.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));
	m_inputManager = OIS::InputManager::createInputSystem(paramList);

	// Create mouse an keyboard input objects
	m_inputMouse = static_cast<OIS::Mouse*>(m_inputManager->createInputObject(OIS::OISMouse, true));
	m_inputKeyboard = static_cast<OIS::Keyboard*>(m_inputManager->createInputObject(OIS::OISKeyboard, true));

	// Clamp the mouse to the window
	unsigned int width, height, depth;
	int top, left;
	Framework::instance()->getRenderWindow()->getMetrics(width, height, depth, left, top);
	const OIS::MouseState &ms = m_inputMouse->getMouseState();
	ms.width = width;
	ms.height = height;

	m_inputKeyboard->setEventCallback(&m_listener);
	m_inputMouse->setEventCallback(&m_listener);

	m_inputData = new PCInputState;
}

void PCInputManager::unload()
{
	if(m_inputManager)
	{
		if(m_inputMouse)
		{
			m_inputManager->destroyInputObject(m_inputMouse);
			m_inputMouse = 0;
		}

		if(m_inputKeyboard) 
		{
			m_inputKeyboard->getEventCallback();
			m_inputManager->destroyInputObject(m_inputKeyboard);
			m_inputKeyboard = 0;
		}

		m_inputManager->destroyInputSystem(m_inputManager);
		m_inputManager = 0;
	}
}

void PCInputManager::update()
{
	for (std::map<const OIS::KeyCode, bool>::iterator it = m_inputData->m_previousHits.begin(); it != m_inputData->m_previousHits.end(); ++it)
	{
		(*it).second = false;
	}

	for (std::map<const OIS::MouseButtonID, bool>::iterator it = m_inputData->m_previousClicks.begin(); it != m_inputData->m_previousClicks.end(); ++it)
	{
		(*it).second = false;
	}

	PCInputManager::instance()->m_inputData->m_mouseDelta = Ogre::Vector3::ZERO;

	m_inputMouse->capture();
	m_inputKeyboard->capture();
}

const PCInputManager::PCInputState *PCInputManager::getInputData() const
{
	return m_inputData;
}

const OIS::Mouse *PCInputManager::getMouseInputDevice() const
{
	return m_inputMouse;
}

const OIS::MouseState &PCInputManager::getMouseState() const
{
	return m_inputMouse->getMouseState();
}

const OIS::Keyboard *PCInputManager::getKeyboardInputDevice() const
{
	return m_inputKeyboard;
}

PCInputManager::PCInputState::PCInputState()
{
}

PCInputManager::PCInputState::~PCInputState()
{
	m_previousHits.clear();
	m_previousClicks.clear();
}

const bool PCInputManager::PCInputState::isKeyDown(const OIS::KeyCode key) const
{
	return PCInputManager::instance()->m_inputKeyboard->isKeyDown(key);
}

const bool PCInputManager::PCInputState::isKeyPressed(const OIS::KeyCode key) const
{
	std::map<const OIS::KeyCode, bool>::const_iterator searchResult = m_previousHits.find(key);
	if (searchResult != m_previousHits.end())
	{
		return (*searchResult).second && PCInputManager::instance()->m_inputKeyboard->isKeyDown(key);
	}
	return false;
}

const bool PCInputManager::PCInputState::isKeyPressed(const OIS::MouseButtonID button) const
{
	std::map<const OIS::MouseButtonID, bool>::const_iterator searchResult = m_previousClicks.find(button);
	if (searchResult != m_previousClicks.end())
	{
		return (*searchResult).second && PCInputManager::instance()->m_inputMouse->getMouseState().buttonDown(button);
	}
	return false;
}

const bool PCInputManager::PCInputState::isKeyReleased(const OIS::KeyCode key) const
{
	std::map<const OIS::KeyCode, bool>::const_iterator searchResult = m_previousHits.find(key);
	if (searchResult != m_previousHits.end())
	{
		return (*searchResult).second && !PCInputManager::instance()->m_inputKeyboard->isKeyDown(key);
	}
	return false;
}

const bool PCInputManager::PCInputState::isKeyReleased(const OIS::MouseButtonID button) const
{
	std::map<const OIS::MouseButtonID, bool>::const_iterator searchResult = m_previousClicks.find(button);
	if (searchResult != m_previousClicks.end())
	{
		return (*searchResult).second && !PCInputManager::instance()->m_inputMouse->getMouseState().buttonDown(button);
	}
	return false;
}

const bool PCInputManager::PCInputState::isModifierDown(const OIS::Keyboard::Modifier key) const
{
	return PCInputManager::instance()->m_inputKeyboard->isModifierDown(key);
}

const Ogre::Vector3 &PCInputManager::PCInputState::getMouseDelta() const
{
	return m_mouseDelta;
}
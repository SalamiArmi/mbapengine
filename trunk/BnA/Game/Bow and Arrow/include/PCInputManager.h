#pragma once

class PCInputManager : public singleton<PCInputManager>
{
	friend singleton;
public:
	~PCInputManager();

	class PCInputState
	{
		friend PCInputManager;
	public:
		PCInputState();
		~PCInputState();

		const bool isKeyDown(const OIS::KeyCode) const;

		const bool isKeyPressed(const OIS::KeyCode) const;
		const bool isKeyPressed(const OIS::MouseButtonID) const;

		const bool isKeyReleased(const OIS::KeyCode) const;
		const bool isKeyReleased(const OIS::MouseButtonID button) const;

		const bool isModifierDown(const OIS::Keyboard::Modifier) const;

		const Ogre::Vector3 &getMouseDelta() const;

	protected:
		std::map<const OIS::KeyCode, bool> m_previousHits;
		std::map<const OIS::MouseButtonID, bool> m_previousClicks;
		Ogre::Vector3 m_mouseDelta;
	};

	void load();
	void unload();

	void update();

	const PCInputState *getInputData() const;

	static float mouseZ;

protected:
	PCInputManager();

	const OIS::Mouse *getMouseInputDevice() const;
	const OIS::MouseState &getMouseState() const;
	const OIS::Keyboard *getKeyboardInputDevice() const;

	// Callback for mouse and keyboard
	class PCInputListener : public OIS::KeyListener, public OIS::MouseListener
	{
		friend PCInputManager;
	public:
		PCInputListener();

		bool keyPressed(const OIS::KeyEvent &arg);
		bool keyReleased(const OIS::KeyEvent &arg);

		bool mouseMoved(const OIS::MouseEvent &arg);
		bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
		bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

	private:
	} m_listener;

	OIS::InputManager *m_inputManager;
	OIS::Mouse *m_inputMouse;
	OIS::Keyboard *m_inputKeyboard;

	PCInputState *m_inputData;
};

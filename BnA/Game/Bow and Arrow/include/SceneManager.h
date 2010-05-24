#ifndef _SCENEMANAGER_HEADER_
#define _SCENEMANAGER_HEADER_

class GameObject;
class Level;
class Player;

class SceneManager : Ogre::Singleton<SceneManager>
	{
	public:
		SceneManager(Ogre::Root* root, Ogre::RenderWindow* renderwin);
		~SceneManager();

		///init(VOID)
		///
		///Main init of the application
		///
		///No Params
		void init();

		bool loadPhyscisScene(char* fileName);

		///update(VOID)
		///
		///Main update of the application
		///
		///deltaT: Delta time
		void update(Ogre::Real deltaT);

		///exit(VOID)
		///
		///main exit before destrucotr is called
		///
		///No Params
		void exit();

		///xboxInput(VOID)
		///
		///All unbuffered input for the xbox controller
		///goes within this function
		///
		///deltaT: Delta time
		void xboxInput(Ogre::Real deltaT);

		///AddGameObject
		///
		///Add a gameObject to be Rendered and updated
		///
		///Param GameObject: The gameobject to be added to the updateable Vector
		void addGameObject(GameObject* objectBeingAdded);

		Ogre::SceneManager* getSceneManager();

		Ogre::RenderWindow* getRenderWindow();

		static SceneManager& getSingleton();

	protected:
		std::vector<GameObject*>	m_GameObjects;

		Ogre::SceneManager*			m_SceneManager;
		Ogre::Root*					m_Root;
		Ogre::RenderWindow*			m_RenderWindow;

		Level*						m_Level;

		Player*						m_Player;
	};
#endif //_SceneManager_HEADER_

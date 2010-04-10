#define _SCENEMANAGER_HEADER_
#ifdef _SCENEMANAGER_HEADER_

#include <string>
#include "Manager.h"
#include "Vector2.h"
#include "SceneNode.h"

namespace OOS
{
	class Viewport;
	class Window;
	class Camera;
	class SceneNode;

	class SceneManager : public Manager
	{
	public:
		SceneManager(std::string Name);
		~SceneManager();

		//Create a viewport
		Viewport* createViewport(Camera* Camera, int Width, int Height, Vector2 Position);
		Window* createWindow( int Width, int Height );

		void CreateChildSceneNode(std::string Name);
		SceneNode* getRootSceneNode() const;

	private:

		SceneNode* m_RootSceneNode;

		bool update();

		Vector<Viewport*> m_Viewports;
		Vector<Window*> m_Windows;
	};

}

#endif //_SCENEMANAGER_HEADER_
#include "SceneManager.h"
#include "Viewport.h"
#include "Window.h"
#include "RenderingSystem.h"
#include "SceneNode.h"
#include "Vector3.h"

namespace OOS
{
	SceneManager::SceneManager( std::string Name )
	{
		m_Name = Name;
		m_RootSceneNode = new SceneNode( "Root", Vector3( 0, 0 ,0) );
	}

	SceneManager::~SceneManager()
	{
		Manager::~Manager();
	}

	bool SceneManager::update()
	{
		m_Viewports.at(0)->update();
		return true;
	}

	Viewport* SceneManager::createViewport(Camera* Camera, int Width, int Height, Vector2 Position )
	{
		Viewport* tempViewport = new Viewport( Camera, Width, Height, Position );
		m_Viewports.push_Back( tempViewport );
		System::getSingleton().getRenderingSystem()->getDx10Device()->RSSetViewports( m_Viewports.Count(), tempViewport->getDirectxObjectRef() );
		return tempViewport;
	}

	Window* SceneManager::createWindow( int Width, int Height )
	{
		Window* tempWindow = new Window( System::getSingleton().getInstance(), Width, Height );
		m_Windows.push_Back( tempWindow );
		return tempWindow;
	}

}
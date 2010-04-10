#include "System.h"
#include "RenderingSystem.h"
#include "SceneManager.h"
#include "Camera.h"
#include "Parser.h"

namespace OOS
{
	template<> System* Singleton<System>::mSingleton = 0;

	System::System(HINSTANCE Instance) : m_Instance(Instance), m_Running(true)
	{
		//Registor the managers
		SceneManager* sceneManager = new SceneManager( "SceneManager" );

		m_Window = sceneManager->createWindow ( 1280, 720 );
		m_RenderingSystem = new RenderingSystem(m_Window);
	}

	System::~System()
	{
		delete m_Window;
		m_Running = false;
		m_Instance = NULL;
	}

	bool System::InitInstance()
	{
		m_Running = m_Window->Initiliase();
		m_Running = m_RenderingSystem->InitInstance();

		static_cast < SceneManager* > ( m_Managers.at(0) )->createViewport( NULL, 100,100, Vector2(0,0));

		return m_Running;
	}

	int System::RenderOneFrame()
	{
		MSG Message;
		HACCEL AccelTable = LoadAccelerators ( m_Instance, "" );

		if ( GetMessage ( &Message, NULL, 0, 0 ) )
		{
			if ( !TranslateAccelerator ( Message.hwnd, AccelTable, &Message ) )
			{
				TranslateMessage( &Message );
				DispatchMessage( &Message );
				m_Window->Update(0.0025);
								m_Managers.at(0)->update();
				m_RenderingSystem->RenderOneFrame( );
			}
		}
		
		return ( int ) Message.wParam;
	}

	void System::Cleanup()
	{
		m_RenderingSystem->Cleanup();
		delete m_RenderingSystem;
		m_RenderingSystem = NULL;
	}

	void System::Exit()
	{
		m_Running = false;
	}

	void System::registorManager( Manager *Manager )
	{
		m_Managers.push_Back( Manager );
	}

	void System::registorParser( Parser *Parser )
	{
		m_Parsers.push_Back( Parser );
	}

	System& System::getSingleton()
	{
		return *mSingleton;
	}
}
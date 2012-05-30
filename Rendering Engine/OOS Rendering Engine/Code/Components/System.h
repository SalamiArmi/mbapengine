#ifndef _SYSTEM_HEADER_
#define _SYSTEM_HEADER_

#include "Window.h"
#include "Vector.h"
#include "Singleton.h"
#include "Config.h"
#include <string>

namespace OOS
{

	class RenderingSystem;
	class Manager;
	class SceneManager;
	class Parser;

	class System : public Singleton<System>
	{
	public:

		System(HINSTANCE Instance);
		~System();

		virtual bool	InitInstance();
		virtual int		RenderOneFrame();
		virtual void	Cleanup();
		void			Exit();

		bool&	IsRunning() { return m_Running; }

		void registorManager(Manager* Manager);
		void registorParser(Parser* Parser);

		unsigned int getNumManagers();
		Manager* getManager( unsigned int Index );
		Manager* getManager( std::string Name );
		
		RenderingSystem* getRenderingSystem() { return m_RenderingSystem; }

		HINSTANCE getInstance() { return m_Instance; }

		static System&	getSingleton();

	private:

		//Is the Rendering System Running
		bool m_Running;

		//Window
		OOS::Window* m_Window;	

		//Instance
		HINSTANCE m_Instance;

		//Handle the Rendering System
		RenderingSystem* m_RenderingSystem;

		//The applications managers
		Vector<Manager*> m_Managers;

		//The application Parsers
		Vector<Parser*> m_Parsers;

	};

}

#endif //_SYSTEM_HEADER_
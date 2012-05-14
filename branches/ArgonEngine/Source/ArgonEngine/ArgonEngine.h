#ifndef _ARGONENGINE_HEADER_
#define _ARGONENGINE_HEADER_

#include <Standard/ArgonStandard.h>
#include <Standard/ArgonSingleton.h>
#include <Standard/ArgonVector.h>
#include <Standard/ArgonTimer.h>

#include <Core\ArgonRoot.h>
#include <Interface\IPlatform.h>
#include <Interface\IWindow.h>

#define _CreateWindow_

namespace Argon
{
	class ArgonEngine : public singleton<ArgonEngine>
	{
		friend singleton;
	public:
		ArgonEngine();
		~ArgonEngine();

		///LOAD(BOOL)
		///
		///Load and init the engine
		///
		///No Params:
		bool				Load();

		///UNLOAD(VOID)
		///
		///Release and Cleanup the Engine
		///
		///No Params:
		bool				Unload();

		///(VOID)
		///
		/// Create a new device with the desired driver and render system
		///
		///No Params:
		bool				Create(void* Window, size_t RenderSystem, size_t DriverIndex, size_t ModeIndex);

		///FRAMEUPDATE(BOOL)
		///
		/// Frame update for the Engine and all its components
		///
		///No Params:
		bool				FrameUpdate();

		///GETROOT(ROOT)
		///
		///Get the root if the engine it contains all the engine components and render systems
		///
		///No Params:
		Root*				GetRoot() const;

		///GETPLATFORM(IPLATFORM)
		///
		/// Get the Main platform that is being used
		///
		///No Params:
		IPlatform*			GetPlatform() const;

	protected:
		IPlatform*				m_Platform;				//The platform that will be used throughout the life of the application
		Root*					m_Root;					//The Root is used to hide all Render Systems
		SceneManager*			m_SceneManager;
		IWindow*				m_Window;

		Timer*					m_Timer;				//Main frame update timer
		float					m_TimeElapsed;			//The time that has elapsed since the start of the scene
	};
} //Namespace

#endif //_ARGONENGINE_HEADER_
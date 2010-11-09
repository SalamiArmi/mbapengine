#ifndef _ARGONENGINE_HEADER_
#define _ARGONENGINE_HEADER_

#include <Standard/ArgonStandard.h>
#include <Standard/ArgonVector.h>
#include <Interface/IRenderSystem.h>
#include <Interface/IPlatform.h>
#include <Interface/IComponent.h>
#include <Standard/ArgonSingleton.h>

namespace Argon
{
	class Log;

	class ArgonEngine : public singleton<ArgonEngine>
	{
		friend singleton;
	public:
		ArgonEngine();

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

		///GETRENDERSYSTEMCOUNT(SIZE_T)
		///
		///Get all the Found and loaded rendersystems once the render system is chosen all others are unloaded
		///
		///
		///No Params:
		size_t				GetRenderSystemCount();

		///GETRENDERSYSTEM(IRENDERSYSTEM)
		///
		///Get a RenderSystem
		///
		///Param Index: Which render system to get
		IRenderSystem*		GetRenderSystem(size_t Index) const;

	protected:

		///ARGONENGINE(VOID)
		///
		///Protected because the engine can not be deleted using the delete keyword
		///
		///No Params:
		virtual				~ArgonEngine();

		///IMPORTCOMPONENTS(VOID)
		///
		///Import all external Components
		///
		///No Params:
		void				ImportComponents();

		///IMPORTRENDERSYSTEM(VOID)
		///
		///Import all supported components that are currently of type IRenderSystem.
		///
		///
		///No Params:
		void				ImportRenderSystems();

		///FINDSUPPORTEDCOMPONENTS(VOID)
		///
		///Find all components and load them into a list
		///
		///No Params:
		void				FindSupportedComponents();

	private:
		Vector<IComponent*>		m_Components;
		Vector<IRenderSystem*>	m_LoadedRenderSystems;
		Vector<String>			m_FoundComponents;
		IPlatform*				m_Platform;
		Log*					m_EngineLog;
	};

	///(VOID)
	///
	///Preload the Engine by creating a new engine and also loading all rendering systems but not
	///Storing or creating until statics are chosen
	///
	///No Params:
	ArgonExport void PreLoadEngine()
	{
		ArgonEngine::instance()->Load(); //Preload all the Components
	}

	ArgonExport int GetRenderSystemCount()
	{
		return ArgonEngine::instance()->GetRenderSystemCount();
	}

	ArgonExport char* GetRenderSystemNameA(int RenderSystemIndex)
	{
		IRenderSystem* RenderSystem = ArgonEngine::instance()->GetRenderSystem(RenderSystemIndex);
		IComponent* Component = NULL;
		if(RenderSystem->QueryInterface(GUID_IComponent, (void**)&Component))
		{
			return Component->GetName().c_str();
		}
		return "";
	}

	ArgonExport int GetRenderSystemDriversCount(int RenderSystemIndex)
	{
		IRenderSystem* RenderSystem = ArgonEngine::instance()->GetRenderSystem(RenderSystemIndex);
		if(RenderSystem)
			return RenderSystem->GetDriverCount();
		return 0; //No Render System was Found
	}

	ArgonExport int GetRenderSystemDriverModesCount(int RenderSystemIndex, int DriverIndex)
	{
		IRenderSystem* RenderSystem = ArgonEngine::instance()->GetRenderSystem(RenderSystemIndex);
		if(RenderSystem)
		{
			IDriver* Driver = RenderSystem->GetDriver(DriverIndex);
			if(Driver)
			{
				return Driver->GetVideoModeCount();
			}
		}
		return 0;
	}

	ArgonExport char* GetRenderSystemDriverModeDescA(int RenderSystemIndex, int DriverIndex, int VideoIndex)
	{
		IRenderSystem* RenderSystem = ArgonEngine::instance()->GetRenderSystem(RenderSystemIndex);
		if(RenderSystem)
		{
			IDriver* Driver = RenderSystem->GetDriver(DriverIndex);
			if(Driver)
			{
				IVideoMode* VideoMode = Driver->GetVideoMode(VideoIndex);
				return VideoMode->GetDescription().c_str();
			}
		}
		return "";
	}

	ArgonExport void CreateEngine(int RenderSystemIndex, int DriverIndex, int VideoModeIndex, int* Window)
	{
		IRenderSystem* RenderSystem = ArgonEngine::instance()->GetRenderSystem(0);

		if(RenderSystem)
		{
			RenderSystem->CreateDevice(DriverIndex, VideoModeIndex, Window);
		}
	}

	ArgonExport void DestroyEngine()
	{

	}


} //Namespace

#endif //_ARGONENGINE_HEADER_
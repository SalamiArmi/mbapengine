//namespace Argon
//{
//	///(VOID)
//	///
//	///Preload the Engine by creating a new engine and also loading all rendering systems but not
//	///Storing or creating until statics are chosen
//	///
//	///No Params:
//	ArgonExport void PreLoadEngine()
//	{
//		ArgonEngine::instance()->Load(); //Preload all the Components
//	}
//
//	ArgonExport int GetRenderSystemCount()
//	{
//		return ArgonEngine::instance()->GetRenderSystemCount();
//	}
//
//	ArgonExport char* GetRenderSystemNameA(int RenderSystemIndex)
//	{
//		IRenderSystem* RenderSystem = ArgonEngine::instance()->GetRenderSystem(RenderSystemIndex);
//		IComponent* Component = NULL;
//		if(RenderSystem->QueryInterface(GUID_IComponent, (void**)&Component))
//		{
//			return Component->GetName().c_str();
//		}
//		return "";
//	}
//
//	ArgonExport int GetRenderSystemDriversCount(int RenderSystemIndex)
//	{
//		IRenderSystem* RenderSystem = ArgonEngine::instance()->GetRenderSystem(RenderSystemIndex);
//		if(RenderSystem)
//			return RenderSystem->GetDriverCount();
//		return 0; //No Render System was Found
//	}
//
//	ArgonExport int GetRenderSystemDriverModesCount(int RenderSystemIndex, int DriverIndex)
//	{
//		IRenderSystem* RenderSystem = ArgonEngine::instance()->GetRenderSystem(RenderSystemIndex);
//		if(RenderSystem)
//		{
//			IDriver* Driver = RenderSystem->GetDriver(DriverIndex);
//			if(Driver)
//			{
//				return Driver->GetVideoModeCount();
//			}
//		}
//		return 0;
//	}
//
//	ArgonExport char* GetRenderSystemDriverModeDescA(int RenderSystemIndex, int DriverIndex, int VideoIndex)
//	{
//		IRenderSystem* RenderSystem = ArgonEngine::instance()->GetRenderSystem(RenderSystemIndex);
//		if(RenderSystem)
//		{
//			IDriver* Driver = RenderSystem->GetDriver(DriverIndex);
//			if(Driver)
//			{
//				IVideoMode* VideoMode = Driver->GetVideoMode(VideoIndex);
//				return VideoMode->GetDescription().c_str();
//			}
//		}
//		return "";
//	}
//
//	ArgonExport void CreateEngine(int RenderSystemIndex, int DriverIndex, int VideoModeIndex, int* Window)
//	{
//		IRenderSystem* RenderSystem = ArgonEngine::instance()->GetRenderSystem(0);
//
//		if(RenderSystem)
//		{
//			RenderSystem->CreateDevice(DriverIndex, VideoModeIndex, Window);
//		}
//	}
//
//	ArgonExport void DestroyEngine()
//	{
//
//	}
//} //Namespace
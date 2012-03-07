///PRELOADENGINE(BOOL)
///
///	Preload the Engine by creating a new engine and also loading all rendering systems but not
// /Storing or creating until statics are chosen
///
///No Params:
ArgonExport bool PreLoadEngine()
{
	ArgonEngine::instance()->Load(); //Preload all the Components
	return true;
}

///CREATEENGINE(BOOL)
///
/// Create the engine using the specified RenderSystem and Drivers
///
///Param Window: A ptr to the window or a NULL for Full screen
///Param RenderSystemIndex: The desired render system to load
///Param DriverIndex: The Video driver to use
///Param ModeIndex: The Specific resolution that will be used
ArgonExport bool CreateEngine(void* Window, size_t RenderSystemIndex, size_t DriverIndex, size_t ModeIndex)
{
	return ArgonEngine::instance()->Create(Window, RenderSystemIndex, DriverIndex, ModeIndex);
}

///GETRENDERSYSTEMCOUNT(SIZE_T)
///
///Get the render system count
///
///No Params:
ArgonExport size_t GetRenderSystemCount()
{
	return ArgonEngine::instance()->GetRoot()->GetRenderSystemCount();
}

///GETRENDERSYSTEMNANE(CONSTCHAR)
///
///Get the desired render system name
///
///Param Index: 
ArgonExport const char* GetRenderSystemNameA(size_t Index)
{
	IRenderSystem* RenderSystem = ArgonEngine::instance()->GetRoot()->GetRenderSystem(Index);
	IComponent* Component = NULL;
	if(RenderSystem->QueryInterface(GUID_IComponent, (void**)&Component))
	{
		Component->UnLoad();
		return Component->GetName().c_str();
	}

	return "";
}

///GETRENDERSYSTEMDRIVERCOUNT(SIZE_T)
///
///Get the Driver count for the render system
///
///Param RenderSystemIndex: The render system that the drivers come from
ArgonExport size_t GetRenderSystemDriverCount(size_t RenderSystemIndex)
{
	IRenderSystem* RenderSystem = ArgonEngine::instance()->GetRoot()->GetRenderSystem(RenderSystemIndex);
	if(RenderSystem)
	{
		return RenderSystem->GetDriverCount();
	}

	return 0;
}

///GETRENDERSYSTEMDRIVERMODESCOUNT(SIZE_T)
///
///Get render system driver mode count
///
///Param RenderSystemIndex: The render system to be retrieved
///Param DriverIndex: The driver that will be retrieved
ArgonExport size_t GetRenderSystemDriverModesCount(size_t RenderSystemIndex, size_t DriveIndex)
{
	IRenderSystem* RenderSystem = ArgonEngine::instance()->GetRoot()->GetRenderSystem(RenderSystemIndex);
	if(RenderSystem)
	{
		IDriver* Driver = RenderSystem->GetDriver(DriveIndex);
		return Driver->GetVideoModeCount();
	}

	return 0;
}

///GETRENDERSYSTEMDRIVERMODE(CONSTCHAR)
///
///Get the description of the desired video mode
///
///Param RenderSystemIndex: The render system to be retrieved
///Param DriverIndex: The driver that will be retrieved
///Param VideoModeIndex: The video mode that will be used to specify the resolution
ArgonExport const char* GetRenderSystemDriverModeA(size_t RenderSystemIndex, size_t DriveIndex, size_t VideoModeIndex)
{
	IRenderSystem* RenderSystem = ArgonEngine::instance()->GetRoot()->GetRenderSystem(RenderSystemIndex);
	if(RenderSystem)
	{
		IDriver* Driver = RenderSystem->GetDriver(DriveIndex);
		IVideoMode* Mode = Driver->GetVideoMode(VideoModeIndex);
		return Mode->GetDescription().c_str();
	}

	return "";
}
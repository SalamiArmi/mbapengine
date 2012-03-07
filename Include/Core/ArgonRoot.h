#ifndef _ARGONROOT_HEADER_
#define _ARGONROOT_HEADER_

#include <Standard/ArgonStandard.h>
#include <Standard/ArgonVector.h>
#include <Interface/IArgonUnknownImp.h>
#include <Interface/IRenderSystem.h>
#include <Interface/IPlatform.h>
#include <Interface/IComponent.h>
#include <Interface/IFrameListner.h>
#include <Standard/ArgonSingleton.h>

#include <Core/ArgonSceneManager.h>

namespace Argon
{
	class Log;
	class SceneManager;
	class Timer;

	class Root : public singleton<Root>
	{
		friend singleton;
	public:
		Root(IPlatform* Platform);

		///SETPLATFORM(VOID)
		///
		/// Set the Desired platform
		///
		///Param Platfom: 
		void				SetPlatform(IPlatform* Platform);

		///LOAD(BOOL)
		///
		///Load and init the Root
		///
		///No Params:
		bool				Load();

		///UNLOAD(VOID)
		///
		///Release and Cleanup the Root
		///
		///No Params:
		bool				UnLoad();

		///CREATE(BOOL)
		///
		/// Create the Rendersystem with the desired Resolution and window
		///
		///No Params:
		bool				Create(void* Window, size_t RenderSystemIndex, size_t DriverIndex, size_t ModeIndex);

		///FRAMEUPDATE(BOOL)
		///
		/// Update the Frame
		///
		///Param DeltaT:
		bool				FrameUpdate(float DeltaT);

		///DRAWONEFRAME(BOOL)
		///
		/// Render a single fame
		///
		///Param DeltaT: The new frame time since last frame
		bool				DrawOneFrame();

		///GETRENDERSYSTEMCOUNT(SIZE_T)
		///
		///Get all the Found and loaded rendersystems once the render system is chosen all others are unloaded
		///
		///No Params:
		size_t				GetRenderSystemCount();

		///GETRENDERSYSTEM(IRENDERSYSTEM)
		///
		///Get a RenderSystem
		///
		///Param Index: Which render system to get
		IRenderSystem*		GetRenderSystem(size_t Index) const;

		///CREATESCENEMANAGER(SCENEMANAGER)
		///
		/// Create a new SceneManager
		///
		///No Params:
		SceneManager*		CreateSceneManager(QString Name);

		///UNLOADSCENEMANAGER(VOID)
		///
		///Unload a desired SceneManager
		///
		///Param Manager: The SceneManager that will be Destroyed or removed from existance
		void				UnLoadSceneManager(SceneManager* Manager);

		///GETCURRENTSCENEMANAGER(SCENEMANAGER)
		///
		/// Get the Current SceneManager that is being used to render the frames
		///
		///No Params:
		SceneManager*		GetCurrentSceneManager() const;

		///SETCURRENTSCENEMANAGER(VOID)
		///
		/// Set the Current SceneManager
		///
		///No Params:
		void				SetCurrentSceneManager(SceneManager* Manager);

		///ADDFRAMELISTNER(VOID)
		///
		/// Add a frame listner to the Render Calls
		///
		///Param FrameListner: The Listner that will be called when a new frame is rendered
		void				AddFrameListner(IFrameListner* FrameListner);

		///REMOVEFRAMELISTNER(VOID)
		///
		/// Remove the desired frame listners
		///
		///Param FrameListner: The Listner that will be removed from the New Frame Calls
		void				RemoveFrameListner(IFrameListner* FrameListner);

		///GETACTIVERENDERSYSTEM(IRENDERSYSTEM)
		///
		/// Get the current working render system
		///
		///No Params:
		IRenderSystem*		GetActiveRenderSystem() const;

	protected:
		Root();
		~Root();

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

		///RENDERLISTNERS(VOID)
		///
		/// Render all the listners if they support the desired pass
		///
		///
		///Param Pass:
		void				RenderListners(IFrameListner::RenderPass Pass);

	private:
		//Active Object
		IRenderSystem*			m_ActiveRenderSystem;
		SceneManager*			m_ActiveSceneManager;
		IPlatform*				m_Platform;

		Vector<IFrameListner*>	m_FrameListners;
		Vector<SceneManager*>	m_SceneManagers;
		Vector<IComponent*>		m_Components;
		Vector<IRenderSystem*>	m_LoadedRenderSystems;
		Vector<String>			m_FoundComponents;
	};

} //Namespace

#endif //_ARGONROOT_HEADER_
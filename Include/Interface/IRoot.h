#ifndef _IROOT_HEADER_
#define _IROOT_HEADER_

#include "IArgonUnknown.h"
#include "ISceneManager.h"
#include "IFrameListner.h"
#include "IRenderSystem.h"

#include <Standard/ArgonQString.h>

namespace Argon
{
	DeclareBasedInterface(IRoot, IArgonUnknown)
		
		///FRAMEUPDATE(BOOL)
		///
		/// Render a single fame
		///
		///Param DeltaT:
		bool				FrameUpdate(float DeltaT);

		///DRAWONEFRAME(BOOL)
		///
		/// Render a single fame
		///
		///No Params:
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
		ISceneManager*		CreateSceneManager(QString Name);

		///UNLOADSCENEMANAGER(VOID)
		///
		///Unload a desired SceneManager
		///
		///Param Manager: The SceneManager that will be Destroyed or removed from existance
		void				UnLoadSceneManager(ISceneManager* Manager);

		///GETCURRENTSCENEMANAGER(SCENEMANAGER)
		///
		/// Get the Current SceneManager that is being used to render the frames
		///
		///No Params:
		ISceneManager*		GetCurrentSceneManager() const;

		///SETCURRENTSCENEMANAGER(VOID)
		///
		/// Set the Current SceneManager
		///
		///No Params:
		void				SetCurrentSceneManager(ISceneManager* Manager);

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

	EndInterface(IRoot)

class IPlatform;

	ArgonExport void ArgonCreateRoot(IRoot** Root, IPlatform* Platform);

} //Namespace

#endif //_IROOT_HEADER_
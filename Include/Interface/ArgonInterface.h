#ifndef _ARGONINTERFACE_HEADER_
#define _ARGONINTERFACE_HEADER_

namespace Argon
{

#	ifndef ArgonInterface
#		define ArgonInterface class
#		define ArgonImplements public
#		define DeclareInterface(Name) __interface actual_##Name {
#		define DeclareBasedInterface(Name, Base) __interface actual_##Name : public actual_##Base {
#		define EndInterface(Name) }; ArgonInterface Name : public actual_##Name { public: virtual ~Name() { } };
#	endif

	enum GUID
	{
		GUID_IArgonUnknown = 0,
		GUID_IRenderSystem,			//The Render System for the Application
		GUID_IPlatform,				//What Platform the Application is Running
		GUID_IComponent,			//External and Internal Components
		GUID_IFrameListner,			//FrameListers will render or update
		GUID_ISeneManager,			//Scenemanager will create all Mesh and Renderable objects
		GUID_IBuffer,				//Device and System Buffers
		GUID_IDriver,				//Device Drivers
		GUID_IMesh,					//Mesh objects
		GUID_ISurface,				//Render Surface
		GUID_IVideoMode,			//Driver Video Information
		GUID_IMessageBoardReader,	//MessageBoard readers will recieve messages
		GUID_IRoot,					//Root creates and Initalises the Rendering Engine also shuts it down
		GUID_IWindow,				//Window is either created externally or internally by the create function
		GUID_IViewport,				//Viewports can allow multiple views for a backbuffer
		GUID_IFont,					//
		GUID_IText,					//
		GUID_IRenderable,			//
		GUID_IShader,				//
		GUID_ITexture,				//
	};
} //Namespace
 
#endif //_ARGONINTERFACE_HEADER_
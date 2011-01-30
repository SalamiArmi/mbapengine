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
		GUID_IRenderSystem,
		GUID_IPlatform,
		GUID_IComponent,
		GUID_IFrameListner,
		GUID_IBuffer,
		GUID_IDriver,
		GUID_IMesh,
		GUID_ISurface,
		GUID_IVideoMode,
		GUID_IMessageBoardReader,
	};
} //Namespace
 
#endif //_ARGONINTERFACE_HEADER_
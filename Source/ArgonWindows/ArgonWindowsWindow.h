#ifndef _ARGONWINDOWSWINDOWS_HEADER_
#define _ARGONWINDOWSWINDOWS_HEADER_

#include "ArgonWindows.h"

#include <Interface/IWindow.h>
#include <Interface/IArgonUnknownImp.h>

namespace Argon
{
	class Window : public IArgonUnknownImp<IWindow, GUID::GUID_IWindow>
	{
	public:
		Window();
		~Window();

		///CREATE(VOID)
		///
		/// Create the windows specific to the platform
		///
		///No Params:
		void	Create();

		///UNLOAD(BOOL)
		///
		/// Unload the window and destroy it
		///
		///No Params:
		bool	UnLoad();

		///GETHANDLE(VOIDPTR)
		///
		/// Get the Handle to the window
		///
		///No Params:
		void*	GetHandle();

		///SETHANDLE(VOID)
		///
		/// Set the Handle of a already created window
		///
		///Param Handle: The Handle to the window that is already created
		void	SetHandle(void* Handle);

	protected:
		HWND	m_Handle;
	};
} //Namespace

#endif //_ARGONWINDOWSWINDOWS_HEADER_
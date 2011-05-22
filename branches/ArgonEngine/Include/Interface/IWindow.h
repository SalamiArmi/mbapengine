#ifndef _IWINDOW_HEADER_
#define _IWINDOW_HEADER_

#include <Interface/IArgonUnknown.h>

namespace Argon
{
	DeclareBasedInterface(IWindow, IArgonUnknown)
		
		///CREATE(VOID)
		///
		/// Create the windows specific to the platform
		///
		///No Params:
		void	Create();

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

	EndInterface(IWindow)

} //Namespace

#endif //_IWINDOW_HEADER_
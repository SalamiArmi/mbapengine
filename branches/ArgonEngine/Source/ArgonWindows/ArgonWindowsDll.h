#ifndef _ARGONWINDOWSDLL_HEADER_
#define _ARGONWINDOWSDLL_HEADER_

#include <Standard/ArgonString.h>
#include "Windows.h"

namespace Argon
{
	class WindowsDll
	{
	public:
		WindowsDll(String Name, HINSTANCE Component);
		~WindowsDll();

		///GETNAME(STRING)
		///
		/// Get the Name of this Dll
		///
		///No Params:
		String GetName();

		///GETNAME(STRING)
		///
		/// Get the Instance or Component of this Dll
		///
		///No Params:
		HINSTANCE GetComponent();

	protected:
		String			m_Name;			//The name of the Component
		HINSTANCE		m_Component;	//The Instance of the Component
	}; //Class

} //Namespace

#endif //_ARGONWINDOWSDLL_HEADER_
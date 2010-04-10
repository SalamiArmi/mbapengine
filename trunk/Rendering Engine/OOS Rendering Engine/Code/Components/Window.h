#ifndef _WINDOW_HEADER_
#define _WINDOW_HEADER_

#include <windows.h>
#include <D3D10.h>

namespace OOS
{
	class Window
	{
	public:

		Window(HINSTANCE instance, int Width, int Height);
		~Window();

		bool Initiliase();

		void Update(float delatT);

		void Cleanup();

		int	&getHeight();
		int &getWidth();

		HWND getWindowHandle();
		
	private:

		//Window and Window Class
		HWND		m_Window;
		WNDCLASS	m_WindowClass;

		//Window Dimensions
		int		m_Width;
		int		m_Height;

		bool	m_Active;

		//Instance
		HINSTANCE m_Instance;
	};
}

#endif //_WINDOW_HEADER_
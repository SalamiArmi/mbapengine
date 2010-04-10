#include "Window.h"
#include "RenderingSystem.h"
#include "System.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
int wmId, wmEvent;
	HDC hdc;
	PAINTSTRUCT PS;

	switch (msg)
	{
	case WM_COMMAND:
		{
			wmId    = LOWORD(wParam);
			wmEvent = HIWORD(wParam);
		break;
		}
	case WM_ACTIVATE:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		OOS::System::getSingleton().Exit();
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &PS);
		EndPaint(hwnd, &PS);
		break;
	default:
		break;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}


namespace OOS
{
	Window::Window(HINSTANCE instance, int Width, int Height) : m_Instance(instance), m_Width(Width), m_Height(Height)
	{
		m_WindowClass.cbClsExtra = NULL;
		m_WindowClass.cbWndExtra= NULL;
		m_WindowClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		m_WindowClass.hCursor= NULL;
		m_WindowClass.hIcon= LoadIcon(m_Instance,"ApplicationIcon");
		m_WindowClass.lpszClassName= "OOS Rendering Engine";
		m_WindowClass.lpfnWndProc = WndProc;
		m_WindowClass.lpszMenuName = NULL;
		m_WindowClass.hInstance = m_Instance;
		m_WindowClass.style = CS_CLASSDC;

		if (RegisterClass(&m_WindowClass))
		{
			m_Window = CreateWindow("OOS Rendering Engine", "OOS Rendering Engine", WS_CAPTION | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 1024,768, NULL, NULL, m_Instance,0);

			if (!m_Window)
			{
				return;
			}
		}
	}

	Window::~Window()
	{

	}

	bool Window::Initiliase()
	{
		ShowWindow(m_Window, 1);
		UpdateWindow(m_Window);

		return true;
	}

	void Window::Update(float deltaT)
	{
	}

	void Window::Cleanup()
	{

	}

	int& Window::getWidth()
	{
		return m_Width;
	}

	int& Window::getHeight()
	{
		return m_Height;
	}

	HWND Window::getWindowHandle()
	{
		return m_Window;
	}
}
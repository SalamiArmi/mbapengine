#include "ArgonWindowsWindow.h"

namespace Argon
{
	Window::Window()
		: m_Handle(0x0)
	{

	}

	Window::~Window()
	{

	}

	void Window::Create()
	{
		
	}

	bool Window::UnLoad()
	{
		return false;
	}

	void* Window::GetHandle()
	{
		return m_Handle;
	}

	void Window::SetHandle(void* Handle)
	{
		m_Handle = Handle;
	}

} //Namespace
#include "ArgonWindowsWindow.h"

namespace Argon
{
	Window::Window()
		: m_Handle(0x0)
	{
		m_RefCount = 0;
	}

	Window::~Window()
	{

	}

	bool Window::Load()
	{
		assert(m_RefCount == 0);
		++m_RefCount;

		return true;
	}

	void Window::Create()
	{
		
	}

	bool Window::UnLoad()
	{
		if(m_RefCount > 1)
		{
			--m_RefCount;
		}
		else
		{
			IArgonUnknownImp<IWindow, GUID_IWindow>::UnLoad();
			return true;
		}

		return false;
	}

	void* Window::GetHandle()
	{
		return m_Handle;
	}

	void Window::SetHandle(void* Handle)
	{
		m_Handle = (HWND)Handle;
	}

} //Namespace
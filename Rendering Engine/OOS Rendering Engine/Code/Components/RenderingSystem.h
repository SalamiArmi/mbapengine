#ifndef _RENDERINGSYSTEM_HEADER_
#define _RENDERINGSYSTEM_HEADER_

#include "System.h"
#include "Singleton.h"

#include <d3d10.h>
#include <d3dx10.h>

namespace OOS
{
	class RenderTarget;

	class RenderingSystem
	{
	public:

		RenderingSystem( Window* Window );
		~RenderingSystem();

		bool	InitInstance();

		bool	RenderOneFrame();

		void	Cleanup();

		bool	isRunning();

		ID3D10Device*	getDx10Device();

		ID3D10Texture2D* getBackBuffer();

	private:

		void DumpMessages();

		bool m_Running;
		Window* m_Window;

		//Device Manager
		ID3D10Device*				m_Device;

		//Rendering chain
		IDXGISwapChain*				m_SwapChain;

		//Message queue from directx
		ID3D10InfoQueue*			m_MessageQueue;

		//Back buffer
		ID3D10Texture2D*			m_BackBuffer;

	};

}

#endif //_RENDERINGSYSTEM_HEADER_
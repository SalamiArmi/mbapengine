#ifndef _VIEWPORT_HEADER_
#define _VIEWPORT_HEADER_

#include "RenderingSystem.h"
#include "Vector2.h"
#include "DirectXObject.h"

namespace OOS
{
	class Camera;
	class RenderTarget;

	class Viewport : public DirectxObject<D3D10_VIEWPORT>
	{
	public:
		Viewport(Camera* Camera, int Width, int Height, Vector2 Position);
		~Viewport();

		Camera*	getCamera();
		void	setCamera(Camera* Camera);

		bool	update();

		int		getHeight();
		int		getWidth();

	private:

		int m_Width;
		int m_Height;

		Vector2 m_Position;

		//Stencil buffer
		ID3D10DepthStencilState*	m_DepthStencilState;
		ID3D10Texture2D*			m_DepthStencilBuffer;
		ID3D10DepthStencilView*		m_DepthStencilView;

		//RenderTarget
		RenderTarget*				m_RenderTarget;

		Camera* m_ViewportCamera;

	};
}


#endif //_VIEWPORT_HEADER_
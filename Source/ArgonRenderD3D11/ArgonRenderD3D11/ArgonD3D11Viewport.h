#ifndef _ARGOND3D11VIEWPORT_HEADER_
#define _ARGOND3D11VIEWPORT_HEADER_

#include <Interface/IViewport.h>
#include <Core/ArgonCamera.h>

#include <Standard/ArgonVector2.h>

#include "ArgonD3D11RenderSystem.h"

namespace Argon
{
	class D3D11Viewport : public IArgonUnknownImp<IViewport, GUID_IViewport> 
	{
	public:
		D3D11Viewport(Vector2 Dimensions, Vector2 Position);
		~D3D11Viewport();

		///(BOOL)
		///
		///
		///
		///
		///No Params:
		bool Load();

		///(BOOL)
		///
		///
		///
		///
		///No Params:
		bool UnLoad();

		///BEGIN(BOOL)
		///
		/// Begin Rendering for this viewport
		///
		///No Params:
		bool Begin();

		///END(BOOL)
		///
		/// Rendering for this viewport complete
		///
		///No Params:
		bool End();

		///GETPOSITION(VECTOR2)
		///
		/// Get the Top left corner of the Viewport
		///
		///No Params:
		Vector2 GetPosition();

		///GETDIMENSIONS(VECTOR2)
		///
		/// Get the Dimensions of the Viewport
		///
		///No Params:
		Vector2 GetDimensions();

		///SETENABLED(VOID)
		///
		/// Set if the viewport will be rendered to or not
		///
		///Param Enabled: The new State of the Viewport
		void SetEnabled(bool Enabled);

		///GETENABLED(BOOL)
		///
		/// Get if the Viewport will be rendered to or not
		///
		///No Params:
		bool GetEnabled();

		///(VOID)
		///
		/// Set the Camera that will be used for viewing
		///
		///Params Cam: The Camera that is required for attaining the View Projection Matrix
		void SetCamera(Camera* Cam);

		///(VOID)
		///
		/// Get the Camera in which rendering is begining viewed from
		///
		///No Params:
		Camera* GetCamera();

		///SETCLEARCOLOR(VOID)
		///
		/// Set the Clear color for this Viewport
		///
		///Params Alpha: How much Alpha will be used. 0 - 255
		///Params Alpha: How much Red will be used. 0 - 255
		///Params Alpha: How much Green will be used. 0 - 255
		///Params Alpha: How much Blue will be used. 0 - 255
		void SetClearColor(size_t Alpha, size_t Red, size_t Green, size_t Blue);

		///GETCLEARCOLOR(SIZE_T)
		///
		/// Get the Clear Color as a Array pointer
		///
		///No Params:
		size_t* GetClearColor();

		///GETD3D11VIEWPORT(D3D11_VIEWPORT)
		///
		/// Get the Directx 11 Viewport
		///
		///No Params:
		D3D11_VIEWPORT	GetD3D11Viewport();

	protected:
		D3D11_VIEWPORT	m_Viewport;

		bool			m_Enabled;
		Vector2			m_Dimensions;
		Vector2			m_Position;
		size_t*			m_ClearColor;
		Camera*			m_Camera;
	};
} //Namespace

#endif //_ARGOND3D11VIEWPORT_HEADER_
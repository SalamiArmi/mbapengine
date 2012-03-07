#ifndef _ARGOND3D10VIEWPORT_HEADER_
#define _ARGOND3D10VIEWPORT_HEADER_

#include <Interface/IViewport.h>
#include <Core/ArgonCamera.h>

#include <Standard/ArgonVector2.h>

#include "ArgonD3D10RenderSystem.h"

namespace Argon
{
	class D3D10Viewport : public IArgonUnknownImp<IViewport, GUID_IViewport> 
	{
	public:
		D3D10Viewport(Vector2T<uint> Dimensions, Vector2T<uint> Position);
		~D3D10Viewport();

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
		Vector2T<uint> GetPosition();

		///GETDIMENSIONS(VECTOR2)
		///
		/// Get the Dimensions of the Viewport
		///
		///No Params:
		Vector2T<uint> GetDimensions();

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

		///GETD3D10VIEWPORT(D3D10_VIEWPORT)
		///
		/// Get the Directx 11 Viewport
		///
		///No Params:
		D3D10_VIEWPORT&	GetD3D10Viewport();

	protected:
		D3D10_VIEWPORT	m_Viewport;

		bool			m_Enabled;
		Vector2T<uint>	m_Dimensions;
		Vector2T<uint>	m_Position;
		size_t*			m_ClearColor;
		Camera*			m_Camera;
	};
} //Namespace

#endif //_ARGOND3D10VIEWPORT_HEADER_
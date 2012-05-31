#ifndef _IVIEWPORT_HEADER_
#define _IVIEWPORT_HEADER_

#include <Interface/IArgonUnknown.h>

#include <Standard/ArgonVector2.h>
#include <Core/ArgonCamera.h>

namespace Argon
{
	DeclareBasedInterface(IViewport, IArgonUnknown)
		
		///BEGIN(BOOL)
		///
		/// Begin Rendering for this viewport
		///
		///No Params:
		virtual bool Begin() = 0;

		///END(BOOL)
		///
		/// Rendering for this viewport complete
		///
		///No Params:
		virtual bool End() = 0;

		///GETPOSITION(VECTOR2)
		///
		/// Get the Top left corner of the Viewport
		///
		///No Params:
		virtual Vector2T<uint> GetPosition() = 0;

		///GETDIMENSIONS(VECTOR2)
		///
		/// Get the Dimensions of the Viewport
		///
		///No Params:
		virtual Vector2T<uint> GetDimensions() = 0;

		///SETENABLED(VOID)
		///
		/// Set if the viewport will be rendered to or not
		///
		///Param Enabled: The new State of the Viewport
		virtual void SetEnabled(bool Enabled) = 0;

		///GETENABLED(BOOL)
		///
		/// Get if the Viewport will be rendered to or not
		///
		///No Params:
		virtual bool GetEnabled() = 0;

		///(VOID)
		///
		/// Set the Camera that will be used for viewing
		///
		///Params Cam: The Camera that is required for attaining the View Projection Matrix
		virtual void SetCamera(Camera* Cam) = 0;

		///(VOID)
		///
		/// Get the Camera in which rendering is begining viewed from
		///
		///No Params:
		virtual Camera* GetCamera() = 0;

		///SETCLEARCOLOR(VOID)
		///
		/// Set the Clear color for this Viewport
		///
		///Params Alpha: How much Alpha will be used. 0 - 255
		///Params Alpha: How much Red will be used. 0 - 255
		///Params Alpha: How much Green will be used. 0 - 255
		///Params Alpha: How much Blue will be used. 0 - 255
		virtual void SetClearColor(size_t Alpha, size_t Red, size_t Green, size_t Blue) = 0;

		///GETCLEARCOLOR(SIZE_T)
		///
		/// Get the Clear Color as a Array pointer
		///
		///No Params:
		virtual size_t* GetClearColor() = 0;

	EndInterface(IViewport)
} //Namespace

#endif //_IVIEWPORT_HEADER_
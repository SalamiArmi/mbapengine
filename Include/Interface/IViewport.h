#ifndef _IVIEWPORT_HEADER_
#define _IVIEWPORT_HEADER_

#include <Interface/ICamera.h>
#include <Standard/ArgonVector2.h>

namespace Argon
{
	DeclareBasedInterface(IViewport, IArgonUnknown)
		
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
		void SetCamera(ICamera* Cam);

		///(VOID)
		///
		/// Get the Camera in which rendering is begining viewed from
		///
		///No Params:
		ICamera* GetCamera();

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

	EndInterface(IViewport)
} //Namespace

#endif //_IVIEWPORT_HEADER_
#ifndef _RENDERTARGET_HEADER_
#define _RENDERTARGET_HEADER_

#include "Vector.h"
#include <string>
#include "DirectXObject.h"
#include "RenderingSystem.h"

namespace OOS
{
	class Viewport;

	class RenderTarget : public DirectxObject<ID3D10RenderTargetView*>
	{
	public:

		RenderTarget(Viewport* Viewport);
		~RenderTarget();

		void clear();

		///GETWIDTH(UINT)
		///
		///Get the width of the Rendertarget
		///
		///No Params:
		unsigned int getWidth(void) const;

		///GETHEIGHT(UINT)
		///
		///Get the height of the rendertarget
		///
		///No Params:
		unsigned int getHeight(void) const;

		///GETVIEWPORT(VIEWPORT)
		///
		///Get the viewport from the viewport list
		///
		///Param ViewportIndex: The index in which to retrieve the viewport
		Viewport* getViewport(unsigned int ViewportIndex) const;

		///GETNUMVIEWPORTS(UINT)
		///
		///Get the number of viewport attached to the rendertarget
		///
		///No Params:
		unsigned int getNumViewports(void) const;

		///REMOVEVIEWPORT(VOID)
		///
		///Remove the viewport at the index
		///
		///No Params:
		void removeViewport(unsigned short ViewportIndex);

		///REMOVEALLVIEWPORTS(VOID)
		///
		///Remove all the viewports from the list
		///
		///No Params:
		void removeAllViewports(void);


	protected:

		//The name of the rendertarget
		std::string m_Name;

		//The width and the height of the rendertarget
		unsigned int m_Width;
		unsigned int m_Height;

		//The list of viewports
		Vector<Viewport*> m_Viewports;

	};

}

#endif //_RENDERTARGET_HEADER_
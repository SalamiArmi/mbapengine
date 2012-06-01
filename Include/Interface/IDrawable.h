#ifndef _ARGONIDRAWABLE_HEADER_
#define _ARGONIDRAWABLE_HEADER_

#include "IArgonUnknown.h"

namespace Argon
{
	DeclareBasedInterface(IDrawable, IArgonUnknown)

		///SUPPORTSPASS(BOOL)
		///
		///Check if this Renderable Supports a pass
		///
		///Param Pass: The pass that will be checked against this is the current pass
		bool SupportsPass(IFrameListner::RenderPass Pass);
	
		///BIND(BOOL)
		///
		///Set all resources to the device and set all the render states and preserve current states
		///
		///No Params:
		bool Bind();

		///BIND(BOOL)
		///
		///Attempt to draw the Renderable
		///
		///No Params:
		bool FrameDraw();

		///UNBIND(BOOL)
		///
		/// Remove the Renderable from the device and reset any render states
		///
		///No Params:
		bool UnBind();
	
	EndInterface(IDrawable)
} //namespace

#endif //_ARGONIDRAWABLE_HEADER_
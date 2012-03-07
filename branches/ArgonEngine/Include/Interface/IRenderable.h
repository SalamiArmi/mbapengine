#ifndef _ARGONIRENDERABLE_HEADER_
#define _ARGONIRENDERABLE_HEADER_

#include "IArgonUnknown.h"

namespace Argon
{
	DeclareBasedInterface(IRenderable, IArgonUnknown)
	
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
	
	EndInterface(IRenderable)
} //namespace

#endif //_ARGONIRENDERABLE_HEADER_
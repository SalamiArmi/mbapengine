#ifndef _IFRAMELISTNER_HEADER_
#define _IFRAMELISTNER_HEADER_

#include "IArgonUnknown.h"

namespace Argon
{
	DeclareBasedInterface(IFrameListner, IArgonUnknown)

		enum RenderPass
		{
			RENDERPASS_Normal = 1 << 1,
			RENDERPASS_Post = 1 << 2,
			RENDERPASS_TopMost = 1 << 3,
		};

		///FRAMEUPDATE(VOID)
		///
		/// The frame needs to be updated so that objects are not in the same
		/// Positioin all the Time.
		///
		///Param DeltaT: Time since Last Frame
		virtual bool FrameUpdate(float DeltaT);

		///DRAW(BOOL)
		///
		///Draw the Graphical object
		///
		///Param Pass: The pass that will be preformed
		virtual bool FrameDraw(RenderPass Pass);

		///SUPPORTEDPASS(BOOL)
		///
		///Does the Graphics Support this pass if so make an attempt to render
		///
		///Param Pass: The Pass that will be checked against
		virtual bool SupportsPass(RenderPass Pass);

	EndInterface(IFrameListner)
} //Namespace

#endif //_IFRAMELISTNER_HEADER_
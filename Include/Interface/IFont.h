#ifndef _ARGONIFONT_HEADER_
#define _ARGONIFONT_HEADER_

#include <Standard/ArgonVector4.h>
#include <Standard/ArgonString.h>

namespace Argon
{
	enum TextAlign
	{
		TEXTALIGN_Left = 0,	//Align all text along the left side of the rectangle
		TEXTALIGN_Center,	//Align the centre of the text with the center of the rectangle
		TEXTALIGN_Right,	//Align the right side of the text with the right side of the rectangle
	};

	DeclareBasedInterface(IFont, IArgonUnknown)

		enum FontFlags
		{
			FONTFLAGS_DontCare		= 0,
			FONTFLAGS_Thin			= 100,
			FONTFLAGS_ExtraLight	= 200,
			FONTFLAGS_Light			= 300,
			FONTFLAGS_Normal		= 400,
			FONTFLAGS_Medium		= 500,
			FONTFLAGS_SemiBold		= 600,
			FONTFLAGS_Bold			= 700,
			FONTFLAGS_ExtraBold		= 800,
			FONTFLAGS_Heavy			= 900,
		};

		///BIND(BOOL)
		///
		/// Set all resources to the device and set all the render states and preserve current states
		///
		///No Params:
		bool Bind();

		///DRAW(BOOL)
		///
		/// Draw the Graphical object
		///
		///No Params:
		bool Draw(String Text, Vector4 Color, Vector3 Position, Vector3 Scale, TextAlign Align);

		///UNBIND(BOOL)
		///
		/// Remove the font from the device and reset any render states
		///
		///No Params:
		bool UnBind();

	EndInterface(IFont)
} //Namespace

#endif //_ARGONIFONT_HEADER_
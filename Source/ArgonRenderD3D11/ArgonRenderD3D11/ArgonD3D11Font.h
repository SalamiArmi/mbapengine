#ifndef _ARGOND3D11FONT_HEADER_
#define _ARGOND3D11FONT_HEADER_

#include <Interface/IFrameListner.h>

#include "ArgonD3D11RenderSystem.h"

namespace Argon
{
	class D3D11Font : IArgonUnknownImp<IFont, GUID_IFont>
	{
	public:
		D3D11Font();

		///LOAD(BOOL)
		///
		///Load the Interface All interfaces must use this
		///
		///No Params:
		bool	Load();

		///RELEASE(BOOL)
		///
		///Either Release a reference or release the object
		///
		///No Params:
		bool	UnLoad();

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
		bool Draw(String Text, Color Col, Vector3 Position, Vector3 Scale, IText::TextAlign Align);

		///UNBIND(BOOL)
		///
		/// Remove the font from the device and reset any render states
		///
		///No Params:
		bool UnBind();

	private:

		struct FontVertex
		{
			Vector3		Position;
			Color		Col;
			Vector2 TextCoord;
		};

		~D3D11Font();

		static ID3D11InputLayout*	m_Decleration;

		ID3DBlob*					m_Shader;
		ID3D11ShaderResourceView*	m_Font;
		Vector<FontVertex>			m_FontVerts;
		ID3D11Buffer*				m_FontBuffer;
		uint						m_BufferBytes;
	};
} //Namespace

#endif //_ARGOND3D11FONT_HEADER_
#ifndef  _ARGONTEXT_HEADER_
#define _ARGONTEXT_HEADER_

#include <Standard/ArgonQString.h>
#include <Standard/ArgonVector4.h>

#include <Interface/IRenderable.h>
#include <Interface/IFont.h>

namespace Argon
{
	class Text : public SceneNode, public IArgonUnknownImp<IRenderable, GUID_IRenderable>
	{
	public:
		Text(QString Name);

		///LOAD(BOOL)
		///
		/// Create the Font and all required resources
		///
		///No Params:
		bool Load();

		///UNLOAD(BOOL)
		///
		///Attempt to release a reference
		///Once the reference is zero automatically cleanup this object
		///If the instance was cleanedup because of zero references will return true else it will return false
		///
		///No Params:
		bool UnLoad();

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

		///SETCOLOR(VOID)
		///
		/// Set the Desired Color of the Text item
		///
		///Param Col: Set the Color of the Text
		void SetColor(Vector4 Col);

		///GETCOLOR(COLOR)
		///
		/// Get the current Vector4 of the Text
		///
		///No Params:
		Vector4 GetColor();

		///SETTEXT(VOID)
		///
		/// Set the currently displaying text
		///
		///Param Text: The Text that will be displayed when rendering
		void SetText(String Text);

		///GETTEXT(STRING)
		///
		/// Get the current text that is being displayed when rendering
		///
		///No Params:
		String GetText();

		///SETALIGN(VOID)
		///
		/// Set the position of which the text will render within the desired rectangle
		///
		///Params Align: The desired position of which the text will render within the desired rectangle
		void SetAlign(TextAlign Align);

		///GSETALIGN(TEXTALIGN)
		///
		/// Get the position of which the text will render within the desired rectangle
		///
		///No Params:
		TextAlign GetAlign();

	protected:
		~Text();
		
		IFont*					m_Font;

		String					m_Text;
		Vector4					m_Color;
		TextAlign				m_Alignment;
	};
} //namespace

#endif //_ARGONTEXT_HEADER_
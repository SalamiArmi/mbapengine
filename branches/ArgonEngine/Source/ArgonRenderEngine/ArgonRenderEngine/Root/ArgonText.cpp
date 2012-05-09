#include "ArgonRoot.h"
#include "ArgonText.h"

namespace Argon
{
	Text::Text(QString Name)
		: SceneNode(Name),
		m_Font(NULL),
		m_Text(""),
		m_Alignment(TEXTALIGN_Left),
		m_Color(Vector4(1.0f, 1.0f, 1.0f, 1.0f))
	{
	}

	Text::~Text()
	{

	}

	bool Text::Load()
	{
		m_Font = Root::instance()->GetActiveRenderSystem()->CreateAFont();
		return true;
	}

	bool Text::UnLoad()
	{
		return false;
	}

	bool Text::Bind()
	{
		return m_Font->Bind();
	}

	bool Text::FrameDraw()
	{
		return m_Font->Draw(m_Text, m_Color, Vector3(0,0,0), Vector3(1,1,0), m_Alignment);
	}

	bool Text::UnBind()
	{
		return m_Font->UnBind();
	}

	void Text::SetColor(Vector4 Col)
	{
		m_Color = Col;
	}

	Vector4 Text::GetColor()
	{
		return m_Color;
	}

	void Text::SetText(String Text)
	{
		m_Text = Text;
	}

	String Text::GetText()
	{
		return m_Text;
	}

	void Text::SetAlign(TextAlign Align)
	{
		m_Alignment = Align;
	}

	TextAlign Text::GetAlign()
	{
		return m_Alignment;
	}

} //namespace
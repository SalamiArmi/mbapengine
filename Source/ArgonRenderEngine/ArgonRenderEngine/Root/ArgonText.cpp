#include "ArgonRoot.h"
#include "ArgonText.h"

namespace Argon
{
	Text::Text(String Name)
		: Entity(Name, Entity::TYPE_Text),
		m_Font(NULL),
		m_Text("HELLO WORLD"),
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

	bool Text::SupportsPass(IFrameListner::RenderPass Pass)
	{
		return (Pass & IFrameListner::RENDERPASS_TopMost);
	}

	bool Text::Bind()
	{
		return m_Font->Bind();
	}

	bool Text::FrameDraw()
	{
		bool DrawnText = m_Font->Draw(m_Text, m_Color, m_WorldTransform.GetTranslation(), m_WorldTransform.GetScale(), m_Alignment);
		ArgonAssert(DrawnText);
		return DrawnText;
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
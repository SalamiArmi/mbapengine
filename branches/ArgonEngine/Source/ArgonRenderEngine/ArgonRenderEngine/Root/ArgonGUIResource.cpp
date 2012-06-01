#include "ArgonGUIResource.h"

#include "ArgonRoot.h"
#include "ArgonGUIManager.h"

namespace Argon
{
	GUIResource::GUIResource(String ResourceName)
		: Entity(ResourceName, Entity::TYPE_GUI),
		IArgonUnknownImp<IDrawable, GUID_IDrawable>(),
		m_DrawOrder(0),
		m_Texture(NULL)
	{
	}

	GUIResource::~GUIResource()
	{

	}

	bool GUIResource::Load()
	{
		return true;
	}

	void GUIResource::SetTexture(TextureResource* Texture)
	{
		m_Texture = Texture;

		m_Dimensions.x = m_Texture->GetWidth();
		m_Dimensions.y = m_Texture->GetHeight();
	}

	TextureResource* GUIResource::GetTexture()
	{
		return m_Texture;
	}

	void GUIResource::SetHotSpot(Vector2 HotSpot)
	{
		m_HotSpot = HotSpot;
	}

	Vector2& GUIResource::GetHotSpot()
	{
		return m_HotSpot;
	}

	void GUIResource::SetDimensions(Vector2 Dimensions)
	{
		m_Dimensions = Dimensions;
	}

	Vector2& GUIResource::GetDimensions()
	{
		return m_Dimensions;
	}

	int& GUIResource::GetDrawOrder()
	{
		return m_DrawOrder;
	}

	void GUIResource::SetDrawOrder(int DrawOrder)
	{
		m_DrawOrder = DrawOrder;
	}

	bool GUIResource::SupportsPass(IFrameListner::RenderPass Pass)
	{
		return (IFrameListner::RENDERPASS_TopMost == (Pass & IFrameListner::RENDERPASS_TopMost));
	}

	bool GUIResource::Bind()
	{	
		GUIManager* Manager = (GUIManager* )Root::instance()->GetComponent("GUI Manager");
		if(Manager)
			Manager->AddSpriteInstance(this);
		return true;
	}

	bool GUIResource::FrameDraw()
	{
		return true;
	}

	bool GUIResource::UnBind()
	{
		return true;
	}

} //namespace
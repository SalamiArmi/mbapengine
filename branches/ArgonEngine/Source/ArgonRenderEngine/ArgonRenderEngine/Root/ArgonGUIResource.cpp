#include "ArgonGUIResource.h"

namespace Argon
{
	GUIResource::GUIResource(String ResourceName)
		: Entity(ResourceName, Entity::TYPE_GUI),
		m_DrawOrder(0),
		m_Texture(NULL)
	{
	}

	GUIResource::~GUIResource()
	{

	}

	void GUIResource::SetTexture(ITexture* Texture)
	{
		m_Texture = Texture;
	}

	ITexture* GUIResource::GetTexture()
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

} //namespace
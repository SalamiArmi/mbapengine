#include "ArgonGUIManager.h"

namespace Argon
{
	GUIManager::GUIManager()
		: m_MaxSprites(0x0),
		m_Sprite(NULL)
	{

	}
	
	GUIManager::~GUIManager()
	{
	}

	QString GUIManager::GetName()
	{

	}

	GUIResource* GUIManager::CreateResource(String Name)
	{
		
	}

	bool GUIManager::FrameDraw(RenderPass Pass)
	{
		return false;
	}

	bool GUIManager::SupportsPass(RenderPass Pass)
	{
		return false;
	}

} //namespace
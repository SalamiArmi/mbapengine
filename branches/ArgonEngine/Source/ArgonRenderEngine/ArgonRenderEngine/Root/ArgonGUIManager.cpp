#include "ArgonGUIManager.h"
#include "ArgonRoot.h"

#define ArgonMaxSprites 4096

namespace Argon
{
	GUIManager::GUIManager()
		: m_MaxSprites(1),
		m_Sprite(NULL)
	{

	}
	
	GUIManager::~GUIManager()
	{
	}

	QString GUIManager::GetName()
	{
		return QString("GUIManager");
	}

	bool GUIManager::Load()
	{
		AddRef();
		return true;
	}

	GUIResource* GUIManager::CreateResource(String Name)
	{
		m_Resources.Push_Back(new GUIResource(Name));

		if(m_MaxSprites == m_Resources.Size())
		{
			if(m_Resources.Size() >= ArgonMaxSprites)
			{
				ArgonAssert(false); //We are at the max sprited do not recreate
				return NULL;
			}

			if(m_Sprite)
			{
				m_Sprite->UnLoad();
				m_Sprite = NULL;
			}
			
			m_MaxSprites = m_MaxSprites * 2;
			m_Sprite = Root::instance()->GetActiveRenderSystem()->CreateSprite(m_MaxSprites);
		}

		return m_Resources.Back();
	}

	bool GUIManager::FrameDraw(RenderPass Pass)
	{		
		if(m_Sprite && m_Resources.Size() > 0)
		{ 
			Refresh(); //TODO Flag Dirty
			
			if(m_Sprite->Bind())
			{
				bool Success = m_Sprite->Draw(false); //Draw
				m_Sprite->UnBind();

				return Success;
			}

			//Report Bind failed
		}

		return false;
	}

	bool GUIManager::SupportsPass(RenderPass Pass)
	{
		return (IFrameListner::RENDERPASS_TopMost == (Pass & IFrameListner::RENDERPASS_TopMost));
	}

	void GUIManager::Refresh()
	{
		m_Sprite->ClearSpriteInstances(); //Clear the current Instances

		//Repopulate
		QuickSort(); //Sort by RenderOrder
		
		for(Vector<GUIResource*>::Iterator it = m_Resources.Begin(); it != m_Resources.End(); ++it)
		{
#if _DEBUG
			ArgonAssert(m_Sprite->AddSpriteInstance((*it)->GetWorldTransform(), (*it)->GetHotSpot(), (*it)->GetDimensions(), (*it)->GetTexture()));
#else
			m_Sprite->AddSpriteInstance((*it)->GetTransform(), (*it)->GetHotSpot(), (*it)->GetDimensions(), (*it)->GetTexture());
#endif
		}
	}

	void GUIManager::QuickSort()
	{
		int Middle = SortPartition(0, m_Resources.Size());
		SortPartition(0, Middle);
		SortPartition(Middle + 1, m_Resources.Size());
	}

	int GUIManager::SortPartition(int Start, int End)
	{
		int x = m_Resources[Start]->GetDrawOrder();
		int i = Start - 1;
		int j = End + 1;
		GUIResource* Temp = NULL;
		do
		{
			do      
			{
				--j;
			}
			while (x < m_Resources[j]->GetDrawOrder());

			do  
			{
				++i;
			} 
			while (x > m_Resources[i]->GetDrawOrder());

			if (i < j)
			{ 

				Temp = m_Resources[i];    // switch elements at positions i and j
				m_Resources[i] = m_Resources[j];
				m_Resources[j] = Temp;
			}
		}
		while (i < j);  

		return j;           // returns middle index 
	}

} //namespace
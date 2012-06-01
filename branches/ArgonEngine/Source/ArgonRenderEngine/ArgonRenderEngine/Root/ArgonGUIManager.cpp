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
		return QString("GUI Manager");
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

	void GUIManager::AddSpriteInstance(GUIResource* Resource)
	{
		//Check if the Resource is already in the list
		for(Vector<GUIResource*>::Iterator it = m_SpriteInstances.Begin(); it != m_SpriteInstances.End(); ++it)
		{
			if((*it) == Resource)
			{
				return;
			}
		}

		//Add to buffer list
		m_SpriteInstances.Push_Back(Resource);
	}

	bool GUIManager::DrawBufferedInstances(bool Clear)
	{
		if(m_Sprite && m_SpriteInstances.Size() > 0)
		{ 
			Refresh(); //TODO Flag Dirty
			
			if(m_Sprite->Bind())
			{
				bool Success = m_Sprite->Draw(Clear); //Draw
				m_Sprite->UnBind();

				return Success;
			}

			//Report Bind failed
		}

		return false;
	}

	void GUIManager::Refresh()
	{
		m_Sprite->ClearSpriteInstances(); //Clear the current Instances

		//Repopulate
		QuickSort(); //Sort by RenderOrder
		
		for(Vector<GUIResource*>::Iterator it = m_SpriteInstances.Begin(); it != m_SpriteInstances.End(); ++it)
		{
#if _DEBUG
			ArgonAssert(m_Sprite->AddSpriteInstance((*it)->GetWorldTransform(), (*it)->GetHotSpot(), (*it)->GetDimensions(), (*it)->GetTexture()->GetResource()));
#else
			m_Sprite->AddSpriteInstance((*it)->GetTransform(), (*it)->GetHotSpot(), (*it)->GetDimensions(), (*it)->GetTexture());
#endif
		}
	}

	void GUIManager::QuickSort()
	{
		if(m_SpriteInstances.Size() < 2) 
			return;

		int Middle = SortPartition(0, m_SpriteInstances.Size());
		SortPartition(0, Middle);
		SortPartition(Middle + 1, m_SpriteInstances.Size());
	}

	int GUIManager::SortPartition(int Start, int End)
	{
		int x = m_SpriteInstances[Start]->GetDrawOrder();
		int i = Start - 1;
		int j = End + 1;
		GUIResource* Temp = NULL;
		do
		{
			do      
			{
				--j;
			}
			while (x < m_SpriteInstances[j]->GetDrawOrder());

			do  
			{
				++i;
			} 
			while (x > m_SpriteInstances[i]->GetDrawOrder());

			if (i < j)
			{ 

				Temp = m_Resources[i];    // switch elements at positions i and j
				m_SpriteInstances[i] = m_SpriteInstances[j];
				m_SpriteInstances[j] = Temp;
			}
		}
		while (i < j);  

		return j;           // returns middle index 
	}

} //namespace
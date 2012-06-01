#include "ArgonGeometryManager.h"

namespace Argon
{

	GeometryManager::GeometryManager()
	{
	}

	GeometryManager::~GeometryManager()
	{

	}

	bool GeometryManager::Load()
	{
		AddRef();
		return true;
	}

	QString GeometryManager::GetName()
	{
		return "Geometry Manager";
	}

	GeometryResource* GeometryManager::CreateResource(String Name)
	{
		return new GeometryResource(Name);
	}


	bool GeometryManager::FrameDraw(RenderPass Pass)
	{
		return false;
	}

	bool GeometryManager::SupportsPass(IFrameListner::RenderPass Pass)
	{
		return (IFrameListner::RENDERPASS_Normal == (Pass & IFrameListner::RENDERPASS_Normal));
	}
}
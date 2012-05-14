#include "ArgonGeometryManager.h"

namespace Argon
{

	GeometryManager::GeometryManager()
	{
	}

	GeometryManager::~GeometryManager()
	{
	}

	QString GeometryManager::GetName()
	{
		return "Geometry Manager";
	}

	GeometryResource* GeometryManager::CreateResource(String Name)
	{
		return new GeometryResource(Name);
	}
}
#define _RESOURCEDATABASE_HEADER_
#ifdef _RESOURCEDATABASE_HEADER_

#include <string>
#include "Pair.h"

namespace OOS
{
	class Resource;

	class ResourceDatabase
	{
	public:
		ResourceDatabase();
		~ResourceDatabase();

		void loadAllResources();
		void loadResource(unsigned int Index);
		void loadResource(std::string Name);

		void releaseAllResources();
		void releaseResource(unsigned int Index);
		void releaseResource(std::string Name);

	private:

		Pair<std::string Name, Resource*> m_Resources;

	};

}

#endif //_RESOURCEDATABASE_HEADER_
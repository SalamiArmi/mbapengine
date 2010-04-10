#define _RESOURCEMANAGER_HEADER_
#ifdef _RESOURCEMANAGER_HEADER_

#include <string>
#include "Windows.h"

namespace OOS
{
	class ResourceDatabase;

	class ResourceManager
	{
	public:
		ResourceManager( std::string RootScanDirectory, bool AutomaticallyLoadResources = true );
		~ResourceManager();

		void setMemoryBudget(SIZE_T bytes);
		SIZE_T getMemoryBudget();

		SIZE_T getMemoryUsage();

		void prepare(std::string Name, std::string FileLocation);

		void reloadAll(bool reloadableOnly = true);
		void unloadAll(bool reloadableOnly = true);

		bool resourceExists(std::string Name);

	private:

		SIZE_T m_CurrentMemoryUsage;
		SIZE_T m_MaxMemoryUsage;

		ResourceDatabase* m_ResourceDatabase;
	};

}

#endif //_RESOURCEMANAGER_HEADER_
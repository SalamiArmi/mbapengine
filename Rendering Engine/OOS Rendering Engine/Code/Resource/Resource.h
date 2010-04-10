#define _RESOURCE_HEADER_
#ifdef _RESOURCE_HEADER_

#include <string>
#include "Pair.h"

namespace OOS
{
	class Manager;

	class Resource
	{
	public:
		Resource(Manager* Manager, std::string Name, std::string FileLocation);
		virtual ~Resource();

		virtual Manager* getManager() { return m_Manager; }
		std::string getName() { return m_Name; }
		std::string getFileLocation() { return m_FileLocation; }

	private:
		std::string m_Name;
		std::string m_FileLocation;

		Manager* m_Manager;
	};
}

#endif //_RESOURCE_HEADER_
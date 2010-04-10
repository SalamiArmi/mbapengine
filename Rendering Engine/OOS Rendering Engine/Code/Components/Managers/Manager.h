#define _MANAGER_HEADER_
#ifdef _MANAGER_HEADER_

#include <string>
#include "Vector.h"

namespace OOS
{

	enum ManagerType
	{
		GeometryManager = 0,
		ShaderManager,
		ScaneManager,
		NumOfManagers
	};

	class Resource;

	class Manager
	{
	public:
		Manager();
		virtual ~Manager();

		virtual bool update( );

		unsigned short getResourceNum();

		virtual bool Contains(std::string File);
		virtual bool Contains(Resource* Resource);
		Resource* getResource(unsigned short Index);

	protected:
		std::string m_Name;
		Vector<Resource*> m_Resources;
	};
}

#endif //_MANAGER_HEADER_
#define _VISUAL_HEADER_
#ifdef _VISUAL_HEADER_

#include <string>
#include "MovableObject.h"

namespace OOS
{
	enum VisualType
	{
		VisualType_Geometry = 0
	};

	class Visual : public MovableObject
	{
	public:
		Visual( std::string meshName );
		~Visual();

	private:
		VisualType m_Type;
	};
}

#endif //_VISUAL_HEADER_
#define _MOVABLEOBJECT_HEADER_
#ifdef _MOVABLEOBJECT_HEADER_

#include <string>
#include "Factory.h"
#include "Vector3.h"

namespace OOS
{
	class SceneManager;
	class SceneNode;

	class MovableObject
	{
	public:
		virtual ~MovableObject();

		virtual void update(float DeltaT);

		void setName(std::string Name);
		std::string getName() const;

		virtual SceneNode* getParentSceneNode() const;
		virtual void detachFromParent();

		bool isAttached() const;

		void setVisible(bool Visible);
		bool getVisible() const;

	protected:
		std::string m_Name;

		Factory<MovableObject*> m_Creator;

		SceneManager* m_Manager;

		bool m_Visible;

		bool m_BeyondFarDistance;

		SceneNode* m_ParentSceneNode;
	};
}

#endif //_MOVABLEOBJECT_HEADER_
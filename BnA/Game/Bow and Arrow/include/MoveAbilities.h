#ifndef _MOVEABILITIES_HEADER_
#define _MOVEABILITIES_HEADER_

#include "BaseAbilities.h"

class MoveAbilities : public BaseAbilities
{
public:
	MoveAbilities(std::string Name, GameObject* OwnerObject);
	~MoveAbilities();

	void Update(Ogre::Real DeltaT);
	void Exit();

	std::string getType();

	std::string getName();

	void setName(std::string Name);

private:
	void updateInput(Ogre::Real DeltaT);

protected:

	Ogre::Real m_MoveScale;

};

#endif //_MOVEABILITIES_HEADER_
#ifndef _DEATHABILITIES_HEADER_
#define _DEATHABILITIES_HEADER_

#include "BaseAbilities.h"

class DeathAbilities : public BaseAbilities
{
public:
	DeathAbilities(std::string Name, GameObject* OwnerObject);
	~DeathAbilities();

	void Update(Ogre::Real DeltaT);
	void Exit();

	std::string getType();

	std::string getName();

	void setName(std::string Name);

protected:

};

#endif //_DEATHABILITIES_HEADER_
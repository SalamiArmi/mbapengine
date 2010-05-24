#ifndef _LOOKABILITIES_HEADER_
#define _LOOKABILITIES_HEADER_

#include "BaseAbilities.h"

class LookAbilities : public BaseAbilities
{
public:

	LookAbilities(std::string Name, GameObject* OwnerObject);
	~LookAbilities();

	void Update(Ogre::Real DeltaT);
	void Exit();

	std::string getType();

	std::string getName();

	void setName(std::string Name);


protected:

};

#endif //_LOOKABILITIES_HEADER_
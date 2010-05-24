#ifndef _JUMPABILITIES_HEADER_
#define _JUMPABILITIES_HEADER_

#include "BaseAbilities.h"

class JumpAbilities : public BaseAbilities
{
public:

	JumpAbilities(std::string Name, GameObject* OwnerObject);
	~JumpAbilities();

	void Update(Ogre::Real DeltaT);
	void Exit();

	std::string getType();

	std::string getName();
	void setName(std::string Name);

private:



};

#endif //_JUMPABILITIES_HEADER_
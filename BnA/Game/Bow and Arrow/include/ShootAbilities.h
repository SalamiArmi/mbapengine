#ifndef _SHOOTABILITIES_HEADER_
#define _SHOOTABILITIES_HEADER_

#include "BaseAbilities.h"

class ShootAbilities : public BaseAbilities
{
public:

	ShootAbilities(std::string Name, GameObject* OwnerObject);
	~ShootAbilities();

	void Update(Ogre::Real DeltaT);
	void Exit();

	std::string getType();

	void setName(std::string Name);

	std::string getName();

	XInputManager* getControllerInput();

protected:

};

#endif //_SHOOTABILITIES_HEADER_
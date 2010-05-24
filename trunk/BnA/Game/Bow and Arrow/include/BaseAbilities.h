#ifndef _BASEABILITIES_HEADER_
#define _BASEABILITIES_HEADER_

#include "Precompiled.h"
#include "Xbox360Controller.h"
#include "AbilityManager.h"
#include "GameObject.h"

class BaseAbilities : public ErrorReporter
{
public:

	virtual ~BaseAbilities();

	///(VOID)
	///
	///All objects that inherit this class gain the ability in update
	///
	///No Params:
	virtual void Update(Ogre::Real DeltaT) = 0;

	/// (VOID)
	///
	///This function controls the cleanup of the inherited classes
	///
	///No Params:
	virtual void Exit() = 0;

	virtual std::string getType() = 0;

	virtual void setName(std::string Name) = 0;

	virtual std::string getName() = 0;

	XInputManager* getControllerInput();
	
protected:

	std::string m_Name;

	GameObject* m_OwnerObject;

private:


};

#endif //_BASEABILITIES_HEADER_
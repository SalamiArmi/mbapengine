#ifndef _ABILITYMANAGER_HEADER_
#define _ABILITYMANAGER_HEADER_

#include <vector>
#include "ErrorReporter.h"

class BaseAbilities;
class GameObject;

enum AbilityType
{
	eMoveAbilities = 0,
	eLookAbilities,
	eJumpAbilities,
	eShootAbilities,
	eDeathAbilities
};

class AbilityManager : public ErrorReporter
{
public:

	AbilityManager();
	~AbilityManager();

	void Update(Ogre::Real DeltaT);

	BaseAbilities* CreateAbility(AbilityType Ability, std::string Name, GameObject* AttachAbilityTo);
	BaseAbilities* getAbility(std::string ByName);
	BaseAbilities* getAbility(int Index);

	void DestroyAbility(BaseAbilities* Ability);
	void DestroyAbility(std::string &AbilityName);
	void DestroyAbility(int Index);

	int getAbilityCount();

protected:

	//A list of all abilities in the wold that are in use
	std::vector<BaseAbilities*>	m_Abilities;

	Ogre::Log* m_OgreLog;

};

#endif //_ABILITYMANAGER_HEADER_
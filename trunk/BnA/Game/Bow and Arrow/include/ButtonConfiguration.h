#ifndef _BUTTONCONFIGURATION_HEADER_
#define _BUTTONCONFIGURATION_HEADER_

class XInputManager;
class BaseAbilities;

#include <map>

enum eControllerInput
{
	ButtonA = 0,
	ButtonB,
	ButtonX,
	ButtonY,
	RightTrigger,
	RightShoulder,
	RightThumbStick,
	LeftTrigger,
	LeftShoulder,
	LeftThumbStick,
	ControllerInput_Size
};

//enum eTriggeredAction
//{
//	Jump = 0,
//	Look,
//	Move,
//	Shoot,
//	TriggeredAction_Size
//};

class ButtonConfiguration
{
public:	
	
	ButtonConfiguration();
	~ButtonConfiguration();

	void setInverted(bool isInverted);
	bool isLookInverted();

	std::map<const eControllerInput, BaseAbilities*> getControllerScheme();

	eControllerInput getButtonPushed(XInputManager* controller);
	bool isButtonPushed(XInputManager* controller, eControllerInput ControllerInput);

private:

	bool m_InvertLook;
	std::map<const eControllerInput, BaseAbilities*> m_ControllerScheme;
};

#endif //_BUTTONCONFIGURATION_HEADER_
#include "Precompiled.h"
#include "ButtonConfiguration.h"
#include "Xbox360Controller.h"

ButtonConfiguration::ButtonConfiguration() :
m_InvertLook(false)
{
}

ButtonConfiguration::~ButtonConfiguration()
{

}

bool ButtonConfiguration::isLookInverted()
{
	return m_InvertLook;
}

void ButtonConfiguration::setInverted(bool isInverted)
{
	m_InvertLook = isInverted;
}

std::map<const eControllerInput, BaseAbilities*> ButtonConfiguration::getControllerScheme()
{
	return m_ControllerScheme;
}

eControllerInput ButtonConfiguration::getButtonPushed(XInputManager *controller)
{
	if(controller->GetState(0).Buttons.A)
		return ButtonA;
	else if(controller->GetState(0).Buttons.B)
		return ButtonB;
	else if(controller->GetState(0).Buttons.X)
		return ButtonX;
	else if(controller->GetState(0).Buttons.Y)
		return ButtonY;
	else if(controller->GetState(0).Buttons.RightShoulder)
		return RightShoulder;
	else if(controller->GetState(0).RightTrigger)
		return RightTrigger;
	else if(controller->GetState(0).Buttons.LeftShoulder)
		return LeftShoulder;
	else if(controller->GetState(0).LeftTrigger)
		return RightTrigger;
}

bool ButtonConfiguration::isButtonPushed(XInputManager *controller, eControllerInput ControllerInput)
{
	if(controller->GetState(0).Buttons.A && ControllerInput == ButtonA)
		return true;
	else if(controller->GetState(0).Buttons.B && ControllerInput == ButtonB)
		return true;
	else if(controller->GetState(0).Buttons.X && ControllerInput == ButtonX)
		return true;
	else if(controller->GetState(0).Buttons.Y && ControllerInput == ButtonY)
		return true;
	else if(controller->GetState(0).Buttons.RightShoulder && ControllerInput == RightShoulder)
		return true;
	else if(controller->GetState(0).RightTrigger && ControllerInput == RightTrigger)
		return true;
	else if(controller->GetState(0).Buttons.LeftShoulder && ControllerInput == LeftShoulder)
		return true;
	else if(controller->GetState(0).LeftTrigger && ControllerInput == LeftTrigger)
		return true;
	else
		return false;
}
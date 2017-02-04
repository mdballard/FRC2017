/*
 * Xbox360_Controller.cpp
 *
 *  Created on: Feb 26, 2015
 *      Author: Matthew
 */

#include "Xbox360_Controller.h"


XBOX360_Controller::XBOX360_Controller(uint32_t port) :
		Joystick(port,8,10)
{
	m_Port = port;


	Assign_Move_SideToSide(XBOX360_LEFT_X);
	Assign_Move_FrontToBack(XBOX360_LEFT_Y);
	Assign_Yaw(XBOX360_RIGHT_X);

	LSxDZ = 0.05;
	LSyDZ = 0.05;
	RSxDZ = 0.05;
	RSyDZ = 0.05;
	LtrigDZ = 0.05;
	RtrigDZ = 0.05;
	axisDelay = 10;
	flipRSy = true;
	flipLSy = true;
	flipRSx = false;
	flipLSx = false;
}

XBOX360_Controller::~XBOX360_Controller()
{

}

void XBOX360_Controller::Set_DeadZones(float lxmin, float lymin, float rxmin, float rymin, float ltriggermin, float rtriggermin)
{
	LSxDZ = lxmin;
	LSyDZ = lymin;
	RSxDZ = rxmin;
	RSyDZ = rymin;
	LtrigDZ = ltriggermin;
	RtrigDZ = rtriggermin;
}

void XBOX360_Controller::Rumble_Left(float intensity)
{
	SetRumble(kLeftRumble, intensity);
}

void XBOX360_Controller::Rumble_Right(float intensity)
{
	SetRumble(kRightRumble, intensity);
}

void XBOX360_Controller::Assign_Move_FrontToBack(XBOX360_AXIS axis)
{
	SetAxisChannel(kYAxis,axis);
}

void XBOX360_Controller::Assign_Move_SideToSide(XBOX360_AXIS axis)
{
	SetAxisChannel(kXAxis,axis);
}

void XBOX360_Controller::Assign_Yaw(XBOX360_AXIS axis)
{
	SetAxisChannel(kTwistAxis,axis);
}

XBOX_AxisState XBOX360_Controller::Get_AxisState()
{
	XBOX_AxisState retval;

	if (flipRSx)
	{
		retval.Raw_RX = 0 - (((GetRawAxis(XBOX360_RIGHT_X)*GetRawAxis(XBOX360_RIGHT_X)) > RSxDZ ) ? GetRawAxis(XBOX360_RIGHT_X) : 0.0);
	} else
	{
		retval.Raw_RX = ((GetRawAxis(XBOX360_RIGHT_X)*GetRawAxis(XBOX360_RIGHT_X)) > RSxDZ ) ? GetRawAxis(XBOX360_RIGHT_X) : 0.0;
	}


	if (flipRSy)
	{
		retval.Raw_RY = 0 - (((GetRawAxis(XBOX360_RIGHT_Y)*GetRawAxis(XBOX360_RIGHT_Y))> RSyDZ) ? GetRawAxis(XBOX360_RIGHT_Y) : 0.0);
	} else
	{
		retval.Raw_RY = ((GetRawAxis(XBOX360_RIGHT_Y)*GetRawAxis(XBOX360_RIGHT_Y))> RSyDZ) ? GetRawAxis(XBOX360_RIGHT_Y) : 0.0;
	}

	if (flipLSx)
	{
		retval.Raw_LX = 0 - (((GetRawAxis(XBOX360_LEFT_X)*GetRawAxis(XBOX360_LEFT_X)) > LSxDZ ) ? GetRawAxis(XBOX360_LEFT_X) : 0.0);
	} else
	{
		retval.Raw_LX = ((GetRawAxis(XBOX360_LEFT_X)*GetRawAxis(XBOX360_LEFT_X)) > LSxDZ ) ? GetRawAxis(XBOX360_LEFT_X) : 0.0;
	}

	if (flipLSy)
	{
		retval.Raw_LY = 0 - (((GetRawAxis(XBOX360_LEFT_Y)*GetRawAxis(XBOX360_LEFT_Y)) > LSyDZ ) ? GetRawAxis(XBOX360_LEFT_Y) : 0.0);
	} else
	{
		retval.Raw_LY = ((GetRawAxis(XBOX360_LEFT_Y)*GetRawAxis(XBOX360_LEFT_Y)) > LSyDZ ) ? GetRawAxis(XBOX360_LEFT_Y) : 0.0;
	}

	retval.RTrigger = (GetRawAxis(XBOX360_RTRIGGER) > RtrigDZ) ? GetRawAxis(XBOX360_RTRIGGER) : 0.0;
	retval.LTrigger = (GetRawAxis(XBOX360_LTRIGGER) > LtrigDZ) ? GetRawAxis(XBOX360_LTRIGGER) : 0.0;
	retval.DPAD = GetPOV();
	retval.Magnitude = GetMagnitude();
	retval.RelativeHeading = GetDirectionDegrees();
	retval.AxisDelay = axisDelay;
	return retval;
}

XBOX_ButtonState XBOX360_Controller::Get_ButtonState()
{
	XBOX_ButtonState retval;
	retval.A = GetRawButton(XBOX360_A);
	retval.B = GetRawButton(XBOX360_B);
	retval.X = GetRawButton(XBOX360_X);
	retval.Y = GetRawButton(XBOX360_Y);
	retval.LeftBumper = GetRawButton(XBOX360_LEFT_BUMPER);
	retval.RightBumper = GetRawButton(XBOX360_RIGHT_BUMPER);
	retval.Back = GetRawButton(XBOX360_BACK);
	retval.Start = GetRawButton(XBOX360_START);
	retval.LeftStick = GetRawButton(XBOX360_LEFT_STICK);
	retval.RightStick = GetRawButton(XBOX360_RIGHT_STICK);
	return retval;
}

int XBOX360_Controller::Get_AxisDelay()
{
	return axisDelay;
}

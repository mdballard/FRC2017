// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef OI_H
#define OI_H

#include "WPILib.h"
#include "Xbox360_Controller.h"

class OI {
private:
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	std::shared_ptr<XBOX360_Controller> xboxOperator;
	std::shared_ptr<JoystickButton> abort_Climb;
	std::shared_ptr<JoystickButton> startClimb;
	std::shared_ptr<JoystickButton> extendGear;
	std::shared_ptr<XBOX360_Controller> xboxDriver;
	std::shared_ptr<JoystickButton> switchCamera;
	std::shared_ptr<JoystickButton> reverseIntake;
	std::shared_ptr<JoystickButton> forwardIntake;
	std::shared_ptr<JoystickButton> shift;
	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
public:
	OI();

	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=PROTOTYPES

	std::shared_ptr<XBOX360_Controller> getXboxDriver();
	std::shared_ptr<XBOX360_Controller> getXboxOperator();
	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=PROTOTYPES
};

#endif
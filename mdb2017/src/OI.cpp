// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "OI.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "SmartDashboard/SmartDashboard.h"
#include "Commands/AbortCLimb.h"
#include "Commands/ActivateShooter.h"
#include "Commands/AutonomousCommand.h"
#include "Commands/Climb.h"
#include "Commands/DetectFire.h"
#include "Commands/Forward_Intake.h"
#include "Commands/IdleShooter.h"
#include "Commands/Reverse_Intake.h"
#include "Commands/ShiftHigh.h"
#include "Commands/ShiftLow.h"
#include "Commands/Switch_Camera.h"
#include "Commands/TeleopDrive.h"
#include "Commands/ToggleGearExtender.h"
#include "Commands/ToggleShift.h"
#include "Commands/UpdateFwdUS.h"
#include "Commands/UpdateGearPixy.h"
#include "Commands/UpdatePerimUS.h"
#include "Commands/UpdateShooterPixy.h"

// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "Commands/DecreaseBrightness.h"
#include "Commands/DecreaseExposure.h"
#include "Commands/DecreaseWhiteBalance.h"
#include "Commands/IncreaseBrightness.h"
#include "Commands/IncreaseExposure.h"
#include "Commands/IncreaseWhiteBalance.h"
#include "Commands/SelectStream.h"
#include "Commands/SetFPS.h"
#include "Commands/SetSize.h"
#include "Commands/StartStreaming.h"
#include "Commands/StopStreaming.h"
#include "Commands/AutoExposure.h"
#include "Commands/AutoWhiteBalance.h"


OI::OI() {
    // Process operator interface input here.
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    xboxOperator.reset(new XBOX360_Controller(1));
    
    abort_Climb.reset(new JoystickButton(xboxOperator.get(), 7));
    abort_Climb->WhenPressed(new AbortCLimb());
    startClimb.reset(new JoystickButton(xboxOperator.get(), 4));
    startClimb->WhenPressed(new Climb());
    extendGear.reset(new JoystickButton(xboxOperator.get(), 3));
    extendGear->WhenPressed(new ToggleGearExtender());
    xboxDriver.reset(new XBOX360_Controller(0));
    
    switchCamera.reset(new JoystickButton(xboxDriver.get(), 1));
    switchCamera->WhenPressed(new Switch_Camera());
    reverseIntake.reset(new JoystickButton(xboxDriver.get(), 5));
    reverseIntake->WhileHeld(new Reverse_Intake());
    forwardIntake.reset(new JoystickButton(xboxDriver.get(), 6));
    forwardIntake->WhenPressed(new Forward_Intake());
    shift.reset(new JoystickButton(xboxDriver.get(), 2));
    shift->WhenPressed(new ToggleShift());

    // SmartDashboard Buttons
    SmartDashboard::PutData("AbortCLimb", new AbortCLimb());
    SmartDashboard::PutData("IdleShooter", new IdleShooter());
    SmartDashboard::PutData("ActivateShooter", new ActivateShooter());
    SmartDashboard::PutData("Climb", new Climb());
    SmartDashboard::PutData("UpdatePerimUS", new UpdatePerimUS());
    SmartDashboard::PutData("UpdateFwdUS", new UpdateFwdUS());
    SmartDashboard::PutData("UpdateGearPixy", new UpdateGearPixy());
    SmartDashboard::PutData("UpdateShooterPixy", new UpdateShooterPixy());
    SmartDashboard::PutData("TeleopDrive", new TeleopDrive());
    SmartDashboard::PutData("ToggleGearExtender", new ToggleGearExtender());
    SmartDashboard::PutData("Switch_Camera", new Switch_Camera());
    SmartDashboard::PutData("Reverse_Intake", new Reverse_Intake());
    SmartDashboard::PutData("Forward_Intake", new Forward_Intake());
    SmartDashboard::PutData("ShiftLow", new ShiftLow());
    SmartDashboard::PutData("ShiftHigh", new ShiftHigh());
    SmartDashboard::PutData("ToggleShift", new ToggleShift());
    SmartDashboard::PutData("Autonomous Command", new AutonomousCommand());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    SmartDashboard::PutData("StopStreaming", new StopStreaming());
    SmartDashboard::PutData("StartStreaming", new StartStreaming());
    SmartDashboard::PutData("SetSize: Size640X480", new SetSize(0));
    SmartDashboard::PutData("SetSize: Size320X240", new SetSize(1));
    SmartDashboard::PutData("SetSize: Size160X120", new SetSize(2));
    SmartDashboard::PutData("DecreaseBrightness Cam1", new DecreaseBrightness(1));
    SmartDashboard::PutData("IncreaseBrightness Cam1", new IncreaseBrightness(1));
    SmartDashboard::PutData("DecreaseWhiteBalance Cam1", new DecreaseWhiteBalance(1));
    SmartDashboard::PutData("IncreaseWhiteBalance Cam1", new IncreaseWhiteBalance(1));
    SmartDashboard::PutData("DecreaseExposure Cam1", new DecreaseExposure(1));
    SmartDashboard::PutData("IncreaseExposure Cam1", new IncreaseExposure(1));
    SmartDashboard::PutData("DecreaseBrightness Cam2", new DecreaseBrightness(2));
    SmartDashboard::PutData("IncreaseBrightness Cam2", new IncreaseBrightness(2));
    SmartDashboard::PutData("DecreaseWhiteBalance Cam2", new DecreaseWhiteBalance(2));
    SmartDashboard::PutData("IncreaseWhiteBalance Cam2", new IncreaseWhiteBalance(2));
    SmartDashboard::PutData("DecreaseExposure Cam2", new DecreaseExposure(2));
    SmartDashboard::PutData("IncreaseExposure Cam2", new IncreaseExposure(2));
    SmartDashboard::PutData("AutoWhiteBalance Cam1", new AutoWhiteBalance(1));
    SmartDashboard::PutData("AutoExposure Cam1", new AutoExposure(1));
    SmartDashboard::PutData("AutoWhiteBalance Cam2", new AutoWhiteBalance(2));
    SmartDashboard::PutData("AutoExposure Cam2", new AutoExposure(2));
    SmartDashboard::PutData("SetFPS Cam1: Low10", new SetFPS(10,1));
    SmartDashboard::PutData("SetFPS Cam1: Med20", new SetFPS(20,1));
    SmartDashboard::PutData("SetFPS Cam1: High30", new SetFPS(30,1));
    SmartDashboard::PutData("SetFPS Cam2: Low10", new SetFPS(10,2));
    SmartDashboard::PutData("SetFPS Cam2: Med20", new SetFPS(20,2));
    SmartDashboard::PutData("SetFPS Cam2: High30", new SetFPS(30,2));
    SmartDashboard::PutData("SelectStream: Camera1", new SelectStream(1));
    SmartDashboard::PutData("SelectStream: Camera2", new SelectStream(2));

}

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS

std::shared_ptr<XBOX360_Controller> OI::getXboxDriver() {
   return xboxDriver;
}

std::shared_ptr<XBOX360_Controller> OI::getXboxOperator() {
   return xboxOperator;
}

// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS

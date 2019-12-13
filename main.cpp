/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// fLDrive              motor         1               
// bLDrive              motor         11              
// fRDrive              motor         10              
// bRDrive              motor         20              
// lLift                motor         2               
// rLift                motor         9               
// claw                 motor         3               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "functions.h"
using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
redTower();
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
    bool clawHold;
    bool isSlow = false;
   void setHoldTrue(){
   clawHold = true;
   }
   void setHoldFalse(){
      clawHold= false;
   }   
   void setSlowTrue(){
   isSlow = true;
   }
   void setSlowFalse(){
      isSlow = false;
   }
void usercontrol(void) {
  // User control code here, inside the loop
  while (true) {
    float holdVal;
    if(isSlow) holdVal = .3;
    else holdVal = 1;
   bLDrive.spin(vex::directionType::fwd, Controller1.Axis3.value()*holdVal,vex::velocityUnits::pct);
   fLDrive.spin(vex::directionType::fwd, Controller1.Axis3.value()*holdVal,vex::velocityUnits::pct);
   bRDrive.spin(vex::directionType::fwd, Controller1.Axis2.value()*holdVal,vex::velocityUnits::pct);
   fRDrive.spin(vex::directionType::fwd, Controller1.Axis2.value()*holdVal,vex::velocityUnits::pct);
  
  //DriveSpeedChange
    Controller1.ButtonA.pressed(setSlowTrue);
    Controller1.ButtonB.pressed(setSlowFalse);

  //Lift Up
    if (Controller1.ButtonR1.pressing()) {
     rLift.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
     lLift.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
   }
   // Down
   else if (Controller1.ButtonR2.pressing()) {
     rLift.spin(vex::directionType::rev, 50, vex::velocityUnits::pct);
     lLift.spin(vex::directionType::rev, 50, vex::velocityUnits::pct);
   }
   // Hold
   else {
     rLift.stop(hold);
     lLift.stop(hold);
   }

     if (Controller1.ButtonL1.pressing()) {
     claw.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
   }
   // Open
   else if (Controller1.ButtonL2.pressing()) {
     claw.spin(vex::directionType::rev, 50, vex::velocityUnits::pct);
   }
   else{
    Controller1.ButtonL1.pressed(setHoldTrue);
    Controller1.ButtonL2.pressed(setHoldFalse);
    if (clawHold)claw.spin(vex::directionType::fwd, 20, vex::velocityUnits::pct);
    else claw.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);
   }
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.

  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}

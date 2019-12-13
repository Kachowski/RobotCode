#include "vex.h"
void aDrive(float inches, int speed){
  float downScale = .32;
  float inchesPerDegree = 4;
  float degrees = inches*downScale/inchesPerDegree;
  fLDrive.startRotateFor(degrees*360,vex::rotationUnits::deg,speed,vex::velocityUnits::pct);
  fRDrive.startRotateFor(degrees*360,vex::rotationUnits::deg,speed,vex::velocityUnits::pct);
  bLDrive.startRotateFor(degrees*360,vex::rotationUnits::deg,speed,vex::velocityUnits::pct);
  bRDrive.startRotateFor(degrees*360,vex::rotationUnits::deg,speed,vex::velocityUnits::pct);
}
void aTurn(float degrees, int aDirection, int speed){//1 = right, 0 = left
   float downScale = .0333;
  float inchesPerDegree = 4;
   degrees = degrees*downScale/inchesPerDegree;
  if(aDirection == 1){
  fLDrive.startRotateFor(degrees*360,vex::rotationUnits::deg,speed,vex::velocityUnits::pct);
  fRDrive.startRotateFor(-degrees*360,vex::rotationUnits::deg,speed,vex::velocityUnits::pct);
  bLDrive.startRotateFor(degrees*360,vex::rotationUnits::deg,speed,vex::velocityUnits::pct);
  bRDrive.startRotateFor(-degrees*360,vex::rotationUnits::deg,speed,vex::velocityUnits::pct);
  }
  else{
  fLDrive.startRotateFor(-degrees*360,vex::rotationUnits::deg,speed,vex::velocityUnits::pct);
  fRDrive.startRotateFor(degrees*360,vex::rotationUnits::deg,speed,vex::velocityUnits::pct);
  bLDrive.startRotateFor(-degrees*360,vex::rotationUnits::deg,speed,vex::velocityUnits::pct);
  bRDrive.startRotateFor(degrees*360,vex::rotationUnits::deg,speed,vex::velocityUnits::pct);
  }
  
}
void oneSideTurn(float degrees, int aDirection, int speed){//use either positive or neg degrees to change direction
   float downScale = .0733;
  float inchesPerDegree = 4;
   degrees = degrees*downScale/inchesPerDegree;
  if(aDirection == 1){
  fRDrive.startRotateFor(degrees*360,vex::rotationUnits::deg,speed,vex::velocityUnits::pct);
  bRDrive.startRotateFor(degrees*360,vex::rotationUnits::deg,speed,vex::velocityUnits::pct);
  }
  else{
  fLDrive.startRotateFor(degrees*360,vex::rotationUnits::deg,speed,vex::velocityUnits::pct);
  bLDrive.startRotateFor(degrees*360,vex::rotationUnits::deg,speed,vex::velocityUnits::pct);
  }
}
void upLift(float inches, int speed){
  rLift.startRotateFor(inches*360/23,vex::rotationUnits::deg,speed,vex::velocityUnits::pct);
  lLift.startRotateFor(inches*360/23,vex::rotationUnits::deg,speed,vex::velocityUnits::pct);
}
void downLift(float inches, int speed){
  rLift.startRotateFor(-inches*360/23,vex::rotationUnits::deg,speed,vex::velocityUnits::pct);
  lLift.startRotateFor(-inches*360/23,vex::rotationUnits::deg,speed,vex::velocityUnits::pct);
}
void aLiftHold(){
  lLift.setStopping(hold);
  rLift.setStopping(hold);
}
void clawOpen(){
  claw.startRotateFor(-80,vex::rotationUnits::deg,50,vex::velocityUnits::pct);
}
void aClawHold(){
  claw.setStopping(hold);
}
void clawClose(){
   claw.startRotateFor(50,vex::rotationUnits::deg,30,vex::velocityUnits::pct);
}
void deploy(){
  claw.startRotateFor(270,vex::rotationUnits::deg,50,vex::velocityUnits::pct);
}
void resetAll(){
}
void closeScreen(){
  Controller1.Screen.clearScreen(); 
}
void controllerTemp(){
  double hot = 100.0;
  if(fLDrive.temperature() > hot || bRDrive.temperature() > hot || fLDrive.temperature() > hot || fRDrive.temperature() > hot){

  }
}
/*void controllerTemp(){
  bool fLDriveB = false;
  bool bLDriveB = false;
  bool fRDriveB = false;
  bool bRDriveB = false;
  bool lLiftB = false;
  bool rLiftB = false;
  bool clawB = false;
  int hotCount = 0;
  motor motorArray[] = {fLDrive, bLDrive, fRDrive, bRDrive, lLift, rLift, claw};
  bool boolMotorArray[] = {fLDriveB, bLDriveB, fRDriveB, bRDriveB, lLiftB, rLiftB, clawB};
  std::string stringArray[] = {"Front Left Drive", "Back Left Drive", "Front Right Drive", "Back Right Drive", "Left Lift", "Right Lift", "Claw"};
  for(int i = 0; i < 6; i++){
    if(motorArray[i].temperature() > 50.0){
      boolMotorArray[i] = true;
      hotCount++;
    }
  }
  if(hotCount > 0){
    Controller1.rumble(rumblePulse);
    Controller1.Screen.print("Motors Are Over Heating");
    Controller1.Screen.newLine();
    Controller1.Screen.print("Motors:");
  }
  for(int i = 0; i < 6; i++){
    if(boolMotorArray[i] == true){
      Controller1.Screen.print(i+1);
      Controller1.Screen.print(" ");
    }
  } 
  Controller1.ButtonX.pressed(closeScreen);
}
*/

void pushAuton(){
  aDrive(8,30);
  vex::task::sleep(2000);
  aDrive(-12,50);
}
void redTower(){
  aDrive(10,30);
  vex::task::sleep(1000);
  aDrive(-10,30);
  vex::task::sleep(1000);
  aTurn(172,1,50);
  vex::task::sleep(1000);
  deploy();
  vex::task::sleep(1000);
  aDrive(30,30);
  vex::task::sleep(3000);
  clawClose();
  vex::task::sleep(500);
  aClawHold();
  aDrive(-10,30);
  vex::task::sleep(1000);
  aTurn(15,1,30);
  vex::task::sleep(500);
  upLift(1,70);
}

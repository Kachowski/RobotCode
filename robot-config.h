using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor fLDrive;
extern motor bLDrive;
extern motor fRDrive;
extern motor bRDrive;
extern motor lLift;
extern motor rLift;
extern motor claw;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );
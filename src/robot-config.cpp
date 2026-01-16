#include "vex.h"

using namespace vex;

brain Brain;

//Drivetrain Motors
controller Controller = controller(primary);
motor FrontLeft = motor(PORT1, ratio18_1, true);
motor MiddleLeft = motor(PORT2, ratio18_1, true);
motor BackLeft = motor(PORT3, ratio18_1, true);
motor FrontRight = motor(PORT4, ratio18_1, false);
motor MiddleRight = motor(PORT12, ratio18_1, false);
motor BackRight = motor(PORT6, ratio18_1, false);

//Intake Motors
motor BackIntake = motor(PORT8, ratio6_1, false);
motor FrontIntake  = motor(PORT9, ratio18_1, false);
motor LoneIntake = motor(PORT10, ratio18_1, true);

//Drivetrain Motor Groups
motor_group LeftSide = motor_group(FrontLeft, MiddleLeft, BackLeft);
motor_group RightSide = motor_group(FrontRight, MiddleRight, BackRight);

//Pneumatics
digital_out MatchLoader = digital_out(Brain.ThreeWirePort.A);
digital_out Descore = digital_out(Brain.ThreeWirePort.H);

//Inertial Sensor
inertial imu = inertial(PORT20);
inertial imu2 = inertial(PORT19);
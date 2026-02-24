/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       100193                                                    */
/*    Created:      10/28/2025, 4:03:29 PM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "robot-config.h"
#include <cmath>
#include <iostream>

//using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

double previous_inertial = 0;
double previous_tracking = 0;


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

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  MatchLoader.set(false);
  Descore.set(false);
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

/*
void getPositon() {

  while() {
  }
  
  LeftSide.getPosition();
  RightSide.getPosition();
}
*/

double wrapAngle(double angleDeg) {
  if (angleDeg > 180) {
    return angleDeg - 360;
  }
  return angleDeg;
}

void turn(double deg, bool clockwise){
 
  // RESET THE INERTIAL SENSOR TO ZERO
  imu.setRotation(0, degrees);

  // NEXT Get the current inertial value in degrees
  double value = wrapAngle(imu.rotation(vex::rotationUnits::deg));
  
  // NOW GO INTO A LOOP.
  LeftSide.setVelocity(35, pct);
  RightSide.setVelocity(35, pct);


  while (true) {

    if (clockwise) {
      LeftSide.spin(fwd);
      RightSide.spin(reverse);

      // check the value of the inertial againsted the target degrees
      if (value >= deg) {// BREAK LOOP when the inertial value reaches the target value
        break;
      }
    } else {
      LeftSide.spin(reverse);
      RightSide.spin(fwd);
   

      if (value <= -deg) {// BREAK LOOP when the inertial value reaches the target value
        break;
      }
    }
    value = wrapAngle(imu.rotation(vex::rotationUnits::deg)); //update value
    wait(20, msec); // small delay to prevent wasted resources

    // DEBUG:
    Brain.Screen.clearLine();
    Brain.Screen.print("Inertial: %.2f", value);
   }

   LeftSide.stop();
   RightSide.stop();

}

void drive_forward(double inches, double speed, double direction = 1) {
  double wheelCircumference = 3.25 * M_PI; // wheel diameter in inches
  double rotations = (inches*0.6153) / wheelCircumference; // calculate the number of wheel rotations needed
  double degreesToRotate = rotations * 360; // convert rotations to degrees

  LeftSide.setVelocity(speed, pct);
  RightSide.setVelocity(speed, pct);
  if (direction == 1) {
    LeftSide.spinFor(fwd, degreesToRotate, degrees, false);
    RightSide.spinFor(fwd, degreesToRotate, degrees, true);
  } else {
    LeftSide.spinFor(reverse, degreesToRotate, degrees, false);
    RightSide.spinFor(reverse, degreesToRotate, degrees, true);
  }
}



void autonomous(void) {

//Left Side (SLOT 1)
  // imu.calibrate();
  // wait(2, sec); // give time to calibrate

  
  // drive_forward(20, 50, 1); // Move forward 20 inches at 50% speed
  // turn(70, false);
  // drive_forward(32, 50, 1);
  // turn(70, true);
  // drive_forward(10, 50, 1);

  // BackIntake.spin(fwd, 100, percent);
  // FrontIntake.spin(fwd, 100, percent);
  // LoneIntake.spin(fwd, 100, percent);
  // wait(1, sec);
  // BackIntake.stop(brake);
  // FrontIntake.stop(brake);
  // LoneIntake.stop(brake);

  // drive_forward(5, 50, -1); // Move backward 5 inches at 50% speed
  // turn(70, true);
  // drive_forward(13, 50, 1);
  // turn(70, false);
  // drive_forward(30, 50, 1);
  // Descore.set(true);


//Right Side (SLOT 2)

  imu.calibrate();
  wait(2, sec); // give time to calibrate

  drive_forward(20, 50, 1); // Move forward 20 inches at 50% speed
  turn(70, true);
  drive_forward(32, 50, 1);
  turn(70, false);
  drive_forward(10, 50, 1);

  BackIntake.spin(fwd, 100, percent);
  FrontIntake.spin(fwd, 100, percent);
  LoneIntake.spin(fwd, 100, percent);
  wait(1, sec);
  BackIntake.stop(brake);
  FrontIntake.stop(brake);
  LoneIntake.stop(brake);

  drive_forward(5, 50, -1); // Move backward 5 inches at 50% speed
  turn(70, true);
  drive_forward(12, 50, 1);
  turn(70, false);
  drive_forward(29, 50, 1);
  Descore.set(true);



//Skills (SLOT 3)

//NOTE: 70 degrees = ~90 degrees turn, 15 degrees = ~45 degrees turn

// BackIntake.spin(reverse, 100, percent);
// FrontIntake.spin(fwd, 100, percent);
// drive_forward(18, 100, 1); // Move forward 20 inches at 50% speed
// BackIntake.stop(brake);
// FrontIntake.stop(brake);




/*
imu.calibrate();
wait(2, sec); // give time to calibrate

//move to loader
drive_forward(47, 50, 1); // Move forward 40 inches at 50% speed
wait(0.5, sec);
turn(28, false);
//load blocks
MatchLoader.set(true);
wait(1, sec);
BackIntake.spin(reverse, 100, percent); 
FrontIntake.spin(fwd, 100, percent);
drive_forward(15, 30, 1);
wait(5, sec);
BackIntake.stop(brake);
FrontIntake.stop(brake);
//move to park zone
drive_forward(15, 50, -1);
MatchLoader.set(false);
wait(0.5, sec);
turn (70, false);
drive_forward(48.5, 50, 1);
wait(0.5, sec);
turn(70, true);
wait(0.5, sec);
*/

/*
turn(160, true);
drive_forward(16, 50, 1);
  BackIntake.spin(fwd, 100, percent);
  FrontIntake.spin(fwd, 100, percent);
  LoneIntake.spin(fwd, 100, percent);
  wait(10, sec);
  BackIntake.stop(brake);
  FrontIntake.stop(brake);
  LoneIntake.stop(brake);
//go and descore
drive_forward(10, 50, -1);
wait (0.5, sec);
turn(70, true);
drive_forward(11, 50, 1);
wait(0.5, sec);
turn(70, false);
drive_forward(15, 50, 1);
*/
//go to park zone 
/*
drive_forward(35, 50, -1);
wait(0.5, sec);
turn(80, true);
*/
drive_forward(20, 100, 1);


/*
drive_forward(1, 50, -1); // Move forward 20 inches at 50% speed
drive_forward(20, 100, 1); // Move forward 20 inches at 50% speed


  drive_forward(20, 50, 1); // Move forward 20 inches at 50% speed
  turn(70, false);
  drive_forward(32, 50, 1);
  turn(70, true);
  drive_forward(8, 50, 1);

  BackIntake.spin(fwd, 75, percent);
  FrontIntake.spin(fwd, 75, percent);
  LoneIntake.spin(fwd, 75, percent);
  wait(2, sec);
  BackIntake.stop(brake);
  FrontIntake.stop(brake);
  LoneIntake.stop(brake);

drive_forward(5, 50, -1); // Move backward 5 inches at 50% speed
wait (0.5, sec);
turn(70, true);
drive_forward(43, 50, 1);
wait (0.5, sec);
turn(70, true);
drive_forward(11.5, 50, -1);
drive_forward(55, 100, 1);
*/

//first loader
/*
drive_forward(25, 75, 1);
wait(0.5, sec);
turn(70, false);
drive_forward(35, 75, 1);
wait(0.5, sec);
turn(80, false);

MatchLoader.set(true);
wait(0.5, sec);
BackIntake.spin(reverse, 100, percent); 
FrontIntake.spin(fwd, 100, percent);

drive_forward(25, 75, 1);
wait (3, sec); 
*/
// drive_forward(25, 50, 1); 
// wait (0.5, sec);
// drive_forward(7, 50, -1);
// drive_forward(14, 50, 1);
// wait (0.5, sec);
// drive_forward(7, 50, -1);
// drive_forward(15, 50, 1);
// wait (0.5, sec);
// drive_forward(7, 50, -1);
/*
BackIntake.stop(brake);
FrontIntake.stop(brake);
drive_forward(10, 75, -1);
MatchLoader.set(false);
wait(0.5, sec);
turn(70, true);
drive_forward(10, 75, 1);
wait(0.5, sec);
turn(70, true);
drive_forward(25, 75, 1);
wait(0.5, sec);
turn(70, false);
drive_forward(30, 100, 1);
*/
/*
//to long goal
turn(140, false);
drive_forward(15, 75, 1);

BackIntake.spin(fwd, 100, percent);
FrontIntake.spin(fwd, 100, percent);
LoneIntake.spin(fwd, 100, percent);
wait(3, sec);
BackIntake.stop(brake);
FrontIntake.stop(brake);
LoneIntake.stop(brake);

//second loader
drive_forward(5, 50, -1);
turn(70, true);
drive_forward(60, 50, 1);
turn(70, true);

MatchLoader.set(true);
BackIntake.spin(reverse, 100, percent);
FrontIntake.spin(fwd, 100, percent);
drive_forward(25, 50, 1);
wait (0.5, sec);
drive_forward(7, 50, -1);
drive_forward(13, 50, 1);
wait (0.5, sec);
drive_forward(7, 50, -1);
drive_forward(14, 50, 1);
wait (0.5, sec);
drive_forward(7, 50, -1);

BackIntake.stop(brake);
FrontIntake.stop(brake);
drive_forward(10, 75, -1);
MatchLoader.set(false);

//to other long goal
turn(140, false);
drive_forward(15, 75, 1);

BackIntake.spin(fwd, 100, percent);
FrontIntake.spin(fwd, 100, percent);
LoneIntake.spin(fwd, 100, percent);
wait(3, sec);
BackIntake.stop(brake);
FrontIntake.stop(brake);
LoneIntake.stop(brake);

//third loader
drive_forward(5, 50, -1);
turn(70, true);
drive_forward(10, 50, 1);
turn(70, false);
drive_forward(60, 50, 1);
turn(70, false);
drive_forward(10, 50, 1);
turn(70, true);

MatchLoader.set(true);
BackIntake.spin(reverse, 100, percent);
FrontIntake.spin(fwd, 100, percent);
drive_forward(25, 50, 1);
wait (0.5, sec);
drive_forward(7, 50, -1);
drive_forward(13, 50, 1);
wait (0.5, sec);
drive_forward(7, 50, -1);
drive_forward(14, 50, 1);
wait (0.5, sec);
drive_forward(7, 50, -1);

BackIntake.stop(brake);
FrontIntake.stop(brake);
drive_forward(10, 75, -1);
MatchLoader.set(false);

//same long goal
turn(140, false);
drive_forward(15, 75, 1);

BackIntake.spin(fwd, 100, percent);
FrontIntake.spin(fwd, 100, percent);
LoneIntake.spin(fwd, 100, percent);
wait(3, sec);
BackIntake.stop(brake);
FrontIntake.stop(brake);
LoneIntake.stop(brake);

//to fourth loader
drive_forward(5, 50, -1);
turn(70, true);
drive_forward(60, 50, 1);
turn(70, true);

MatchLoader.set(true);
BackIntake.spin(reverse, 100, percent);
FrontIntake.spin(fwd, 100, percent);
drive_forward(25, 50, 1);
wait (0.5, sec);
drive_forward(7, 50, -1);
drive_forward(13, 50, 1);
wait (0.5, sec);
drive_forward(7, 50, -1);
drive_forward(14, 50, 1);
wait (0.5, sec);
drive_forward(7, 50, -1);

BackIntake.stop(brake);
FrontIntake.stop(brake);
drive_forward(10, 75, -1);
MatchLoader.set(false);

//to long goal
turn(140, false);
drive_forward(15, 75, 1);

BackIntake.spin(fwd, 100, percent);
FrontIntake.spin(fwd, 100, percent);
LoneIntake.spin(fwd, 100, percent);
wait(3, sec);
BackIntake.stop(brake);
FrontIntake.stop(brake);
LoneIntake.stop(brake);

//going to clear park zone and park
drive_forward(5, 50, -1);
turn(70, false);
drive_forward(15, 50, 1);
turn(70, false);
drive_forward(20, 50, 1);
turn(70, true);
drive_forward(30, 100, 1);
turn(70, true);
drive_forward(25, 50, 1);
turn(70, true);
drive_forward(15, 50, 1);
turn(70, true);
drive_forward(15, 50, -1);
drive_forward(35, 100, 1);
*/

/*
BackIntake.spin(reverse, 100, percent);
FrontIntake.spin(fwd, 100, percent);

drive_forward(28, 50, 1);

BackIntake.stop(brake);
FrontIntake.stop(brake);

turn(70, true);
drive_forward(10, 50, 1);

BackIntake.spin(fwd, 50, percent);
FrontIntake.spin(fwd, 50, percent);
LoneIntake.spin(fwd, 50, percent);
wait(3, sec);
BackIntake.stop(brake);
FrontIntake.stop(brake);
LoneIntake.stop(brake);
*/
/*
//to loader and loading
turn(70, true);
drive_forward(25, 75, 1);
turn(15, false);
drive_forward(20, 75, 1);
turn(70, true);

MatchLoader.set(true);
BackIntake.spin(reverse, 100, percent);
FrontIntake.spin(fwd, 100, percent);
drive_forward(25, 75, 1);

drive_forward(3, 75, -1);
drive_forward(3, 75, 1);
drive_forward(3, 75, -1);
drive_forward(3, 75, 1);
drive_forward(3, 75, -1);
drive_forward(3, 75, 1);

BackIntake.stop(brake);
FrontIntake.stop(brake);

//to long goal
drive_forward(10, 75, -1);
turn(150, true);

drive_forward(20, 75, 1);
BackIntake.spin(fwd, 50, percent);
FrontIntake.spin(fwd, 50, percent);
LoneIntake.spin(fwd, 50, percent);
wait(3, sec);
BackIntake.stop(brake);
FrontIntake.stop(brake);
LoneIntake.stop(brake);
*/


/*
//to centre goal again
drive_forward(5, 75, -1);
turn(70, false);
drive_forward(5, 75, 1);
turn(15, true);

BackIntake.spin(reverse, 100, percent);
FrontIntake.spin(fwd, 100, percent);
drive_forward(25, 50, 1);
BackIntake.stop(brake);
FrontIntake.stop(brake);

BackIntake.spin(reverse, 50, percent);
FrontIntake.spin(reverse, 50, percent);
wait(3, sec);
BackIntake.stop(brake);
FrontIntake.stop(brake);

//to different loader and loading
drive_forward(5, 75, -1);
turn(70, false);
drive_forward(30, 75, 1);
turn(15, true);
drive_forward(5, 75, 1);
turn(70, false);

MatchLoader.set(true);
BackIntake.spin(reverse, 100, percent);
FrontIntake.spin(fwd, 100, percent);

drive_forward(10, 75, 1);
drive_forward(3, 75, -1);
drive_forward(3, 75, 1);
drive_forward(3, 75, -1);
drive_forward(3, 75, 1);
drive_forward(3, 75, -1);
drive_forward(3, 75, 1);

BackIntake.stop(brake);
FrontIntake.stop(brake);

//to other long goal
drive_forward(10, 75, -1);
turn(140, false);

drive_forward(20, 75, 1);
BackIntake.spin(fwd, 50, percent);
FrontIntake.spin(fwd, 50, percent);
LoneIntake.spin(fwd, 50, percent);
wait(3, sec);
BackIntake.stop(brake);
FrontIntake.stop(brake);
LoneIntake.stop(brake);
*/

  /*
  turn(90, true);  Turn 90 degrees clockwise
  wait(1, sec);  give time to calibrate
  turn(90, false);  Turn 90 degrees counterclockwise
  //wait(1, sec);
  //turn(90, false); // Turn 90 degrees counter-clockwise
  //Drive forward
*/

  /*
  LeftSide.spin(fwd, 100, pct);
  RightSide.spin(fwd, 100, pct);
  wait(0.5, sec);
  LeftSide.stop(brake);
  RightSide.stop(brake);
  */

  //No movement = 16 3/4"
  //Move forward (100% for 1 second) = Hits centre goal, ~63"
  //Move forward (100% for 0.5 seconds) = 

  //Turn to the right
  /*
  LeftSide.spin(fwd, 100, percent);
  RightSide.spin(reverse, 100, percent);
  wait(0.50, sec);
  LeftSide.stop(brake);
  RightSide.stop(brake);
  */
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
double value = 0;
void usercontrol(void) {
  while (1)
  {
    value = wrapAngle(imu.rotation(vex::rotationUnits::deg)); //update value

    Brain.Screen.clearLine();
    Brain.Screen.print("Inertial: %.2f", value);

    float throttle = Controller.Axis3.position(); //get user input from joystick

    if (throttle < 5 && throttle > -5)
    {
      throttle = 0;
    }
    float turn = Controller.Axis1.position();
    if (turn < 5 && turn > -5)
    {
      turn = 0;
    }
    // throttle /= 1.27;
    // turn /= 1.27;

    throttle = pow(throttle, 3) / pow(10, 4);
    turn = pow(turn, 3) / pow(10, 4);

    float leftpow;
    float rightpow;

    leftpow = throttle + turn;
    rightpow = throttle - turn;

    // double sum = (leftpow + rightpow) / 100;
    // if (sum > 1) {
    //   leftpow /= sum;
    //   rightpow /= sum;
    // }
    if (leftpow == 0)
    {
      LeftSide.stop(brake);
    }
    if (rightpow == 0)
    {
      RightSide.stop(brake);
    }

    std::cout << throttle << std::endl;
    std::cout << turn << std::endl;

    LeftSide.spin(fwd, (leftpow * 12) / 100, volt);
    RightSide.spin(fwd, (rightpow * 12) / 100, volt);

    //LeftSide.spin(fwd, 255, volt);
    //RightSide.spin(fwd, 255, volt);

    /*
    // Manual Intake control, turns the back motor
    if(Controller.ButtonL1.pressing())
    {
      BackIntake.spin(fwd, 75, percent);
    } 
    
    else if(Controller.ButtonL2.pressing())
    {
      BackIntake.spin(reverse, 75, percent);
    }
    else 
    { 
      BackIntake.stop(brake);
    }
    wait(20, msec);

    // Intake control, turns the front motor
      if(Controller.ButtonR1.pressing())
    {
      FrontIntake.spin(fwd, 75, percent);
    } 
     else if(Controller.ButtonR2.pressing())
    {
      FrontIntake.spin(reverse, 75, percent);
    }
    else 
    { 
      FrontIntake.stop(brake);
    }
    wait(20, msec);

    // Intake control, turns the lone motor
      if(Controller.ButtonUp.pressing())
    {
      LoneIntake.spin(fwd, 75, percent);
    } 
     else if(Controller.ButtonDown.pressing())
    {
      LoneIntake.spin(reverse, 75, percent);
    }
    else 
    { 
      LoneIntake.stop(brake);
    }
    wait(20, msec);
    */

    //Long Goal Intake Control
    if(Controller.ButtonR1.pressing())
    {
      BackIntake.spin(fwd, 100, percent);
      FrontIntake.spin(fwd, 100, percent);
      LoneIntake.spin(reverse, 100, percent);
    } 
   
    //Middle Goal Intake Control
     else if(Controller.ButtonR2.pressing())
    {
      BackIntake.spin(fwd, 100, percent);
      FrontIntake.spin(fwd, 100, percent);
      LoneIntake.spin(fwd, 100, percent);
    } 

    //Basket Intake Control
     else if(Controller.ButtonL1.pressing())
    {
    BackIntake.spin(reverse, 100, percent);
    FrontIntake.spin(fwd, 100, percent);
    LoneIntake.spin(fwd, 100, percent);
    } 
    
    //Low Goal Intake Control
     else if(Controller.ButtonL2.pressing())
    {
      BackIntake.spin(fwd, 100, percent);
      FrontIntake.spin(reverse, 100, percent);
      LoneIntake.spin(fwd, 100, percent);
    } 
    else 
    { 
      BackIntake.stop(brake);
      FrontIntake.stop(brake);
      LoneIntake.stop(brake);
    }
    wait(20, msec);

    //Match Loader Pneumatic Control
    if(Controller.ButtonB.pressing()) {
        MatchLoader.set(true);
    }
    else if(Controller.ButtonY.pressing()) {
        MatchLoader.set(false);
    }

    //Descore Pneumatic Control
     if(Controller.ButtonDown.pressing()) {
        Descore.set(true);
    }
    else if(Controller.ButtonRight.pressing()) {
        Descore.set(false);
    }
  }
}

int main() {
    // Set up callbacks.
    Competition.autonomous(autonomous);
    Competition.drivercontrol(usercontrol);

    // Prevent main from exiting with an infinite loop.
    while (true) {
        wait(100, msec);
     }
}


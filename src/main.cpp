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

//using namespace vex;

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

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  Solenoid.set(false);
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
*/

}

void autonomous(void) {
//Drive forward
LeftSide.spin(fwd, 100, pct);
RightSide.spin(fwd, 100, pct);
wait(0.5, sec);
LeftSide.stop(brake);
RightSide.stop(brake);

//No movement = 16 3/4"
//Move forward (100% for 1 second) = Hits centre goal, ~63"
//Move forward (100% for 0.5 seconds) = 

//Turn to the right
LeftSide.spin(fwd, 100, percent);
RightSide.spin(reverse, 100, percent);
wait(0.50, sec);
LeftSide.stop(brake);
RightSide.stop(brake);
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

void usercontrol(void) {
  while (1)
  {
    float throttle = Controller.Axis3.value(); //get user input from joystick

    if (throttle < 5 && throttle > -5)
    {
      throttle = 0;
    }
    throttle = throttle / 1.27;
    float turn = Controller.Axis1.value();
    if (turn < 5 && turn > -5)
    {
      turn = 0;
    }
    turn = turn / 1.27;
    throttle = pow(throttle, 3) / 10000;
    turn = pow(turn, 3) / 10000;

    float leftpow;
    float rightpow;

    leftpow = throttle + turn;
    rightpow = throttle - turn;

    if (leftpow == 0)
    {
      LeftSide.stop(brake);
    }
    if (rightpow == 0)
    {
      RightSide.stop(brake);
    }

    LeftSide.spin(fwd, (leftpow * 0.12), volt);
    RightSide.spin(fwd, (rightpow * 0.12), volt);
    
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
      BackIntake.spin(fwd, 75, percent);
      FrontIntake.spin(fwd, 75, percent);
      LoneIntake.spin(reverse, 75, percent);
    } 
   
    //Middle Goal Intake Control
     else if(Controller.ButtonR2.pressing())
    {
      BackIntake.spin(fwd, 75, percent);
      FrontIntake.spin(fwd, 75, percent);
      LoneIntake.spin(fwd, 75, percent);
    } 

    //Basket Intake Control
     else if(Controller.ButtonL1.pressing())
    {
      BackIntake.spin(reverse, 75, percent);
      FrontIntake.spin(fwd, 75, percent);
    } 
    
    //Low Goal Intake Control
     else if(Controller.ButtonL2.pressing())
    {
      BackIntake.spin(reverse, 75, percent);
      FrontIntake.spin(reverse, 75, percent);
      LoneIntake.spin(fwd, 75, percent);
    } 
    else 
    { 
      BackIntake.stop(brake);
      FrontIntake.stop(brake);
      LoneIntake.stop(brake);
    }
    wait(20, msec);

    //Pneumatic Control
    if(Controller.ButtonB.pressing()) {
        Solenoid.set(true);
    }
    else if(Controller.ButtonY.pressing()) {
        Solenoid.set(false);
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

//Inertial Sensor Setup

//Configuration
double wheelSize = 3.25; //Wheel diameter in inches
double wheelCircumference = wheelSize * std::numbers::pi; //Calculate wheel circumference

double offset = 0; //Distance from center of robot to tracking wheel in inches

double x_pos = 0; 
double y_pos = 0; 
double theta = 0;

double turn_to_radians(double turn_degrees) {
  return turn_degrees * (std::numbers::pi / 180.0);
}
double radians_to_turn(double radians) {
  return radians * (180.0 / std::numbers::pi);
}

void Setposition(double x, double y, double degrees) {
  x_pos = x;
  y_pos = y;
  theta = turn_to_radians(degrees);
}

double wrapAngle(double angleDeg) {
  if (angleDeg > 180) {
    return angleDeg - 360;
  }
  return angleDeg;
}

double previous_inertial = 0;
double previous_tracking = 0;


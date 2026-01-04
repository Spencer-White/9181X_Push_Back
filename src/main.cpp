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
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
  
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

     // Intake control, turns the front motor
      if(Controller.ButtonY.pressing())
    {
      LoneIntake.spin(fwd, 75, percent);
    } 
     else if(Controller.ButtonB.pressing())
    {
      LoneIntake.spin(reverse, 75, percent);
    }
    else { 
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
    /*
    else 
    { 
      BackIntake.stop(brake);
      FrontIntake.stop(brake);
      LoneIntake.stop(brake);
    }
    wait(20, msec);
    */

    //Middle Goal Intake Control
     else if(Controller.ButtonR2.pressing())
    {
      BackIntake.spin(fwd, 75, percent);
      FrontIntake.spin(fwd, 75, percent);
      LoneIntake.spin(fwd, 75, percent);
    } 
    /*
    else 
    { 
      BackIntake.stop(brake);
      FrontIntake.stop(brake);
      LoneIntake.stop(brake);
    }
    wait(20, msec);
    */

    //Basket Intake Control
     else if(Controller.ButtonL1.pressing())
    {
      BackIntake.spin(reverse, 75, percent);
      FrontIntake.spin(fwd, 75, percent);
    } 
    /*
    else 
    { 
      BackIntake.stop(brake);
      FrontIntake.stop(brake);
    }
    wait(20, msec);
    */

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
  }
}

 Solenoid.set(false);
 while(true) {
        if(Controller1.ButtonB.pressing()) {
            Solenoid.set(true);
            }
        else if(Controller1.ButtonY.pressing()) {
            Solenoid.set(false);
        }
              wait(20, msec); 
    }

/*
int main() {
    // Set up callbacks.
    Competition.autonomous(autonomous);
    Competition.drivercontrol(usercontrol);

    // Prevent main from exiting with an infinite loop.
    while (true) {
        wait(100, msec);
     }
}
*/
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



/*
  imu.calibrate();
  wait(2, sec); // give time to calibrate

  
  drive_forward(20, 50, 1); // Move forward 24 inches at 50% speed
  //wait(1, sec);
  turn(70, false);
  drive_forward(32, 50, 1);
  turn(70, true);
  drive_forward(8, 50, 1);

  BackIntake.spin(reverse, 75, percent);
  FrontIntake.spin(reverse, 75, percent);
  LoneIntake.spin(fwd, 75, percent);
  wait(2, sec);
  BackIntake.stop(brake);
  FrontIntake.stop(brake);
  LoneIntake.stop(brake);
*/


  imu.calibrate();
  wait(2, sec); // give time to calibrate

  drive_forward(20, 50, 1); // Move forward 24 inches at 50% speed
  //wait(1, sec);
  turn(70, true);
  drive_forward(32, 50, 1);
  turn(70, false);
  drive_forward(8, 50, 1);

  BackIntake.spin(reverse, 75, percent);
  FrontIntake.spin(reverse, 75, percent);
  LoneIntake.spin(fwd, 75, percent);
  wait(2, sec);
  BackIntake.stop(brake);
  FrontIntake.stop(brake);
  LoneIntake.stop(brake);

  


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

//Inertial Sensor Setup
/*
//Configuration
double wheelSize = 3.25; //Wheel diameter in inches
double wheelCircumference = wheelSize * M_PI; //Calculate wheel circumference

double offset = 0; //Distance from center of robot to tracking wheel in inches

double x_pos = 0; 
double y_pos = 0; 
double theta = 0;

double turn_to_radians(double turn_degrees) {
  return turn_degrees * (M_PI / 180.0); 
}
double radians_to_turn(double radians) {
  return radians * (180.0 / M_PI);
}

void Setposition(double x, double y, double degrees) {
  x_pos = x;
  y_pos = y;
  theta = turn_to_radians(degrees);
}



void updatePos() {


  //Gathers current values
  double heading_degrees = wrapAngle(imu.getheading());
  double tracking_degrees = LeftSide.getposition(); + RightSide.getposition() / 2.0;

  //Change in heading
  double delta_heading = heading_degrees - previous_inertial;
  double delta_tracking = tracking_degrees - previous_tracking;

  //Storing new tracking value for repeat
  previous_tracking = tracking_degrees;
  previous_inertial = heading_degrees;

  //Convert to linear distance
  double delta_distance = (delta_tracking/360) * wheelCircumference;

  //Update position
  x_pos += delta_distance * std::cos(turn_to_radians(heading_degrees));
  y_pos += delta_distance * std::sin(turn_to_radians(heading_degrees));
  theta = turn_to_radians(heading_degrees);

  //Print position on the brain screen
  print(2, "X_Position: %.2f inches", x_pos);
  print(3, "Y_Position: %.2f inches", y_pos);
  print(4, "Heading: %.2f degrees", radians_to_turn(theta));
}



void resetOdometry() {

  //Calibrate the IMU (only id not already calibrated)
  imu.reset();
  wait(200, msec); //Minimal time to begin calibration

  //Wait until the IMU finishes calibrating (can take 1-2 seconds)
  while (imu.is_calibrating()) {
    wait(10, msec);
  }
  //Zero the rotation sensor (tracking wheel)
  verticalEnc.reset_position();

  //Reset global odometry positions
  x_pos = 0.0;
  y_pos = 0.0;
  theta = turn_to_radians(degrees:0.0);

  //Store the inertial sensor readings for next update
  previous_inertial = wrapAngle(imu.get_heading()); //IMU heading
  previous_tracking = verticalEnc.get_position(); //Rotation sensor degrees

}

void resetOdometryAuto () {

  //Only reset tracking wheel here
  vertical_Enc.reset_position();

  //Reset global pose
  x_pos = 0.0;
  y_pos = 0.0;

  //Set previous sensor logs
  previous_inertial = wrapAngle(imu.get_heading());
  previous_tracking = verticalEnc.get_position();
}

void odom_task_fn(void*) {
  while (true) {
    updatePos();
    wait(10, msec); //Time between position updates
  }
}
*/

void initialize() {
 // pros::lcd::initialize();
  //imu.isCalibrating();
  //Task odom_task(odom_task_fn, parameters(void*)"ODOM", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Odom Task");
}
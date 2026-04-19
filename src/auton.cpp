

/**
 * 2026 Pushback Tournament
 * Team 938G Coder ARM
 * Pros ProsAuton.cpp
 */

 /*
 * This is the co-ordinate plane below, the points are in (x,y)
 * This looking at the field with the Red on the right side
 * and blue on the left side when looking from outside onto the field.
 *   
 *
 *               (-, +)  |  (+, +)
 *  blue park    _________________   red park
 *               (-, -)  |  (+, -)
 *
 *
 */

//Include initialized devices and ProsAuton.h.
#include "Initialize.h"
#include "Auton.h"
#include "lemlib/timer.hpp"



// float getDistanceInInches(pros::Distance& sensor) {
//     return sensor.get() * 0.0393701;
// }

// float calculateDistanceFromFront() {
//     // Calculate the actual robot position and ensure we drove the right 
//     // distance in case we are off using the front distance sensor.
//     float currentRobotDistanceFromWall = getDistanceInInches(frontDistanceSensor) + FRONT_DISTANCE_SENSOR_TO_CENTER;
//     float currentRobotDistanceFromStart = HALF_FIELD_DISTANCE - currentRobotDistanceFromWall;
//     return currentRobotDistanceFromStart;
// }

// float calculateDistanceFromLeft() {
//     // Calculate the actual robot position and ensure we drove the right 
//     // distance in case we are off using the front distance sensor.
//     float currentRobotDistanceFromWall = getDistanceInInches(leftDistanceSensor) + LEFT_DISTANCE_SENSOR_TO_CENTER;
//     float currentRobotDistanceFromStart = HALF_FIELD_DISTANCE - currentRobotDistanceFromWall;
//     return currentRobotDistanceFromStart;
// }

// float calculateDistanceFromRight() {
//     // Calculate the actual robot position and ensure we drove the right 
//     // distance in case we are off using the front distance sensor.
//     float currentRobotDistanceFromWall = getDistanceInInches(rightDistanceSensor) + RIGHT_DISTANCE_SENSOR_TO_CENTER;
//     float currentRobotDistanceFromStart = HALF_FIELD_DISTANCE - currentRobotDistanceFromWall;
//     return currentRobotDistanceFromStart;
// }

// float calculateDistanceFromBack() {
//     // Calculate the actual robot position and ensure we drove the right 
//     // distance in case we are off using the front distance sensor.
//     float currentRobotDistanceFromWall = getDistanceInInches(backDistanceSensor) + BACK_DISTANCE_SENSOR_TO_CENTER;
//     float currentRobotDistanceFromStart = HALF_FIELD_DISTANCE - currentRobotDistanceFromWall;
//     return currentRobotDistanceFromStart;
// }


void soloAWP() {
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    chassis.setPose(47, 0, 0);

    // Go to first match loader (right)
    chassis.moveToPoint(47, 48, 2000);
    Hood.set_value(true);
    chassis.waitUntilDone();
    chassis.turnToHeading(90, 500, {.maxSpeed = 100});
    MatchLoader.set_value(true);
    Intake.move(127);
    Transfer.move(-127);
    Outtake.move(127);
    chassis.waitUntilDone();

    chassis.moveToPoint(60, 48, 1000, {.minSpeed = 40});
    chassis.waitUntilDone();    
    chassis.moveToPoint(58, 48, 1000, {.maxSpeed = 40});
    chassis.waitUntilDone();
    pros::delay(700);
    
    // go to long goal and outtake
    chassis.moveToPoint(29, 49.5, 1000, {.forwards = false, .minSpeed = 20});
    MatchLoader.set_value(false);
    chassis.waitUntilDone();

    chassis.arcade(-70, 0);
    Hood.set_value(false);
    pros::delay(700);
    chassis.arcade(0, 0);
    // leave long goal and go to right cluster of 3 blocks
    chassis.turnToPoint(18,24, 500, {.minSpeed = 40});
    chassis.waitUntilDone();
    Hood.set_value(true);

    chassis.moveToPoint(19,24, 1000, {.minSpeed = 70});
    //chassis.waitUntil(5.5);
    //MatchLoader.set_value(true);
    chassis.waitUntilDone();
    //pros::delay(100);
    //MatchLoader.set_value(false);

    // go to the second left cluster of 3 blocks
    chassis.turnToPoint(20, -15, 500, {.minSpeed = 40});
    chassis.waitUntilDone();

    chassis.moveToPoint(20, -15, 1000, {.minSpeed = 40});
    //chassis.waitUntil(20);
    //MatchLoader.set_value(true);
    chassis.waitUntilDone();
    //MatchLoader.set_value(false);

    // score blocks in left long goal
    chassis.turnToPoint(41, -42, 500, {.minSpeed = 40});
    chassis.waitUntilDone();

    chassis.moveToPoint(41, -39, 2000, {.minSpeed = 20});
    chassis.waitUntilDone();

    chassis.turnToHeading(90, 500, {.minSpeed = 40});
    chassis.waitUntilDone();

    chassis.moveToPoint(29, -39, 1000, {.forwards = false});
    chassis.waitUntilDone();
    chassis.arcade(-70, 0);
    Hood.set_value(false);
    Intake.move(127);
    Outtake.move(127);
    Transfer.move(-127);
    pros::delay(700);
    chassis.arcade(0, 0);
    chassis.setPose(29, -39, 90);

    // collect blocks from left match loader
    MatchLoader.set_value(true);
    chassis.moveToPoint(58, -39, 1000, {.minSpeed = 40});
    chassis.waitUntilDone();
    chassis.moveToPoint(56, -39, 1000, {.maxSpeed = 40});
    pros::delay(700);

    // Score in mid goal
    chassis.moveToPoint(46, -39, 1000, {.forwards = false, .minSpeed = 40});
    chassis.waitUntil(5.5);
    chassis.turnToPoint(18, 3, 500, {.forwards = false, .minSpeed = 40});
    chassis.waitUntilDone();
    chassis.moveToPoint(18, 3, 1000, {.forwards = false,.minSpeed = 40});
    chassis.waitUntilDone();





}
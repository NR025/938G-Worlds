

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



float getDistanceInInches(pros::Distance& sensor) {
    return sensor.get() * 0.0393701;
}

float calculateDistanceFromFront() {
    // Calculate the actual robot position and ensure we drove the right 
    // distance in case we are off using the front distance sensor.
    float currentRobotDistanceFromWall = getDistanceInInches(FrontDistanceSensor) + FRONT_DISTANCE_SENSOR_TO_CENTER;
    float currentRobotDistanceFromStart = HALF_FIELD_DISTANCE - currentRobotDistanceFromWall;
    return currentRobotDistanceFromStart;
}

float calculateDistanceFromLeft() {
    // Calculate the actual robot position and ensure we drove the right 
    // distance in case we are off using the front distance sensor.
    float currentRobotDistanceFromWall = getDistanceInInches(LeftDistanceSensor) + LEFT_DISTANCE_SENSOR_TO_CENTER;
    float currentRobotDistanceFromStart = HALF_FIELD_DISTANCE - currentRobotDistanceFromWall;
    return currentRobotDistanceFromStart;
}

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
    int firstMatchLoaderY = 47;
    chassis.moveToPoint(47, firstMatchLoaderY, 2200, {.maxSpeed = 80});
    chassis.waitUntilDone();
    
    /*
    float currentY = calculateDistanceFromFront();
    chassis.setPose(47, currentY, 0);
    chassis.moveToPoint(47, firstMatchLoaderY, 500, {.maxSpeed = 60});
    chassis.waitUntilDone();
    */

    int firstLongGoalY = 48;
    chassis.turnToHeading(90, 1000, {.maxSpeed = 90});
    Hood.set_value(true);
    MatchLoader.set_value(true);
    chassis.waitUntilDone();
    Intake.move(127);
    Transfer.move(-127);
    Outtake.move(127);
    chassis.moveToPoint(58, firstLongGoalY, 1500, {.minSpeed = 40});
    chassis.waitUntilDone();
    pros::delay(700);

    // go to long goal and outtake
    //float currentY2 = calculateDistanceFromLeft();
    //chassis.setPose(62, currentY2, 90);
    chassis.moveToPoint(29, firstLongGoalY, 2000, {.forwards = false, .maxSpeed = 90});
    MatchLoader.set_value(false);
    chassis.waitUntilDone();

    chassis.arcade(-127, 0);
    Hood.set_value(false);
    pros::delay(1000);
    chassis.arcade(0, 0);
    float currentY3 = calculateDistanceFromLeft();
    chassis.setPose(29, currentY3, 90);

    // leave long goal and go to right cluster of 3 blocks
    //chassis.setPose(28, 48, chassis.getPose().theta);
    chassis.moveToPoint(36, 48, 1000);
    chassis.waitUntilDone();
    chassis.turnToPoint(29,24, 1000);
    chassis.waitUntilDone();
    Hood.set_value(true);

    chassis.moveToPoint(29, 24, 1000);
    chassis.waitUntilDone();
    pros::delay(200);
    
    // go to the second left cluster of 3 blocks
    chassis.turnToHeading(180, 500);
    chassis.waitUntilDone();
    
    chassis.moveToPoint(29, -20, 2000);
    //chassis.waitUntil(20);
    //MatchLoader.set_value(true);
    chassis.waitUntilDone();
    //MatchLoader.set_value(false);
    
    // score blocks in left long goal
    chassis.turnToPoint(55, -48, 2000);
    chassis.waitUntilDone();

    chassis.moveToPoint(55, -48, 2000);
    chassis.waitUntilDone();

    chassis.turnToHeading(90, 500);
    chassis.waitUntilDone();

    chassis.moveToPoint(28.5, -50, 2000, {.forwards = false});
    chassis.waitUntilDone();
    Hood.set_value(false);
    chassis.arcade(-70, 0);
    Hood.set_value(false);
    Intake.move(127);
    Outtake.move(127);
    Transfer.move(-127);
    pros::delay(700);
    chassis.arcade(0, 0);
    chassis.setPose(28.5, -48, chassis.getPose().theta);
    
    /*
    // collect blocks from left match loader
    MatchLoader.set_value(true);
    pros::delay(350);
    chassis.waitUntilDone();
    chassis.moveToPoint(59, -48, 2000, {.maxSpeed = 60});
    pros::delay(700);

    // Score in mid goal
    chassis.moveToPoint(46, -48, 2000, {.forwards = false, .minSpeed = 40});
    chassis.waitUntil(5.5);
    chassis.turnToPoint(15.5, 8, 1000, {.forwards = false, .minSpeed = 40});
    chassis.waitUntilDone();
    chassis.moveToPoint(15.5, 8, 2000, {.forwards = false,.minSpeed = 40});
    chassis.waitUntilDone();
    Intake.move(127);
    Outtake.move(-127);
    Transfer.move(-127);


    */
}



void sevenBlockElemsAutonRightSide() {
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    chassis.setPose(47, 12, 270);

    // Intake cluster of 3
    chassis.moveToPoint(42, 12, 2000);
    Hood.set_value(true);
    chassis.waitUntilDone();
    Intake.move(127);
    Transfer.move(-127);
    Outtake.move(127);
    chassis.turnToPoint(24, 23, 1000);
    chassis.waitUntilDone();
    chassis.moveToPoint(24, 23, 2000);
    chassis.waitUntilDone();
    chassis.turnToPoint(41, 48, 2000, {.forwards = false});
    chassis.waitUntilDone();
    chassis.moveToPoint(41, 48, 2000, {.forwards = false});
    chassis.waitUntilDone();
    chassis.turnToHeading(90, 2000);
    chassis.waitUntilDone();
    MatchLoader.set_value(true);
    pros::delay(500);

    chassis.moveToPoint(62, 48, 2000);
    pros::delay(1000);

    // score in long goal
    chassis.moveToPoint(53, 48, 2000, {.forwards = false});
    chassis.waitUntilDone();
    Hood.set_value(false);
    pros::delay(700);


    



}
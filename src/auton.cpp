

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
    chassis.moveToPoint(47, firstMatchLoaderY, 2000, {.maxSpeed = 100});
    SecondDescore.set_value(true);
    chassis.waitUntilDone();
    
    
    float currentY = calculateDistanceFromFront();
    chassis.setPose(47, currentY, 0);
    chassis.moveToPoint(47, firstMatchLoaderY, 500, {.maxSpeed = 60});
    chassis.waitUntilDone();

    

    chassis.turnToHeading(90, 1000, {.maxSpeed = 100});
    chassis.waitUntilDone();

    MatchLoader.set_value(true);
    Hood.set_value(true);
    Intake.move(127);
    Transfer.move(-127);
    Outtake.move(127);
    pros::delay(145);

    chassis.moveToPoint(56, firstMatchLoaderY, 1500, {.minSpeed = 60});
    chassis.waitUntilDone();
    chassis.arcade(25, 0);
    pros::delay(650);
    chassis.arcade(0, 0);


    int firstLongGoalY = 48;
    // go to long goal and outtake
    //float currentY2 = calculateDistanceFromLeft();
    //chassis.setPose(62, currentY2, 90);
    chassis.moveToPoint(29, firstLongGoalY, 2000, {.forwards = false});
    chassis.waitUntilDone();
    MatchLoader.set_value(false);

    chassis.arcade(-127, 0);
    Hood.set_value(false);
    pros::delay(670);
    chassis.arcade(0, 0);
    float currentY3 = calculateDistanceFromLeft();
    chassis.setPose(29, currentY3, chassis.getPose().theta);

    // leave long goal and go to right cluster of 3 blocks
    //chassis.setPose(28, 48, chassis.getPose().theta);
    chassis.moveToPoint(36, 48, 1000, {.minSpeed = 30});
    //chassis.waitUntilDone();
    chassis.turnToPoint(26,25, 5000, {.minSpeed = 30});
    chassis.waitUntilDone();
    Hood.set_value(true);

    chassis.moveToPoint(26, 25, 1000, {.minSpeed =30});
    //chassis.waitUntilDone();
    //pros::delay(70);
    
    // go to the second left cluster of 3 blocks
    chassis.turnToHeading(180, 500, {.minSpeed = 30});
    chassis.waitUntilDone();
    
    chassis.moveToPoint(27, -20, 2000, {.minSpeed = 40});
    //chassis.waitUntil(20);
    //MatchLoader.set_value(true);
    //chassis.waitUntilDone();
    //MatchLoader.set_value(false);
    
    // score blocks in left long goal
    chassis.turnToPoint(55, -48.5, 400, {.minSpeed = 40});
    chassis.waitUntilDone();

    chassis.moveToPoint(55, -48.5, 1100, {.minSpeed = 45});
    //chassis.waitUntilDone();

    chassis.turnToHeading(90, 500, {.minSpeed = 40});
    chassis.waitUntilDone();
    chassis.setPose(55, -48.5, 90);
    /*
    chassis.moveToPoint(35, -49.5, 2000, {.forwards = false, .minSpeed = 40});
    chassis.waitUntilDone();
    Hood.set_value(false);
    chassis.arcade(-127, 0);
    MatchLoader.set_value(true);
    pros::delay(670);
    chassis.arcade(0, 0);
    chassis.setPose(28.5, -48.5, 90);
    
    // collect blocks from left match loader
    chassis.moveToPoint(43, -48.5, 2000);
    chassis.waitUntilDone();
    chassis.moveToPoint(65, -48.5, 2000, {.minSpeed = 65});
    Hood.set_value(true);
    chassis.waitUntilDone();
    pros::delay(475);

    // Score in mid goal
    chassis.moveToPoint(48, -50.5, 2000, {.forwards = false, .minSpeed = 40});
    chassis.turnToPoint(20, -10, 1000, {.forwards = false, .minSpeed = 40});
    chassis.waitUntilDone();
    chassis.moveToPoint(20, -10, 2000, {.forwards = false, .minSpeed = 60, .earlyExitRange = 0.5});
    Hood.set_value(false);
    chassis.waitUntilDone();
    Intake.move(127);
    Outtake.move(-127);
    Transfer.move(-127);*/


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

    // wing
    chassis.moveToPoint(38, 48, 2000);
    chassis.waitUntilDone();

    chassis.turnToPoint(22.5, 33, 1000, {.forwards = false});
    chassis.waitUntilDone();
    chassis.moveToPoint(22.5, 33, 2000, {.forwards = false});
    chassis.waitUntilDone();
    
    chassis.turnToHeading(90, 1000);
    chassis.waitUntilDone();
    Descore.set_value(true);
    chassis.moveToPoint(12, 33, 2000, {.forwards = false});
    chassis.waitUntilDone();






    



}


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
    chassis.moveToPoint(47, firstMatchLoaderY, 1500, {.maxSpeed = 100});
    SecondDescore.set_value(true);
    chassis.waitUntilDone();
    
    /*
    float currentY = calculateDistanceFromFront();
    chassis.setPose(47, currentY, chassis.getPose().theta);
    chassis.moveToPoint(47, firstMatchLoaderY, 500, {.maxSpeed = 60});
    chassis.waitUntilDone();
    */
    
    chassis.turnToHeading(90, 1000, {.maxSpeed = 70});
    MatchLoader.set_value(true);
    Hood.set_value(false);
    chassis.waitUntilDone();

    chassis.moveToPoint(54, firstMatchLoaderY, 1500, {.minSpeed = 60});
    Intake.move(127);
    Transfer.move(-127);
    Outtake.move(127);
    chassis.waitUntilDone();
    chassis.arcade(20, 0);
    pros::delay(800);
    chassis.arcade(0, 0);

    int firstLongGoalY = 49;
    // go to long goal and outtake
    //float currentY2 = calculateDistanceFromLeft();
    //chassis.setPose(62, currentY2, 90);
    chassis.moveToPoint(29, firstLongGoalY, 2000, {.forwards = false});
    chassis.waitUntilDone();
    MatchLoader.set_value(false);

    chassis.arcade(-127, 0);
    Hood.set_value(true);
    pros::delay(670);

    chassis.arcade(0, 0);
    //pros::delay(500);
    
    //float currentY3 = calculateDistanceFromLeft();
    chassis.setPose(29, 49, 90);

    //pros::lcd::print(2, "Current Y: %f currenttheta: %d", currentY3, currenttheta);

    // leave long goal and go to right cluster of 3 blocks
    //chassis.setPose(28, 48, chassis.getPose().theta);
    chassis.moveToPoint(36, 49, 1000, {.minSpeed = 20});
    //chassis.waitUntilDone();

    int blockClusterX = 23.5;
    chassis.turnToHeading(180, 700, {.maxSpeed = 60,.minSpeed = 5});
    chassis.waitUntilDone();
    Hood.set_value(false);

    chassis.moveToPoint(blockClusterX, 24, 2000);
    //chassis.waitUntilDone();
    //pros::delay(70);
    
    // go to the second left cluster of 3 blocks
    chassis.turnToHeading(180, 1000, {.maxSpeed = 70, .minSpeed = 10});
    //chassis.turnToPoint(23.5, -24, 1500, {.maxSpeed = 50});//,.minSpeed = 20});
    chassis.waitUntilDone();
    //pros::delay(3000);
 
    int secondBlockClusterX = 23.5; //38;
    chassis.moveToPoint(secondBlockClusterX, -24, 2000, {.minSpeed = 30});
    //chassis.waitUntil(20);
    //MatchLoader.set_value(true);
    //chassis.waitUntilDone();
    //MatchLoader.set_value(false);
    
    // go to left long goal
    int secondLongGoalY = -48;
    chassis.turnToPoint(50, secondLongGoalY, 400, {.maxSpeed = 70, .minSpeed = 10});
    chassis.waitUntilDone();

    chassis.moveToPoint(50, secondLongGoalY, 2000);
    chassis.waitUntilDone();

    chassis.turnToHeading(90, 500, {.maxSpeed = 70, .minSpeed = 10});
    chassis.waitUntilDone();
    chassis.setPose(50, secondLongGoalY, 90);
    
    // Align with the long goal and outtake
    chassis.moveToPoint(30, -49, 1000, {.forwards = false, .maxSpeed = 75});
    chassis.waitUntilDone();
    Hood.set_value(true);
    chassis.arcade(-127, 0);
    MatchLoader.set_value(true);
    pros::delay(670);
    chassis.arcade(0, 0);
    //pros::delay(500);
    chassis.setPose(28.5, -48, 90);
    //pros::delay(500);

    
    // collect blocks from left match loader
    chassis.moveToPoint(43, -46, 2000);
    chassis.waitUntilDone();
    chassis.moveToPoint(59, -46, 2000, {.minSpeed = 60});
    Hood.set_value(false);
    chassis.waitUntilDone();
    chassis.arcade(20, 0);
    pros::delay(475);
    chassis.arcade(0, 0);

    // Score in mid goal
    chassis.moveToPoint(48, -50.5, 2000, {.forwards = false, .minSpeed = 20});
    chassis.turnToPoint(21, -12.5, 1000, {.forwards = false, .minSpeed = 20});
    chassis.waitUntilDone();
    chassis.moveToPoint(21, -12.5, 2000, {.forwards = false, .minSpeed = 60, .earlyExitRange = 0.5});
    Hood.set_value(true);
    chassis.waitUntilDone();
    Intake.move(127);
    Outtake.move(-127);
    Transfer.move(-127);
    pros::delay(1000);
    Intake.move(0);
    Outtake.move(0);
    Transfer.move(0);

}




void sevenBlockElemsAutonRightSide() {
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    chassis.setPose(47, 12, 270);

    // Intake cluster of 3
    chassis.moveToPoint(42, 12, 2000);
    Hood.set_value(false);
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
    
    // match load
    int firstMatchLoaderY = 46;
    chassis.moveToPoint(55, firstMatchLoaderY, 1500, {.minSpeed = 60});
    chassis.waitUntilDone();
    chassis.arcade(20, 0);
    pros::delay(870);
    chassis.arcade(0, 0);

    // score in long goal
    int firstLongGoalY = 49;
    chassis.moveToPoint(29, firstLongGoalY, 2000, {.forwards = false});
    chassis.waitUntilDone();
    chassis.arcade(-127, 0);
    Hood.set_value(true);
    MatchLoader.set_value(false);
    pros::delay(1000);
    chassis.setPose(29, firstLongGoalY, 90);

    // wing
    Descore.set_value(false);
    SecondDescore.set_value(false);
    chassis.moveToPoint(41, 49, 2000);
    chassis.waitUntilDone();

    chassis.turnToPoint(37, 41, 1000, {.forwards = false});
    chassis.waitUntilDone();
    chassis.moveToPoint(37, 41, 2000, {.forwards = false});
    chassis.waitUntilDone();
    
    chassis.swingToHeading(90, DriveSide::LEFT, 2000);
    chassis.waitUntilDone();
    chassis.moveToPoint(12, 41, 2000, {.forwards = false, .maxSpeed = 60});
    chassis.waitUntilDone();


}


void fourBlockElemsAutonRightSide() {
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    chassis.setPose(47, 12, 270);

    // Intake cluster of 3
    chassis.moveToPoint(42, 12, 800);
    Hood.set_value(false);
    chassis.waitUntilDone();
    Intake.move(127);
    Transfer.move(-127);
    Outtake.move(127);
    chassis.turnToPoint(24, 23, 700);
    chassis.waitUntilDone();
    chassis.moveToPoint(24, 23, 1000);
    chassis.waitUntilDone();
    chassis.turnToPoint(41, 48, 2000, {.forwards = false});
    chassis.waitUntilDone();
    chassis.moveToPoint(41, 48, 2000, {.forwards = false});
    chassis.waitUntilDone();
    chassis.turnToHeading(90, 1100);
    chassis.waitUntilDone();
    //MatchLoader.set_value(true);
    pros::delay(500);

    // score in long goal
    int firstLongGoalY = 49;
    chassis.moveToPoint(29, firstLongGoalY, 1000, {.forwards = false});
    chassis.waitUntilDone();
    chassis.arcade(-127, 0);
    Hood.set_value(true);
    MatchLoader.set_value(false);
    pros::delay(600);
    chassis.setPose(29, firstLongGoalY, 90);

    // wing
    Descore.set_value(false);
    SecondDescore.set_value(false);
    chassis.moveToPoint(41, 49, 1000);
    chassis.waitUntilDone();

    chassis.turnToPoint(37, 41, 700, {.forwards = false});
    chassis.waitUntilDone();
    chassis.moveToPoint(37, 41, 1000, {.forwards = false});
    chassis.waitUntilDone();
    
    chassis.swingToHeading(90, DriveSide::LEFT, 2000);
    chassis.waitUntilDone();
    chassis.moveToPoint(12, 41, 2000, {.forwards = false, .maxSpeed = 60});
    chassis.waitUntilDone();


}





void DONOTUSEsoloAWPFast() {
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    chassis.setPose(47, 0, 0);

    // Go to first match loader (right)
    int firstMatchLoaderY = 47;
    chassis.moveToPoint(47, firstMatchLoaderY, 1500, {.maxSpeed = 100});
    SecondDescore.set_value(true);
    chassis.waitUntilDone();
    
    /*
    float currentY = calculateDistanceFromFront();
    chassis.setPose(47, currentY, chassis.getPose().theta);
    chassis.moveToPoint(47, firstMatchLoaderY, 500, {.maxSpeed = 60});
    chassis.waitUntilDone();
    */
    
    MatchLoader.set_value(true);
    chassis.turnToHeading(90, 1000, {.maxSpeed = 80});
    chassis.waitUntilDone();

    Hood.set_value(false);
    Intake.move(127);
    Transfer.move(-127);
    Outtake.move(127);
    pros::delay(150);

    chassis.moveToPoint(54, firstMatchLoaderY, 1500, {.minSpeed = 60});
    chassis.arcade(20, 0);
    pros::delay(800);
    chassis.arcade(0, 0);

    int firstLongGoalY = 49;
    // go to long goal and outtake
    //float currentY2 = calculateDistanceFromLeft();
    //chassis.setPose(62, currentY2, 90);
    chassis.moveToPoint(29, firstLongGoalY, 2000, {.forwards = false, .minSpeed = 80});
    MatchLoader.set_value(false);

    chassis.cancelMotion();
    chassis.arcade(-127, 0);
    Hood.set_value(true);
    pros::delay(670);

    chassis.arcade(0, 0);
    chassis.cancelMotion();
    pros::delay(500);
    
    float currentY3 = calculateDistanceFromLeft();
    chassis.setPose(29, currentY3, 90);

    //pros::lcd::print(2, "Current Y: %f currenttheta: %d", currentY3, currenttheta);

    // leave long goal and go to right cluster of 3 blocks
    //chassis.setPose(28, 48, chassis.getPose().theta);
    chassis.moveToPoint(36, 48, 1000, {.minSpeed = 60});
    //chassis.waitUntilDone();

    int blockClusterX = 23.5;
    chassis.turnToPoint(blockClusterX, 24, 700, {.minSpeed = 60});
    Hood.set_value(false);

    chassis.moveToPoint(blockClusterX, 24, 1000, {.minSpeed = 60});
    //chassis.waitUntilDone();
    //pros::delay(70);
    
    // go to the second left cluster of 3 blocks
    chassis.turnToHeading(178, 700, {.minSpeed = 60});
    //chassis.waitUntilDone();
 
    int secondBlockClusterX = 22.7; //38;
    chassis.moveToPoint(secondBlockClusterX, -24, 2000, {.minSpeed = 30});
    //chassis.waitUntil(20);
    //MatchLoader.set_value(true);
    //chassis.waitUntilDone();
    //MatchLoader.set_value(false);
    
    /*
    // go to left long goal
    int secondLongGoalY = -48;
    chassis.turnToPoint(50, secondLongGoalY, 400, {.minSpeed = 20});
    chassis.waitUntilDone();

    chassis.moveToPoint(50, secondLongGoalY, 2000);
    chassis.waitUntilDone();

    chassis.turnToHeading(90, 500, {.minSpeed = 20});
    chassis.waitUntilDone();
    chassis.setPose(50, secondLongGoalY, 90);
    
    // Align with the long goal and outtake
    chassis.moveToPoint(30, -49, 1000, {.forwards = false, .maxSpeed = 75});
    chassis.waitUntilDone();
    Hood.set_value(true);
    chassis.arcade(-127, 0);
    MatchLoader.set_value(true);
    pros::delay(670);
    chassis.arcade(0, 0);
    chassis.setPose(28.5, -48, 90);

    
    // collect blocks from left match loader
    chassis.moveToPoint(43, -48, 2000);
    chassis.waitUntilDone();
    chassis.moveToPoint(59, -48, 2000, {.minSpeed = 60});
    Hood.set_value(false);
    chassis.waitUntilDone();
    chassis.arcade(20, 0);
    pros::delay(475);
    chassis.arcade(0, 0);

    // Score in mid goal
    chassis.moveToPoint(48, -50.5, 2000, {.forwards = false, .minSpeed = 20});
    chassis.turnToPoint(21, -12.5, 1000, {.forwards = false, .minSpeed = 20});
    chassis.waitUntilDone();
    chassis.moveToPoint(21, -12.5, 2000, {.forwards = false, .minSpeed = 60, .earlyExitRange = 0.5});
    Hood.set_value(true);
    chassis.waitUntilDone();
    Intake.move(127);
    Outtake.move(-127);
    Transfer.move(-127);
    pros::delay(1000);
    Intake.move(0);
    Outtake.move(0);
    Transfer.move(0);
    */
}


void awpRightSide() {
    // Intake blocks from right match loader
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    chassis.setPose(47, 11, 0);

    // Go to (right) match loader
    int firstMatchLoaderY = 46;
    chassis.moveToPoint(47, firstMatchLoaderY, 1500, {.maxSpeed = 100});
    SecondDescore.set_value(true);
    chassis.waitUntilDone();
    
    chassis.turnToHeading(90, 1500, {.maxSpeed = 80});
    chassis.waitUntilDone();

    MatchLoader.set_value(true);
    Hood.set_value(false);
    Intake.move(127);
    Transfer.move(-127);
    Outtake.move(127);
    pros::delay(145);

    chassis.moveToPoint(55, firstMatchLoaderY, 1500, {.minSpeed = 60});
    chassis.waitUntilDone();
    chassis.arcade(20, 0);
    pros::delay(870);
    chassis.arcade(0, 0);

    // Score blocks in right long goal
    int firstLongGoalY = 49;
    // go to long goal and outtake
    //float currentY2 = calculateDistanceFromLeft();
    //chassis.setPose(62, currentY2, 90);
    chassis.moveToPoint(29, firstLongGoalY, 2000, {.forwards = false});
    chassis.waitUntilDone();
    MatchLoader.set_value(false);

    chassis.arcade(-127, 0);
    Hood.set_value(true);
    pros::delay(760);

    chassis.arcade(0, 0);
    //pros::delay(500);
    
    //float currentY3 = calculateDistanceFromLeft();
    chassis.setPose(29, 49, 90);

    // leave long goal and go to right cluster of 3 blocks
    chassis.moveToPoint(39, 49, 2000);
    chassis.waitUntilDone();

    chassis.turnToPoint(24, 24, 1000);
    chassis.waitUntilDone();
    Hood.set_value(false);
    chassis.waitUntilDone();

    chassis.moveToPoint(24, 24, 1000, {.maxSpeed = 55});
    chassis.waitUntilDone();

    chassis.turnToPoint(15.5, 13, 2000);
    chassis.waitUntilDone();

    chassis.moveToPoint(15.5, 13, 1000);
    chassis.waitUntilDone();

    chassis.turnToHeading(225, 1000, {.maxSpeed = 70});
    chassis.waitUntilDone();



    // int blockClusterX = 23.5;
    // chassis.turnToPoint(blockClusterX, 24, 700);
    // chassis.waitUntilDone();
    // Hood.set_value(false);

    // chassis.moveToPoint(blockClusterX, 24, 1000, {.maxSpeed = 70});
    // chassis.waitUntilDone();

    // // score in bottom goal
    // chassis.turnToPoint(11, 14, 1000);
    // chassis.waitUntilDone();
    // chassis.moveToPoint(11, 14, 1000);
    // chassis.waitUntilDone();


    Intake.move(-70);
    Outtake.move(-70);
    Transfer.move(70);


}

void awpLeftSide() {
    // Intake blocks from right match loader
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    chassis.setPose(47, -11, 180);

    // Go to (right) match loader
    int firstMatchLoaderY = -47;
    chassis.moveToPoint(47, firstMatchLoaderY, 1500, {.maxSpeed = 100});
    SecondDescore.set_value(true);
    chassis.waitUntilDone();
    
    chassis.turnToHeading(90, 1500, {.maxSpeed = 80});
    chassis.waitUntilDone();

    MatchLoader.set_value(true);
    Hood.set_value(false);
    Intake.move(127);
    Transfer.move(-127);
    Outtake.move(127);
    pros::delay(145);

    chassis.moveToPoint(54, firstMatchLoaderY, 1500, {.minSpeed = 60});
    chassis.waitUntilDone();
    chassis.arcade(20, 0);
    pros::delay(800);
    chassis.arcade(0, 0);

    // Score blocks in right long goal
    int firstLongGoalY = -47;
    // go to long goal and outtake
    //float currentY2 = calculateDistanceFromLeft();
    //chassis.setPose(62, currentY2, 90);
    chassis.moveToPoint(29, firstLongGoalY, 2000, {.forwards = false});
    chassis.waitUntilDone();
    MatchLoader.set_value(false);

    chassis.arcade(-127, 0);
    Hood.set_value(true);
    pros::delay(760);

    chassis.arcade(0, 0);
    //pros::delay(500);
    
    //float currentY3 = calculateDistanceFromLeft();
    chassis.setPose(29, -47, 90);

    // leave long goal and go to right cluster of 3 blocks
    chassis.moveToPoint(39, -47, 2000);
    chassis.waitUntilDone();

    chassis.turnToPoint(24, -24, 1000);
    chassis.waitUntilDone();
    Hood.set_value(false);
    chassis.waitUntilDone();

    chassis.moveToPoint(24, -24, 1000, {.maxSpeed = 70});
    chassis.waitUntilDone();

    chassis.turnToPoint(10, -10, 2000, {.forwards = false});
    chassis.waitUntilDone();

    chassis.moveToPoint(10, -10, 1000, {.forwards = false});
    chassis.waitUntilDone();
    Intake.move(127);
    Outtake.move(-127);
    Transfer.move(-127);


}


void fastSoloAWP() {
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    chassis.setPose(47, 0, 0);

    // Go to first match loader (right)
    int firstMatchLoaderY = 46.5;
    chassis.moveToPoint(47, firstMatchLoaderY, 1500, {.maxSpeed = 100});
    SecondDescore.set_value(true);
    chassis.waitUntilDone();
    
    chassis.turnToHeading(90, 1000, {.maxSpeed = 70});
    chassis.waitUntilDone();

    MatchLoader.set_value(true);
    Hood.set_value(false);
    pros::delay(200);

    // Intake blocks fromloader
    chassis.moveToPoint(60, firstMatchLoaderY, 1500, {.maxSpeed = 60});
    Intake.move(127);
    Transfer.move(-127);
    Outtake.move(127);
    chassis.waitUntilDone();
    chassis.arcade(20, 0);
    pros::delay(500);
    chassis.arcade(0, 0);


    int firstLongGoalY = 49;
    // go to long goal and outtake
    chassis.moveToPoint(32, firstLongGoalY, 2000, {.forwards = false});
    chassis.waitUntilDone();
    MatchLoader.set_value(false);

    chassis.arcade(-127, 0);
    Hood.set_value(true);
    pros::delay(670);

    chassis.arcade(0, 0);
    chassis.setPose(29, 49, 90);

    // leave long goal and go to right cluster of 3 blocks
    chassis.moveToPoint(42, 49, 2000);
    chassis.waitUntilDone();
    chassis.turnToPoint(24, 24, 700);
    //chassis.swingToPoint(24, 24, DriveSide::RIGHT, 2000);
    chassis.waitUntilDone();
    Hood.set_value(false);
    chassis.moveToPoint(24, 24, 2000, {.maxSpeed = 70});
    chassis.waitUntilDone();

    chassis.turnToPoint(26, -22.5, 700);
    chassis.waitUntilDone();
    chassis.moveToPoint(26, -22.5, 2000);
    chassis.waitUntilDone();

    chassis.turnToPoint(13.5, -15, 700, {.forwards = false});
    chassis.waitUntilDone();
    chassis.moveToPoint(13.5, -15, 2000, {.forwards = false});
    chassis.waitUntilDone();
    Hood.set_value(true);
    Outtake.move(-127);
    pros::delay(1000);


    //Go get blocks from left match loader
    chassis.moveToPoint(49, -47, 2000);
    chassis.waitUntilDone();
    chassis.turnToHeading(90, 700);
    chassis.waitUntilDone();
    MatchLoader.set_value(true);

    int firstMatchLoaderY2 = -45.5;
    chassis.moveToPoint(60, firstMatchLoaderY2, 1500, {.maxSpeed = 60});
    Intake.move(127);
    Transfer.move(-127);
    Outtake.move(127);
    chassis.waitUntilDone();
    chassis.arcade(20, 0);
    pros::delay(550);
    chassis.arcade(0, 0);


    int firstLongGoalY2 = -47;
    // go to long goal and outtake
    chassis.moveToPoint(32, firstLongGoalY2, 2000, {.forwards = false});
    chassis.waitUntilDone();
    MatchLoader.set_value(false);

    chassis.arcade(-127, 0);
    Hood.set_value(true);
    pros::delay(670);

    chassis.arcade(0, 0);

}
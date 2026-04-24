/**
 * 2026 Pushback Tournament
 * Team 938G Coder ARM
 * Pros ProsImp.h
 */

//Includes api.h.
#include "api.h"
#include "lemlib/api.hpp"
#include "pros/distance.hpp"
#ifndef _PROS_IMP_H_
#define _PROS_IMP_H_

//- Declare objects as initialization.
#define FRONT_DISTANCE_SENSOR_TO_CENTER  5.5
#define LEFT_DISTANCE_SENSOR_TO_CENTER  5.25
#define HALF_FIELD_DISTANCE 72

//Declare controller and other general objects.
extern pros::Controller MasterCont;

//Declare 6 motor drivetrain with left and right motor groups.
extern pros::Motor LFwheel;
extern pros::Motor LMwheel;
extern pros::Motor LBwheel;
extern pros::Motor RFwheel;
extern pros::Motor RMwheel;
extern pros::Motor RBwheel;

extern pros::MotorGroup LMotorGroup;
extern pros::MotorGroup RMotorGroup;

extern lemlib::Drivetrain drivetrain;
extern lemlib::Chassis chassis;

//Declare block processing flywheels as motors separated by height.
extern pros::Motor Intake;
extern pros::Motor Transfer;
extern pros::Motor Outtake;

//Declare pneumatics.
extern pros::adi::Pneumatics Descore;
extern pros::adi::Pneumatics SecondDescore;
extern pros::adi::Pneumatics MatchLoader;
extern pros::adi::Pneumatics Hood;

//Declare sensors and odom.
extern pros::Imu IMU;
//Declare extra opcontrol lemlib.
extern lemlib::ExpoDriveCurve ThrottleCurve;
extern lemlib::ExpoDriveCurve SteerCurve;

//Declare PID.
extern lemlib::ControllerSettings LController;
extern lemlib::ControllerSettings AController;

extern pros::Distance FrontDistanceSensor;
extern pros::Distance LeftDistanceSensor;

#endif //_PROS_IMP_H_
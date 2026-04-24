/**
 * 2026 Pushback Tournament
 * Team 938G Coder ARM
 * Pros ProsImp.cpp
 */

//Includes Pros.Imp.
#include "Initialize.h"

//- Define objects as initialization.

//Define controller and other general objects.
pros::Controller MasterCont (pros::E_CONTROLLER_MASTER);


// Competition robot definition starts here.

//Define 6 motor drivetrain with left and right motor groups. 
pros::Motor LFwheel (-11, 
					pros::v5::MotorGears::blue);
pros::Motor LMwheel (-12, 
					pros::v5::MotorGears::blue);
pros::Motor LBwheel (-13, 
					pros::v5::MotorGears::blue);
pros::Motor RFwheel (20,
					pros::v5::MotorGears::blue);
pros::Motor RMwheel (19,
					pros::v5::MotorGears::blue);
pros::Motor RBwheel (18, 
					pros::v5::MotorGears::blue);

pros::MotorGroup LMotorGroup ({-11, -12, -13}, 
							 pros::v5::MotorGearset::blue);
pros::MotorGroup RMotorGroup ({20, 19, 18}, 
							 pros::v5::MotorGearset::blue);

lemlib::Drivetrain drivetrain (&LMotorGroup, 
							  &RMotorGroup, 
							  11.5,
							  lemlib::Omniwheel::NEW_325,
							  450,
							  2);

// Intake and outtake 
pros::Motor Intake (7);
pros::Motor Outtake (8);
pros::Motor Transfer (6);

//Define pneumatics.
pros::adi::Pneumatics Hood('a', false);
pros::adi::Pneumatics SecondDescore('c', false);
pros::adi::Pneumatics Descore('h', true);
pros::adi::Pneumatics MatchLoader('b', false);

//Defines sensors and odom
pros::Imu IMU(16);
//pros::Rotation VerticalSensor(1);
pros::Distance FrontDistanceSensor(5);
pros::Distance LeftDistanceSensor(14);
//Defines extra opcontrol lemlib.
/*
lemlib::ExpoDriveCurve ThrottleCurve (3,
                                     10,
                                     1.019);
lemlib::ExpoDriveCurve SteerCurve (3,
                                  10,
                                  1.019);
*/

lemlib::OdomSensors OSensors (nullptr,
							  nullptr,
							  //&VerticalTracking,
	                          nullptr,
							  nullptr,
							  &IMU);


// lateral PID controller
lemlib::ControllerSettings LateralPID(10, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              10, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (slew)
);

lemlib::ControllerSettings TurningPID(4.5, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              3, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (slew)
);

lemlib::Chassis chassis (drivetrain,
						LateralPID,
						TurningPID,
						OSensors);


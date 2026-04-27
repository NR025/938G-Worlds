/**
 * 2026 Pushback Tournament
 * Team   Coder ARM()
 * Lem main.cpp
 */

//#We include main.h and LemImp, Op, and Auton.
#include "lemlib/api.hpp"
#include "main.h"
#include "Initialize.h"
#include "Auton.h"
#include "lemlib/timer.hpp"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */



void initialize() {
	/*# This commented code in initialize tells us the code program and the lemlib pose
	the robot thinks its at. Only turn on for testing */

	pros::lcd::initialize();
	//pros::lcd::print(7, "ARM, AutonS, 2/14");

	//# Calibrate the chassis.
	chassis.calibrate();
	Descore.set_value(false);
	SecondDescore.set_value(true);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomousS or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

void squareTest() {
	chassis.setPose(0, 0, 0);
	chassis.moveToPoint(0, 18, 1000);
	chassis.turnToHeading(90, 3000);
	chassis.waitUntilDone();
	chassis.moveToPoint(18, 18, 1000);
	chassis.turnToHeading(180, 3000);
	chassis.waitUntilDone();
	chassis.moveToPoint(18, 0, 1000);
	chassis.turnToHeading(270, 3000);
	chassis.waitUntilDone();
	chassis.moveToPoint(0, 0, 1000);
	chassis.turnToHeading(0, 3000);
	chassis.waitUntilDone();
}

void testTurn()	{
	chassis.setPose(0, 0, 0);
	chassis.turnToHeading(90, 1000);
	chassis.waitUntilDone();
	chassis.turnToHeading(180, 1000);
	chassis.waitUntilDone();
	chassis.turnToHeading(270, 1000);
	chassis.waitUntilDone();
	chassis.turnToHeading(0, 1000);
	chassis.waitUntilDone();
}


/**
 * Runs the user autonomous code. This function will be s	tarted in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	//skillsWithDistanceSensor();
	// fastSoloAWP();

	// awpRightSide();
	//fastSoloAWP();
	// sevenBlockElemsAutonRightSide();
	fourBlockElemsAutonRightSide();
	//awpLeftSide();
	//testTurn();
	//sevenBlockElemsAutonRightSide();
	// chassis.setPose(0, 0, 0);
	// chassis.moveToPoint(0, 5, 1000);
	// chassis.waitUntilDone();
	//chassis.turnToHeading(90, 2000);
	//chassis.waitUntilDone();
	//testMatchLoader();
	//testDistanceSensors();
	//testTurn();
	//squareTest();
	//testOuttake();
}



/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 * If no competition control is connected,
 *  this function will run immediately
 * following initialize().
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */


void opcontrol() {

	double TurnFactor = 1;
	bool HoodValue = false;
	bool DescoreValue = true;
	bool LoaderValue = false;

	while (true) {
		// Drive controls
		int LeftY = MasterCont.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int RightX = MasterCont.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
		chassis.arcade (LeftY, RightX);
			
		//Intke, transfer, and outtake controls
		if (MasterCont.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {

			Intake.move(127);
			Transfer.move(-127);
			Outtake.move(127);

		}

		//mid goal outtake
		else if (MasterCont.get_digital(pros::E_CONTROLLER_DIGITAL_Y)){

			Intake.move(127);
			Transfer.move(-127);
			Outtake.move(-127);

		}

		//Reverse(Low goal) outake.
		else if (MasterCont.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {

			Intake.move(-127);
			Transfer.move(127);
			Outtake.move(-127);
		}



		else {
			Intake.move(0);
			Transfer.move(0);
			Outtake.move(0);
		}

		//Hood
		if (MasterCont.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
			if (HoodValue == false) {
				
				Hood.set_value(false);
				HoodValue = true;
				pros::delay(250);

			} else {

				Hood.set_value(true);
				HoodValue = false;
				pros::delay(250);

			}

		}

		//Descore
		if (MasterCont.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
			{
				Descore.set_value(false);
			}

			else
			{
				Descore.set_value(true);
			}
	
		//SecondDescore
		if (MasterCont.get_digital(pros::E_CONTROLLER_DIGITAL_L2))
			{
				SecondDescore.set_value(true);
			}

			else
			{
				SecondDescore.set_value(false);
			}


		// Match loader
		if (MasterCont.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {

			if (LoaderValue == false) {
				
				MatchLoader.set_value(false);
				LoaderValue = true;
				pros::delay(250);

			} else {

				MatchLoader.set_value(true);
				LoaderValue = false;
				pros::delay(250);

			}

	

	}
	}
}
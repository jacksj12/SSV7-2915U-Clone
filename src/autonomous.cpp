#include "main.h"
#include "pid.hpp"
#include "autoSelect/selection.h"
/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() 
{
    PID chassis;
    PID rotation; // A second instance of PID for the imu turning. Should deprecate?

    // Alliance triball in goal.
    if (selector::auton == 1){

        // Push triball in goal for 200ms.
        drive_left.move(1000);
        drive_right.move(1000);
        pros::delay(200);
        // Move away from the goal for 170ms.
        drive_left.move(-800);
        drive_right.move(-800);
        pros::delay(170);
        // HAULT.
        drive_left.move(0);
        drive_right.move(0);
    }
    else if (selector::auton == 2){
        drive_left.move(1000);
        drive_right.move(1000);
        pros::delay(500);
        drive_left.move(-300);
        drive_right.move(-300);
        pros::delay(200);
        drive_left.move(0);
        drive_right.move(0);
    }
    else if (selector::auton == 3){
        chassis.drive(rotation, 5, 0.1,0.1,0.1,10,2,0.2,3);
    }




}
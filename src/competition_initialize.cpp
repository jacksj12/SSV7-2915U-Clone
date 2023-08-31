#include "main.h"
#include "autoSelect/selection.h"
/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */

void competition_initialize() 
{
    // TODO: check that devices are installed. report to cntrl?
    // Check that motors are installed.
    drive_left.size();


    // init auton selector.
    selector::init();
}
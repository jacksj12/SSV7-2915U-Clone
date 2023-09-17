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
    
    // https://pros.cs.purdue.edu/v5/api/cpp/motors.html#pros-motor-flag-e-t
    for(int i=0; i < drive_left_cata.size(); i++) { 
        int motor_flags = drive_left_cata[i].get_flags();

        if(motor_flags == 0x01)
            controller_main.rumble("............................");
        
    }

    for(int i=0; i < drive_left_cata.size(); i++) {
        int motor_flags = drive_right_cata[i].get_flags();

        if (motor_flags == 0x01)
            controller_main.rumble("............................");

    }

}
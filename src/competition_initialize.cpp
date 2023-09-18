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

    
    // When no device connected - Prog brain. "2147483647"
    for(int i=0; i < drive_left_cata.size(); i++) { 
        std::uint32_t motor_flags = drive_left_cata[i].get_flags();
        
        // FIXME: further testing required! 
        //it says to use pros::motor_flag_e_t::E_MOTOR_FLAGS_BUSY,
        // but it seems like it doesn't work X_X use a l-value instead.
        if(motor_flags == 2147483647) {
            std::cout << "Motor Disconected!" << "\n";
            controller_main.rumble("............................");
            break;
        }
    }

    for(int i=0; i < drive_left_cata.size(); i++) {
        std::uint32_t motor_flags = drive_right_cata[i].get_flags();

        if(motor_flags == 2147483647) {
            std::cout << "Motor Disconected!" << "\n";
            controller_main.rumble("............................");
            break;
        }
    }

}
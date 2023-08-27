#include "main.h"
#include "devices.hpp"
#include "opcontrol.hpp"

// https://pros.cs.purdue.edu/v5/api/cpp/index.html





/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

void opcontrol(void)
{
    while (true)
    {
        
        // Get Joysticks 
        int8_t main_left_joystick =  controller_main.get_analog(ANALOG_LEFT_Y); // AXIS 3 of controller_main.
        int8_t main_right_joystick = controller_main.get_analog(ANALOG_RIGHT_X); // AXIS 1 of controller_main.

        if (main_left_joystick != 0)
        {
            main_left_joystick = joystick_scaling(main_left_joystick);
            main_left_joystick = apply_deadzone(main_left_joystick, VERTICAL_DEADZONE);
            main_left_joystick = cubic_scaling(main_left_joystick);
            main_left_joystick = scaled_milivolts(main_left_joystick);
        }
        if (main_right_joystick != 0)
        {
            main_right_joystick = joystick_scaling(main_right_joystick);
            main_right_joystick = apply_deadzone(main_right_joystick, HORIZONTAL_DEADZONE);
            main_right_joystick = cubic_scaling(main_right_joystick);
            main_right_joystick = scaled_milivolts(main_right_joystick);
        }
        drive_left.move_voltage((main_left_joystick + main_right_joystick) / MAX_VOLTS);
        drive_left.move_voltage((main_left_joystick - main_right_joystick) / MAX_VOLTS);
        
        pros::delay(20); // 20 ms for user based interactions
    }
}

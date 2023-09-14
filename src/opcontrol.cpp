#include "main.h"
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
        int8_t joystick_scaling_ammount = 2;    // scales the joystick inputs for the algorithim to not exceed voltage threshold.
                                                // Allows for greater movement when only one joystick signal is active.

        // Get Joysticks.
        int8_t main_left_joystick =  controller_main.get_analog(ANALOG_LEFT_Y); // AXIS 3 of controller_main.
        int8_t main_right_joystick = controller_main.get_analog(ANALOG_RIGHT_X) * -1; // AXIS 1 of controller_main. Invert joystick



        if (main_left_joystick == 0 || main_right_joystick == 0)
        {
            joystick_scaling_ammount = 1;
        }

        // Apply deadzones to Joysticks.
        main_left_joystick = apply_deadzone(main_left_joystick, VERTICAL_DEADZONE);
        main_right_joystick = apply_deadzone(main_right_joystick, HORIZONTAL_DEADZONE);

        // Update the drive motors. The move method uses voltage control.
        drive_left.move((main_left_joystick + main_right_joystick)  / joystick_scaling_ammount);
        drive_right.move((main_left_joystick - main_right_joystick) / joystick_scaling_ammount);


        if(controller_main.get_digital_new_press(DIGITAL_L1))
        {
            wing_left_toggle = !wing_left_toggle; 
            wing_left.set_value(wing_left_toggle);
        }
        if(controller_main.get_digital_new_press(DIGITAL_R1))
        {
            wing_right_toggle = !wing_right_toggle;
            wing_right.set_value(wing_right_toggle);
        }

        pros::delay(20); // 20 ms delay for user based interactions

    }
}

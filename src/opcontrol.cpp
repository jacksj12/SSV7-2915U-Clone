#include "main.h"
#include "opcontrol.hpp"

// https://pros.cs.purdue.edu/v5/api/cpp/index.html
// https://github.com/purduesigbots/pros-docs/tree/e2b268679b89ea566b35a43bcf2e4f8b3248656b/v5/api/cpp

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

        // Get Joysticks.
        int8_t main_left_joystick = controller_main.get_analog(ANALOG_LEFT_Y);        // AXIS 3 of controller_main.
        int8_t main_right_joystick = controller_main.get_analog(ANALOG_RIGHT_X) / 2; // AXIS 1 of controller_main. Invert joystick

        // // Apply deadzones to Joysticks.
        // main_left_joystick = apply_deadzone(main_left_joystick, VERTICAL_DEADZONE);
        // main_right_joystick = apply_deadzone(main_right_joystick, HORIZONTAL_DEADZONE);

        // Update the drive motors. The move method uses voltage control.
        drive_left.move((main_left_joystick + main_right_joystick) );
        drive_right.move((main_left_joystick - main_right_joystick));

        // Wings Toggle.
        if (controller_main.get_digital_new_press(DIGITAL_L1))
        {
            wing_left_toggle = !wing_left_toggle;
            wing_left.set_value(wing_left_toggle);
        }
        if (controller_main.get_digital_new_press(DIGITAL_R1))
        {
            wing_right_toggle = !wing_right_toggle;
            wing_right.set_value(wing_right_toggle);
        }

        
        pros::delay(20); // 20 ms delay for user based interactions
    }
}

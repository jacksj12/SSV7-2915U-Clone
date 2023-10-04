#include "main.h"
#include "opcontrol.hpp"
#include "pid.hpp"

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
    u_int16_t current_time = 0; // The current time of the opcontrol perioid.

    while (true)
    {
        // FOR TESTING ONLY! Runs autonomous function.
        if(controller_main.get_digital_new_press(DIGITAL_B)) autonomous();


            // Sets and toggles the PTO solonoid state.
        if (controller_main.get_digital_new_press(DIGITAL_L2)) {
            pto_enable = ! pto_enable;

            // Checks if the user clicked the button to connect the PTO to the cata.
            // Will not send any power to the motor and it will coast. 
            if (pto_enable) {
                drive_left_cata.move_voltage(0);
                drive_right_cata.move_voltage(0);
            }
            
            pto_cata.set_value(pto_enable);
        }


        // Get Joysticks.
        int8_t main_left_joystick = controller_main.get_analog(ANALOG_LEFT_Y);        // AXIS 3 of controller_main.
        int8_t main_right_joystick = controller_main.get_analog(ANALOG_RIGHT_X) / 2;  // AXIS 1 of controller_main. Scalled cuz ruzi is a bad driver.

        // Apply deadzones to Joysticks.
        main_left_joystick = apply_deadzone(main_left_joystick, VERTICAL_DEADZONE);
        main_right_joystick = apply_deadzone(main_right_joystick, HORIZONTAL_DEADZONE);

        // TODO: Try joystick curving?
        int16_t left_power = main_left_joystick + main_right_joystick;  // Calculates the power from the joysticks which is applied to the left side of the drive.
        int16_t right_power = main_left_joystick - main_right_joystick; // Calculates the power for the joysticks  which is applied to the right side of the drive.

        // Set the PTO and Drive motors power!
        move_motors(left_power, right_power); 


        // Toggle Wings.
        wing_left_toggle    = toggle_wings(DIGITAL_L1, wing_left_toggle, wing_left);        // Check and toggles the Left Wing.
        wing_right_toggle   = toggle_wings(DIGITAL_R1, wing_right_toggle, wing_right);      // Check and toggles the Right Wing.


        // Increaments the time counter by 10ms.
        current_time += 10;

        // Checks if the opcontrol time is within the endgame time.
        if (current_time >= 7500) {
            if (controller_main.get_digital_new_press(DIGITAL_B)) {
                PID robot;

                robot.ballance_pitch(0.1,0,0,0,0,0,0);
            }
        }
        pros::delay(10); // 10 ms delay for user based interactions
    }
}

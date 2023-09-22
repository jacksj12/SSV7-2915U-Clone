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
        int8_t main_right_joystick = controller_main.get_analog(ANALOG_RIGHT_X) / 2;  // AXIS 1 of controller_main. Scalled cuz ruzi is a bad driver.

        // Apply deadzones to Joysticks.
        main_left_joystick = apply_deadzone(main_left_joystick, VERTICAL_DEADZONE);
        main_right_joystick = apply_deadzone(main_right_joystick, HORIZONTAL_DEADZONE);


        // TODO: Try joystick curving?
        // Calculates the power for the joysticks
        int16_t left_power = main_left_joystick + main_right_joystick;
        int16_t right_power = main_left_joystick - main_right_joystick;

        // if the value overflows, scale it so that the user can still turn. May cause unexpected results.
        if (left_power > 127)
            left_power = main_left_joystick / 2 + main_right_joystick;
        
        // if the value overflows, scale it so that the user can still turn. May cause unexpected results.
        if (right_power < -127) 
            right_power = main_left_joystick / 2 + main_right_joystick;


        // Sets and toggles the PTO solonoid state.
        if (controller_main.get_digital_new_press(DIGITAL_A)) {
            pto_enable = ! pto_enable;
            pto_cata.set_value(pto_enable);
        }
        
        // FIXME: This is ugly.. 
        // Update the drive motors. The move method uses voltage control. Determines which motor_group to use. Its Ugly ik.
        // when enable, PTO is connected to drive

        // https://github.com/purduesigbots/pros/blob/1e7513d4f110d2eac625b6300dbbb8c086ab6c0c/include/pros/motors.hpp#L861C4-L861C4
        // https://github.com/purduesigbots/pros/blob/1e7513d4f110d2eac625b6300dbbb8c086ab6c0c/src/devices/vdml_motors.cpp#L337
        // drive_left_cata.move(700);
        
        
        
        if(pto_enable){
            drive_left_cata.move(left_power);
            drive_right_cata.move(right_power);
        }
        // PTO is conntected to cata
        else {
            drive_left.move(left_power);
            drive_right.move(right_power);
        }

 
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

        pros::delay(10); // 10 ms delay for user based interactions
    }
}

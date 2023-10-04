#pragma once // Avoid multiple header links.
#include "main.h"

double squared_scaler(int8_t joystick_value);
int8_t joystick_scaling(int8_t joystick_value);
int8_t apply_deadzone(int8_t joystick_value, int8_t deadzone);
int8_t cubic_scaling(int8_t joystick_value);
int32_t scaled_milivolts(int8_t joystick_value);
void move_motors(int16_t left_power, int16_t right_power);
bool toggle_wings(pros::controller_digital_e_t button, bool wing_toggle, pros::ADIDigitalOut solonoid);

const int8_t MAX_THERSHOLD          = 100;
const int8_t VERTICAL_DEADZONE      = 5;
const int8_t HORIZONTAL_DEADZONE    = 2;
const float MAX_VOLTS               = 12000.0f;
const int8_t MAX_SCALED_JOYSTICK    = 100;
const int8_t MAX_ANALOG_JOYSTICK    = 127;
const int16_t DENOMONATOR           = 10;   // temp!! forgot how this works!
const int16_t MIN_MV                = -12000;
const double VOLTAGE_DRIVE          = 12000.0f / 127.0f;
int16_t drive_left_voltage;
int16_t drive_right_voltage;

bool wing_left_toggle               = false;
bool wing_right_toggle              = true;

bool pto_enable                     = false;



/// @brief 
/// @param joystick_value 
/// @return 
int8_t joystick_scaling(int8_t joystick_value)
{
    return joystick_value / MAX_ANALOG_JOYSTICK * MAX_SCALED_JOYSTICK;
}

/// @brief Determines wether to apply a deadzone to a joystick.
///        If the joystick value is below the deadzone, the function will act.
/// @param joystick_value The value of the joystick -127 to 127.
/// @param deadzone The upper value for the deadzone. 
/// @returns Returns zero if the joystick < the deadzone OR
/// @returns Returns the joystick value.
int8_t apply_deadzone(int8_t joystick_value, int8_t deadzone)
{
      if (joystick_value <= deadzone) 
        {
            return 0;
        }
        return joystick_value;
}

/// @brief 
/// @param joystick_value 
/// @return 
int8_t cubic_scaling(int8_t joystick_value)
{
    return powf(joystick_value / 12.0f, 3) * MAX_THERSHOLD;
}

double squared_scaler(int8_t joystick_value)
{
    return powf(joystick_value, 2) / MAX_VOLTS * sgn(joystick_value);
}

/// @brief 
/// @param joystick_value 
/// @return 
int32_t scaled_milivolts(int8_t joystick_value)
{
    int numerator = joystick_value - (-127);

    // FIXME: denomonator is currently 0, prevent DBZ exception. 
    return MIN_MV + (numerator / DENOMONATOR) * 24000;

    return 0;
}

/// @brief Applys power to move the drivetrain and PTO motors.
/// @param left_power The power needed to be applied to the left drive motors.
/// @param right_power The power needed to be applied to the right drive motors.
void move_motors(int16_t left_power, int16_t right_power) {
    // When PTO is connected to the drive.
    if(pto_enable) {
            drive_left_cata.move(left_power);
            drive_right_cata.move(right_power);
    }
    // The PTO is connected to the cata.
    else {
            // While button is pressing rewind cata
            if (controller_main.get_digital(DIGITAL_R1)) {
                motor_drive_4.move_voltage(-12000);
                motor_drive_8.move_voltage(-12000);
            }
            else {
                motor_drive_4.move_voltage(0);
                motor_drive_8.move_voltage(0);
            }
        // Move only the drive motors. NOT PTO!
        drive_left.move(left_power);
        drive_right.move(right_power);
    }
}

/// @brief Toggles the wings of the robot.
/// @param button The button of the primary / master controller used to toggle the wing. Is a digital input.
/// @param wing_toggle The boolean value of the current state of the wing.
/// @param solonoid The solonoid of that the wing is connected to. Is an digital output.
/// @return The current state of the wing.
bool toggle_wings(pros::controller_digital_e_t button, bool wing_toggle, pros::ADIDigitalOut solonoid) {
        if (controller_main.get_digital_new_press(button))
        {
            wing_toggle = !wing_toggle;
            solonoid.set_value(wing_toggle);
        }
        return wing_toggle;
}
        


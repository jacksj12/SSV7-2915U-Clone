#pragma once // Avoid multiple header links.
#include "main.h"

double squared_scaler(int8_t joystick_value);
int8_t joystick_scaling(int8_t joystick_value);
int8_t apply_deadzone(int8_t joystick_value, int8_t deadzone);
int8_t cubic_scaling(int8_t joystick_value);
int32_t scaled_milivolts(int8_t joystick_value);


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

// C++ sign function
// https://stackoverflow.com/a/4609795
template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

/// @brief 
/// @param joystick_value 
/// @return 
int8_t joystick_scaling(int8_t joystick_value)
{
    return joystick_value / MAX_ANALOG_JOYSTICK * MAX_SCALED_JOYSTICK;
}

/// @brief 
/// @param joystick_value 
/// @param deadzone 
/// @return 
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

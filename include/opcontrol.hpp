#pragma once // Avoid multiple header links.
#include "main.h"

double squared_scaler(int8_t joystick_value, int16_t maximum);
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
const int16_t DENOMONATOR           = 127-(127);
const int16_t MIN_MV                = -12000;


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
      if (abs(joystick_value) <= deadzone) 
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

double squared_scaler(int8_t joystick_value, int16_t maximum)
{
    return pow(joystick_value, 2) / maximum * sgn(joystick_value);
}

/// @brief 
/// @param joystick_value 
/// @return 
int32_t scaled_milivolts(int8_t joystick_value)
{
    int numerator = joystick_value - (-127);

    return MIN_MV + (numerator / DENOMONATOR) * 24000;
}

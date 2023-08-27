#pragma once // Avoid multiple header links.
#include "main.h"

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

/// @brief 
/// @param joystick_value 
/// @return 
int32_t scaled_milivolts(int8_t joystick_value)
{
    return joystick_value / MAX_SCALED_JOYSTICK;
}

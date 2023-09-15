#include "pid.hpp"
#include "main.h"
#include <math.h>


// type safe sgn (sign) function
// https://stackoverflow.com/a/4609795
template <typename T> int sgn(T val) { 
  return (T(0) < val) - (val < T(0)); 
}


double PID::get_PID(double targetValue, double sensorReading){
    error = target_value - sensor_reading; // calculates the distance between target and current robot.

    if(fabs(error) >= 0.0) {
        error = error / target_value * 100;
    }

    derivative = error - previous_error;
    previous_error = error;

    speed = (kp * error) + (kd * derivative);

    return speed;

}
double  PID::get_error(void) {
    return error;
}


void PID::turn_with_gains(double angle, double new_kp, double new_kd) {
    // kinda not nessecary but 👍 
    last_kp = kp;
    last_kd = kd;
    
    // sets custom gains as default.
    kp = new_kp;
    kd = new_kd;
    

    while (1) {
        int8_t turn_direction = 1;

        // get imu current sensing.
        current_heading = imu_drive.get_heading();

        // get speed output.
        speed = PID::get_PID(angle, current_heading);
        
        // determine direction to turn.
        if(fabs(error) < 180){
            int8_t turn_direction = -1;
        }

        // Apply PID power output, convert to voltage and apply turn direction.
        drive_left.move_voltage(speed * 12000 * turn_direction); 
        drive_right.move_voltage(speed * 12000 * turn_direction);
    }
}
// void PID::drive(double inches, double new_kp, double new_kd);
// double PID::get_ticks(double inches);
// void PID::reset(void);




// // print hello world
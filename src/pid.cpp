#include "pid.hpp"
#include "main.h"


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

    power = (kp * error) + (kd * derivative);

    return power;

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
        power = PID::get_PID(angle, current_heading);
        
        // determine direction to turn.
        if(fabs(error) < 180){
            int8_t turn_direction = -1;
        }


        // TODO: Mb set the cata motors to coast and drive only the main drive motors to prevent additional slop / backlash from the PTO gears.
        // Apply PID power output, convert to voltage and apply turn direction.
        drive_left_cata.move_voltage(power * 12000 * turn_direction); 
        drive_right_cata.move_voltage(power * 12000 * turn_direction);
    
        pros::delay(7);
    }
}
void PID::drive(double inches, double new_kp, double new_kd) {
    // gets the direction of which way the robot needs to drive. E.g. 1 is forwards -1 is backwards.
    int direction = sgn(inches);
    
    // resets the positions of all motor encoders.
    drive_left_cata.set_zero_position(0);
    drive_right_cata.set_zero_position(0);

    // Get the value of distance in ticks.
    double distance_in_ticks = get_ticks(inches);
    while(1) {
        

        // Constantly get the newest position of the robot
        double drive_encoder_averages = get_drive_encoders();

        // Constantly Calculate the newest power of the robot.
        power =  PID::get_PID(distance_in_ticks, drive_encoder_averages);

        // Checks if the error is <= 1 (natually there will moslikely be a bit of error e.g. 0.583")
        if (fabs(PID::get_error()) <= 1) {
            // Stops robot
            drive_left_cata.move_voltage(0);
            drive_right_cata.move_voltage(0);
            // Resets values
            PID::reset();
            // Breaks out of PID.
            break;  
        }
        // Constantly apply the newest power to the drivetrain.
        drive_left_cata.move_voltage(power * 12000 * direction); 
        drive_right_cata.move_voltage(power * 12000 * direction);
        
        // Delay program to prevent lockups.
        pros::delay(7);
    }
}



double get_drive_encoders(void){
    // set encoder units to degrees.
    drive_left_cata.set_encoder_units (pros::E_MOTOR_ENCODER_DEGREES);
    drive_right_cata.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);
    
    // TODO: account for the errno if motor is busy.
    // Get average of Drive Encoders.
    double left_drive_encoders =    (drive_left_cata[0].get_position()  + drive_left_cata[2].get_position())    / 2;
    double right_drive_encoders =   (drive_right_cata[0].get_position() + drive_right_cata[2].get_position())   / 2;

    // Return the average of both geartrains. This might cause problems e.g. if one side spins more than the rest it
    // might actually cause error value to be lower than what it should.
    return left_drive_encoders + right_drive_encoders / 2;
}
double get_ticks(double inches){
    return 360 / (4.125 * M_PI) * inches;
}


void PID::reset(void) {
    kp = last_kp;
    kd = last_kd;

    target_value = 0;
    current_heading = 0;
    sensor_reading = 0;

    error = 0;
    previous_error = 0;
    
    derivative = 0;
    power = 0;
}




// // print hello world - youtube.com/@2915Z
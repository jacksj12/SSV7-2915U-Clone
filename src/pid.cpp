#include "pid.hpp"
#include "main.h"


/// @brief Calculates the PID.
/// @param target The target where the robot needs to be.
/// @param sensor_reading What the sensor is reading. Either the motor encoder or IMU.
/// @return The power to be applied to the v5 Motors.
double PID::calculate(double target, double sensor_reading) {
    // calculate the error. Proportional
    error = target - sensor_reading;

    // Get the intergral.
    if (fabs(error) < start_i) 
        accumulated_error += error;

    // Prevent the robot from continuing to drive when we reach the set point.
    if (fabs(error) > 0 && previous_error < 0 || error < 0 && previous_error > 0) 
        accumulated_error = 0;

    // Calculates the output by adding the Proportional, intergral and Derivatives.
    output = (kp * error) + (ki * accumulated_error) + (kd * (error-previous_error));
    
    // Sets output to 100 so we don't exceed the motors max voltage. 
    if (output > 100)
        output = 100;

    // Sets the previous error.
    previous_error = error;

    // Adds time to the settling time.
    if (fabs(error) < settle_error) time_waiting += 10;
    else time_waiting = 0;

    // Adds to total ammount of time.
    time_spent_running += 10;

    return output;
}

/// @brief Checks if the robot can be considered settled.
/// @return true if settled. False if not settled.
bool PID::is_settled(void) {
    // The robot failed to reach its target in specified time. Quits.
    if (time_spent_running > timeout && timeout != 0) 
        return true;
    
    // The robot has settled for more than the ammount of time required.
    if (time_waiting > settle_time)
        return true;
    
    // The robot is not settled.
    return false;
}

/// @brief Calculates the value of a v5 Internal Motor Encoders.
/// @return An average of both sides of the drive using the v5 internal motor encoders.
double get_encoders(void) {
    // Get averages for the left encoders. 
    double left_encoders_averages = (motor_drive_2.get_position() + motor_drive_3.get_position()) / 2;

    // Get averages for the right encoders.
    double right_encoders_averages = (motor_drive_6.get_position() + motor_drive_7.get_position()) / 2;

    // Return encoders.
    return left_encoders_averages + -right_encoders_averages / 2;
}

/// @brief Calculates the distance of the robot in ticks.
/// @param inches The distance to the target - in inches.
/// @return The distance to the target - in ticks.
double get_ticks(double inches) {
    return 360 / (4.125 * M_PI);
}

/// @brief The main PID controller to drive in a straight line, uses an IMU to adjust the power.
/// @param rot_obj A rotation object which is a instance of PID to check if the robot is driving straight.
/// @param target_distance The target distance in inches.
/// @param kp Proportional constant.
/// @param ki Integral Constant.
/// @param kd Derivative Constant.
/// @param start_i The limiter for the intergral.
/// @param settle_time The ammount of time the robot has to be in a settle zone to be considered fully settled.
/// @param settle_error The ammount of displacement the robot has to be in to have the chance to be considered settled.
/// @param timeout The ammount of time for a given run.
void PID::drive(PID &rot_obj, double target_distance, double kp, double ki, double kd, double start_i, double settle_time, double settle_error, double timeout) {
    
    // Set values becuase the constructor is 👎
    this->kp = kp;
    this->ki = ki;
    this->kd = kd;
    this->start_i = start_i;
    this->settle_time = settle_time;
    this->settle_time = settle_error;
    this->timeout = timeout;

    // Gets the target direction, 1 if forward -1 if in reverse.
    direction = sgn(target_distance);

    // The target converted to ticks.
    target = target_distance * tick_constant;

    // The current heading of the robot in degrees.
    current_heading = imu_drive.get_heading();

    while(true) {
        // Calculates the power needed to output to the motors using the distance.
        double main_power = calculate(target, get_encoders());
        // Calculates the angle of the robot and makes sure the robot drives straight.
        double imu_adjustment_power = rot_obj.calculate(current_heading, imu_drive.get_heading());

        // Applys the power to the motors.
        drive_left_cata.move_voltage((main_power + imu_adjustment_power) * 1200 * direction);
        drive_right_cata.move_voltage((main_power - imu_adjustment_power) * 1200 * direction);

        // Checks the robot can be considered settled.
        if(is_settled()) {
            // Stop the robot.
            drive_left_cata.move_voltage(0);
            drive_right_cata.move_voltage(0);
            return;
        }
        pros::delay(10); // Always delayed by 10ms, in order to sync with the settle time thingy.
    }
}


/// @brief The main PID controller to turn. Uses an IMU.
/// @param angle The angle of the robot needs to turn to.
/// @param kp Proportional constant.
/// @param ki Integral Constant.
/// @param kd Derivative Constant.
/// @param start_i the limiter for the intergral.
/// @param settle_time The ammount of time the robot has to be in a settle zone to be considered fully settled.
/// @param settle_error The ammount of displacement the robot has to be in to have the chance to be considered settled.
/// @param timeout The ammount of time for a given run.
void PID::set_turning(double angle, double kp, double ki, double kd, double start_i, double settle_time, double settle_error, double timeout) {
    // Set PID values.
    this->kp = kp;
    this->ki = ki;
    this->kd = kd;
    this->start_i = start_i;
    this->settle_time = settle_time;
    this->settle_time = settle_error;
    this->timeout = timeout;
    
    
    while (true) {
        // Reset the direction.
        direction = 1;

        // get imu current sensing.
        target = imu_drive.get_heading();

        // get speed output.
        output = calculate(angle, target);
        
        // determine direction to turn.
        if(fabs(error) < 180)
            direction = -1;

        // Applys the power to the motors.
        drive_left_cata.move_voltage (output * 1200 * direction); 
        drive_right_cata.move_voltage(output * 1200 * direction);

        // Checks the robot can be considered settled.
        if(is_settled()) {
            drive_left_cata.move_voltage(0);
            drive_right_cata.move_voltage(0);
            return;
        }

        pros::delay(10); // Always delayed by 10ms, in order to sync with the settle time thingy.
    }
}



/// @brief Resets the values of lonely variables.
void PID::reset(void) {
    time_waiting        = 0;
    time_spent_running  = 0;
    accumulated_error   = 0;
    previous_error      = 0;
}




// // print hello world - youtube.com/@2915Z
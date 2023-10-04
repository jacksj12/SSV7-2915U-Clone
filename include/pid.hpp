#include "main.h"

#define M_PI		        3.14159265358979323846
#define tick_constant      27.779771885130824


/// @brief The PID class implements a Proportional-Integral-Derivative (PID) controller used for control systems.
///        It calculates the power to be applied to motors in order to achieve a desired target or maintain a specific orientation.
class PID{
    private:
        double target_ticks         = 0; // The target distance of inches converted to encoder ticks.
        double target               = 0; // The target either inches or degrees.
        double sensor_reading       = 0; // The current reading of the sensor.
        double error                = 0; // The current error of the robot from the target.
        double kp                   = 0; // Proportional constant.
        double ki                   = 0; // Integral Constant.
        double kd                   = 0; // Derivative Constant.
        double start_i              = 0; // The limiter for the intergral, if this value is less than the absolute value of error than it will add to accumulated error.
        double settle_error         = 0; // How far the robot can be away from the raw target and be considered at the right point. 
        double settle_time          = 0; // How long the robot can be away from the raw target granted that the robot is within the range of settle_error. In multiples of 10ms
        double timeout              = 0; // The ammount of time the robot should take to reach the target. In multiples of 10ms
        double accumulated_error    = 0; // The total ammount of error for a single run.
        double previous_error       = 0; // The last value of PID::error.
        double output               = 0; // The output to be applied to the motors.
        double time_waiting         = 0; // The total ammount of time settled in a position. 
        double time_spent_running   = 0; // The total ammount of time from start to the target.

        int16_t inital_heading     = 0;  // The current heading of the robot. So we don't have to reset the imu every time we need to use it.
        int8_t direction           = 1;  // The turning direction. Either 1 or -1.
        
        double get_encoders(void);
        double get_ticks(double inches);
        double calculate(double target, double sensor_reading);
        bool is_settled(void);
        void reset(void);
    public:
        void turn(double angle, double kp, double ki, double kd, double start_i, double settle_time, double settle_error, double timeout);
        void drive(PID &rot_obj, double target_distance, double kp, double ki, double kd, double start_i, double settle_time, double settle_error, double timeout);
        void ballance_pitch(double kp, double ki, double kd, double start_i, double settle_time, double settle_error, double timeout);
};


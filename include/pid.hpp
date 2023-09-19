#define M_PI		3.14159265358979323846

// type safe sgn (sign) function
// https://stackoverflow.com/a/4609795
template <typename T> int sgn(T val) { 
  return (T(0) < val) - (val < T(0)); 
}


double get_drive_encoders(void);
double get_ticks(double inches);
class PID{
    private:
        double target_ticks         = 0;
        double target_distance      = 0;
        double error                = 0;
        double kp                   = 0;
        double ki                   = 0;
        double kd                   = 0;
        double start_i              = 0;
        double settle_error         = 0;
        double settle_time          = 0;
        double timeout              = 0;
        double accumulated_error    = 0;
        double previous_error       = 0;
        double output               = 0;
        double time_waiting         = 0;
        double time_spent_running   = 0;


    public:
        /// @brief Consturctor for the PID.
        /// @param error 
        /// @param kp 
        /// @param ki 
        /// @param kd 
        /// @param starti 
        /// @param settle_time 
        /// @param timeout 
        PID(double error, double kp, double ki, double kd, double start_i, double settle_time, double timeout);
        PID(double error, double kp, double ki, double kd, double start_i);

        double calculate(double target_ticks, double sensor_reading);
        bool is_settled();

        void set_drive(double inches, double kp, double ki, double kd, double start_i, double settle_time, double timeout);
        void set_drive(double inches, double kp, double ki, double kd, double start_i);

        // Defined turning function for readability.
        void set_turning(double angle, double kp, double ki, double kd, double start_i, double settle_time, double timeout);
        void set_turning(double angle, double kp, double ki, double kd, double start_i);
};


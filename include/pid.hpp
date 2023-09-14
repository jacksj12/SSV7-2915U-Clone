class PID{
    private:
        double target_value;

        double current_heading;
        double sensor_reading;

        double error;
        double previous_error;

        double derivative;

        double speed;

        bool autonomous_end;
        bool rotation_finished;

    public:
        double kp;
        double kd;

        double last_kp;
        double last_kd;

        double get_PID(double targetValue, double sensorReading);
        double get_error(void);
        void turn_with_gains(double angle, double new_kp, double new_kd);
        void drive(double inches, double new_kp, double new_kd);
        double get_ticks(double inches);
        void reset(void);

};
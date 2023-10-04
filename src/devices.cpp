#include "main.h"


// Declare Devices Port Numbers.
//      Left Drive Ports.
#define motor_drive_1_port 13    // Front Left Drive Motor Port.
#define motor_drive_2_port 15    // Middle Front Drive Motor Port.
#define motor_drive_3_port 16    // Back Back Drive Motor Port.


//      Right Drive Ports.
#define motor_drive_5_port 3    // Front Right Drive Motor Port.
#define motor_drive_6_port 5    // Middle Front Drive Motor Port.
#define motor_drive_7_port 6    // Middle Back Drive Motor 


//      Cata -> drive PTO PORTS.
#define motor_drive_4_port 17    // Left PTO Motor Port.
#define motor_drive_8_port 7     // Right PTO Motor Port.

//      Solonoid Ports.
#define wing_left_port 'B'   // Left Pneumatic Wing Solonoid Port.
#define wing_right_port 'H'  // Right Pneumatic Wing Solonoid Port.
#define pto_cata_port 'C'    // Cata -> Drive solonoid Port

#define imu_drive_port 7    // IMU port for drive.

// Controllers
pros::Controller controller_main(CONTROLLER_MASTER);    // Master Controller.

// Left Drive Motors.
pros::Motor motor_drive_1(motor_drive_1_port,   false);     // Front Left Drive Motor.
pros::Motor motor_drive_2(motor_drive_2_port,   true );     // Middle front Left Drive Motor.
pros::Motor motor_drive_3(motor_drive_3_port,   false);     // back Left Drive Motor.

// Right Drive Motors.
pros::Motor motor_drive_5(motor_drive_5_port,   true );       //Front Right Drive Motor.
pros::Motor motor_drive_6(motor_drive_6_port,   false);       // Middle 1 Right Drive Motor.
pros::Motor motor_drive_7(motor_drive_7_port,   true );       // Middle 2 Right Drive Motor.

// PTO Motors
pros::Motor motor_drive_4(motor_drive_4_port,   false);       // Back PTO Left Drive Motor.
pros::Motor motor_drive_8(motor_drive_8_port,   true );       // Back PTO Right Drive Motor.

// Drive Motor Groups.
pros::Motor_Group drive_left_cata   ({motor_drive_1, motor_drive_2, motor_drive_3, motor_drive_4});     // Left Drive Motor Group with cata motors.
pros::Motor_Group drive_right_cata  ({motor_drive_5, motor_drive_6, motor_drive_7, motor_drive_8});     // Right Drive Motor Group with cata motors.

pros::Motor_Group drive_left        ({motor_drive_1, motor_drive_2, motor_drive_3});                    // Left Drive Motor Group 
pros::Motor_Group drive_right       ({motor_drive_5, motor_drive_6, motor_drive_7});                    // Right Drive Motor Group
// Solonoids
pros::ADIDigitalOut wing_left(wing_left_port, true);   // Left Pneumatic Wing Solonoid.
pros::ADIDigitalOut wing_right(wing_right_port, false);   // Right Pneumatic Wing Solonoid.
pros::ADIDigitalOut pto_cata(pto_cata_port, false);         // PTO 
// IMU
pros::Imu imu_drive(imu_drive_port);

// All V5 Devices connected goes here! 
int all_devices_ports [9] = 
    {
    motor_drive_1_port,
    motor_drive_2_port,
    motor_drive_3_port,
    motor_drive_5_port,
    motor_drive_6_port,
    motor_drive_7_port,
    motor_drive_4_port,
    motor_drive_8_port,
    imu_drive_port
    };
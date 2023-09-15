#include "main.h"


// Declare Devices Port Numbers.
//      Left Drive Ports.
#define motor_drive_1_port 14    // Front Left Drive Motor Port.
#define motor_drive_2_port 15    // Middle Front Drive Motor Port.
#define motor_drive_3_port 16    // Back Back Drive Motor Port.
#define motor_drive_4_port 17    //Front Right Drive Motor Port.

//      Right Drive Ports.
#define motor_drive_5_port 4    // Front Right Drive Motor Port.
#define motor_drive_6_port 5    // Middle Front Drive Motor Port.
#define motor_drive_7_port 6    // Middle Back Drive Motor 
#define motor_drive_8_port 7    // Back Right Drive Motor Port.

//      Solonoid 
#define wing_left_port 'A'   // Left Pneumatic Wing Solonoid Port.
#define wing_right_port 'H'  // Right Pneumatic Wing Solonoid Port.
// #define pto_cata_port 'C'    // Cata -> Drive solonoid Port

// #define imu_drive_port 7    // IMU port for drive.

// Controllers
pros::Controller controller_main(CONTROLLER_MASTER);    // Master Controller.

// Left Drive Motors.
pros::Motor motor_drive_1(13,   false);     // Front Left Drive Motor.
pros::Motor motor_drive_2(15,   true );     // Middle 1 Left Drive Motor.
pros::Motor motor_drive_3(16,   false);     // Middle 2 Left Drive Motor.
pros::Motor motor_drive_4(17,   false );      // Back Left Drive Motor.

// Right Drive Motors.
pros::Motor motor_drive_5(3, true );       //Front Right Drive Motor.
pros::Motor motor_drive_6(5, false   );       // Middle 1 Right Drive Motor.
pros::Motor motor_drive_7(6, true );       // Middle 2 Right Drive Motor.
pros::Motor motor_drive_8(7, true);       // Back Right Drive Motor.


// Drive Motor Groups.
pros::Motor_Group drive_left ({motor_drive_1, motor_drive_2, motor_drive_3, motor_drive_4});   // Left Drive Motor Group.
pros::Motor_Group drive_right({motor_drive_5, motor_drive_6, motor_drive_7, motor_drive_8});   // Right Drive Motor Group.


// Solonoids
pros::ADIDigitalOut wing_left(wing_left_port, true);   // Left Pneumatic Wing Solonoid.
pros::ADIDigitalOut wing_right(wing_right_port, false);   // Right Pneumatic Wing Solonoid.
// pros::ADIDigitalOut pto_cata(pto_cata_port, false);
// IMU
// pros::Imu imu_drive(imu_drive_port);

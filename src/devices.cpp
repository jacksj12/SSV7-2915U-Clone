#include "main.h"


// Declare Devices Port Numbers.
//      Left Drive Ports.
#define motor_drive_1_port 1    // Front Left Drive Motor Port.
#define motor_drive_2_port 2    // Middle Left Drive Motor Port.
#define motor_drive_3_port 3    // Back Left Drive Motor Port.
//      Right Drive Ports.
#define motor_drive_4_port 4    //Front Right Drive Motor Port.
#define motor_drive_5_port 5    // Middle Right Drive Motor Port.
#define motor_drive_6_port 6    // Back Right Drive Motor Port.

//      Solonoid 
#define wing_left_port 'A'   // Left Pneumatic Wing Solonoid Port.
#define wing_right_port 'B'   // Right Pneumatic Wing Solonoid Port.

// Controllers
pros::Controller controller_main(CONTROLLER_MASTER);    // Master Controller.

// Left Drive Motors.
pros::Motor motor_drive_1(motor_drive_1_port,   false);    // Front Left Drive Motor.
pros::Motor motor_drive_2(motor_drive_2_port,   true );     // Middle Left Drive Motor.
pros::Motor motor_drive_3(motor_drive_3_port,   false);     // Back Left Drive Motor.

// Right Drive Motors.
pros::Motor motor_drive_4(motor_drive_4_port, true );    //Front Right Drive Motor.
pros::Motor motor_drive_5(motor_drive_5_port, false);   // Middle Right Drive Motor.
pros::Motor motor_drive_6(motor_drive_6_port, true );   // Back Right Drive Motor.


// Drive Motor Groups.
pros::Motor_Group drive_left ({motor_drive_1, motor_drive_2, motor_drive_3});   // Left Drive Motor Group.
pros::Motor_Group drive_right({motor_drive_4, motor_drive_5, motor_drive_6});   // Right Drive Motor Group.


// Solonoids
pros::ADIDigitalOut wing_left(wing_left_port, false);   // Left Pneumatic Wing Solonoid.
pros::ADIDigitalOut wing_right(wing_right_port, false);   // Right Pneumatic Wing Solonoid.



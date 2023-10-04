#pragma once // Avoid multiple header links.
#include "main.h"

// Ports
// Left Drive ports.
extern int motor_drive_1_port;
extern int motor_drive_2_port;
extern int motor_drive_3_port;

// Right Drive ports.
extern int motor_drive_4_port;
extern int motor_drive_5_port;
extern int motor_drive_6_port;

// Pneumatic solonoid ports.
extern int wing_left_port;
extern int wing_left_port;

extern int imu_drive_port;
// V5 Master controller 
extern pros::Controller controller_main;

// V5 Motor decleration
extern pros::Motor motor_drive_1;
extern pros::Motor motor_drive_2;
extern pros::Motor motor_drive_3;
extern pros::Motor motor_drive_4;
extern pros::Motor motor_drive_5;
extern pros::Motor motor_drive_6;
extern pros::Motor motor_drive_7;
extern pros::Motor motor_drive_8;

// Drive Motor Group Decleration
extern pros::Motor_Group drive_left;
extern pros::Motor_Group drive_right;

extern pros::Motor_Group drive_left_cata;
extern pros::Motor_Group drive_right_cata;

// Solonoid declaration.
extern pros::ADIDigitalOut wing_left;
extern pros::ADIDigitalOut wing_right;
extern pros::ADIDigitalOut pto_cata;

extern pros::Imu imu_drive;

extern int all_devices_ports;

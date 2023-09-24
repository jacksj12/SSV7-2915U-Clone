import numpy
import os
MAX_THERSHOLD: int = 127
maximum: int = 12000
MAX_SCALED_JOYSTICK: int = 127
VOLTAGE_DRIVE: float = 12000.0 / 127.0

def squared_scaling(joystick_input: int) -> float:
    return pow(joystick_input, 2) / maximum * numpy.sign(joystick_input)

def cubic_scaler(joystick_input: int) -> float: 
    return pow(joystick_input / 127, 3) * MAX_THERSHOLD

# 1 value increases mV by 94.4881889763783 FLI!
while True:
    
    joystick_input_1: str = input("Joystick 1\t")
    # To fix my OCD.
    if joystick_input_1 == "cls":
        os.system("cls")
        continue

    joystick_input_2: str = input("Joystick 2\t")
    
    joystick_1_check: bool = joystick_input_1.isdigit() or joystick_input_1.startswith('-') and joystick_input_1[1:].isdigit()
    joystick_2_check: bool = joystick_input_2.isdigit() or joystick_input_2.startswith('-') and joystick_input_2[1:].isdigit()

    if joystick_1_check and joystick_2_check:
        
        joystick_1_value: int = int(joystick_input_1)
        joystick_2_value: int = int(joystick_input_2) / 2


        # numerator = joystick_value-(-127) 
        # denomorator = 127 - (-127)
        # scaled_milivolts = -12000 + (numerator/ denomorator) * 24000
        # print(f"milivolts  {scaled_milivolts}")

        # drive_left_voltage = (joystick_1_value  + joystick_2_value) * VOLTAGE_DRIVE
        # drive_right_voltage = (joystick_1_value  - joystick_2_value) * VOLTAGE_DRIVE
        # print(f"Drive Voltage {drive_left_voltage}\t {drive_right_voltage}")


        # cubic_scaling: float = pow(joystick_value / 100, 3) * MAX_THERSHOLD
        # print(f"Cubic scalling {cubic_scaling}")

        drive_left_voltage =  (joystick_1_value + joystick_2_value)
        drive_right_voltage = (joystick_1_value - joystick_2_value)

        # if the value overflows, scale it so that the user can still turn. May cause unexpected results.
        if (abs(drive_left_voltage) > 127):
            drive_left_voltage = joystick_1_value / 2 + joystick_2_value
        
        # if the value overflows, scale it so that the user can still turn. May cause unexpected results.
        if abs(drive_right_voltage > 127):
            drive_right_voltage = joystick_1_value / 2 - joystick_2_value


        print(f"Drive Voltage {drive_left_voltage}\t {drive_right_voltage}")

        # cubed_joystick_1: float = cubic_scaler(joystick_1_value)
        # cubed_joystick_2: float = cubic_scaler(joystick_2_value)
        # print(f"cubed scalling {cubed_joystick_1}\t {cubed_joystick_2}")


        # left: float = squared_scaling(joystick_1_value + joystick_2_value)
        # right: float = squared_scaling(joystick_1_value - joystick_2_value)
        # print(f"Drive squared {left}\t {right}")

    continue


import numpy

MAX_THERSHOLD: int = 127
maximum: int = 12000
MAX_SCALED_JOYSTICK: int = 127


# 1 value increases mV by 94.4881889763783 FLI!
while True:
    joystick_input: str = input("Joystick\t")
    

    if joystick_input.isdigit() or joystick_input.startswith('-') and joystick_input[1:].isdigit():
        
        joystick_value: int = int(joystick_input)

        # FIXME: Make float?
        joystick_scaled: float = joystick_value / 127.0 * 100
        print(f"Joystick scalled {joystick_scaled}")

        cubic_scaling: float = pow(joystick_value / 100, 3) * MAX_THERSHOLD
        print(f"Cubic scalling {cubic_scaling}")

        squared_scaling: float = pow(joystick_value, 2) / maximum * numpy.sign(joystick_value)
        print(f"squared scalling {squared_scaling}")

        
        numerator = joystick_value-(-127) 
        denomorator = 127 - (-127)
        scaled_milivolts = -12000 + (numerator/ denomorator) * 24000
        print(f"milivolts  {scaled_milivolts}")
    continue


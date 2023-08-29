MAX_THERSHOLD: int = 100

while True:
    joystick_input: str = input("Joystick\t")
    print(joystick_input.isalnum())

    if joystick_input.isdigit() or joystick_input.startswith('-') and joystick_input[1:].isdigit():
        
        joystick_value: int = int(joystick_input)

        # FIXME: Make float?
        joystick_scaled: float = joystick_value / 127.0 * 100
        print(f"Joystick scalled {joystick_scaled}")

        cubic_scaling: float = pow(joystick_value / 100, 3) * MAX_THERSHOLD
        print(f"Cubic scalling {cubic_scaling}")
    continue


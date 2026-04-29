#!/usr/bin/env python3

def input_temperature(temp_str: str) -> int:
    return int(temp_str)


def test_temperature() -> None: 
    print( "=== Garden Temperature ===")
    number = "25"
    string = "abc"
    print(f"\nInput data is '{number}'")
    try:
        temp = input_temperature(number)
        print(f"Temperature is now {temp}°C")
    except ValueError as e:
        print(f"Caught input_temperature error: '{e}'")

    print(f"\nInput data is '{string}'")
    try:
        temp = input_temperature(string)
        print(f"Temperature is now {temp}°C")
    except ValueError as e:
        print(f"Caught input_temperature error: '{e}'")

    print("\nAll tests completed - program didn't crash")


if __name__ == "__main__":
    test_temperature()

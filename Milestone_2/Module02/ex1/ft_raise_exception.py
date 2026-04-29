#!/usr/bin/env python3

def input_temperature(temp_str: str) -> int:
    temp = int(temp_str)
    if temp < 0:
        raise ValueError(f"{temp}  is too cold for plants (min 0°C)")
    elif temp > 40:
        raise ValueError(f"{temp}  is too hot for plants (max 40°C)")
    return temp


def test_temperature() -> None:
    print("=== Garden Temperature ===")
    values = ["25", "abc", "100", "-50"]
    for value in values:
        print(f"\nInput data is {value!r}")
        try:
            tepm = input_temperature(value)
            print(f"Temperature is now {tepm}°C")
        except ValueError as e:
            print(f"Caught input_temperature error: {e}")
    print("\nAll tests completed - program didn't crash!")


if __name__ == "__main__":
    test_temperature()

#!/usr/bin/env python3

def garden_operations(operation_number: int) -> int:
    if operation_number == 0:
        int("abc")
    elif operation_number == 1:
        10 / 0
    elif operation_number == 2:
        open("garden_not_found.txt", "r")
    elif operation_number == 3:
        "hello" + 2
    else:
        return int(operation_number)


def test_error_types() -> None:
    print("=== Garden Error Types Demo ===")
    for value in range(5):
        print(f"Testing operation {value}...")
        try:
            garden_operations(value)
            print("Operation completed successfully")
        except ValueError as e:
            print(f"Caught ValueErro: {e}")

        except ZeroDivisionError as e:
            print(f"Caught ValueErro: {e}")

        except FileNotFoundError as e:
            print(f"Caught ValueErro: {e}")

        except TypeError as e:
            print(f"Caught ValueErro: {e}")
    print("\nAll error types tested successfully!")


if __name__ == "__main__":
    test_error_types()

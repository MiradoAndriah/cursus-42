#!/usr/bin/env python3

class GardenError(Exception):
    def __init__(self, message: str = "Unknown garden error") -> None:
        super().__init__(message)


class PlantError(GardenError):
    def __init__(self, message: str = "Unknown plant error") -> None:
        super().__init__(message)


class WaterError(GardenError):
    def __init__(self, message: str = "Unknown watering error"):
        super().__init__(message)


def check_plant() -> None:
    raise PlantError("The tomato plant is wilting!")


def check_water() -> None:
    raise WaterError("Not enough water in the tank!")


def test_garden() -> None:
    print("=== Custom Garden Errors Demo ===\n")
    print("Testing PlantError...")
    try:
        check_plant()
    except PlantError as e:
        print(f"Caught WaterError: {e}\n")
    print("Testing WaterError...")
    try:
        check_water()
    except WaterError as e:
        print(f"Caught WaterError: {e}\n")
    functions = [check_plant, check_water]
    print("Testing catching all garden errors...")
    for function in functions:
        try:
            function()
        except GardenError as e:
            print(f"Caught GardenError: {e}")
    print("\nAll custom error types work correctly!")


if __name__ == "__main__":
    test_garden()

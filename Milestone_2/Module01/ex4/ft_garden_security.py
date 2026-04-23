#!/usr/bin/env python3

class Plant:
    def __init__(self, name: str, height: float, age: int):
        self.name = name
        if height < 0:
            print(f"{self.name}: Error, height can't be negative")
            self._height = 0.0
        else:
            self._height = height
        if age < 0:
            print(f"{self.name}: Error, age can't be negative")
            self._age = 0
        else:
            self._age = age

    def set_height(self, height: float) -> None:
        if height < 0:
            print(f"{self.name}: Error, height can't be negative")
            print("Height update rejected")
        else:
            self._height = height
            print(f"Height updated: {height}cm")

    def set_age(self, age: int) -> None:
        if age < 0:
            print(f"{self.name}: Error, age can't be negative")
            print("Age update rejected")
        else:
            self._age = age
            print(f"Age updated: {age} days")

    def get_height(self) -> float:
        return (self._height)

    def get_age(self) -> float:
        return (self._age)

    def show(self) -> None:
        print(f"{self.name}: {self._height:.1f}cm, {self._age} days old")


if __name__ == "__main__":
    plant = Plant("Rose", 15, 10)
    print("=== Garden Security System ===")
    print("Plant created: ", end="")
    plant.show()
    print("")
    plant.set_height(25)
    plant.set_age(30)
    print("")
    plant.set_height(-5)
    plant.set_age(-50)
    print("")
    print("Current state: ", end="")
    plant.show()

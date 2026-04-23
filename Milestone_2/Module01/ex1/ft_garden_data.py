#!/usr/bin/env python3

class Plant:
    def __init__(self, name: str, height: int, age: int):
        self.name = name
        self.height = height
        self.ages = age

    def show(self) -> None:
        print(f"{self.name}: {self.height}cm, {self.ages} days old")


if __name__ == "__main__":
    print("=== Garden Plant Registry ===")
    plants = [
        Plant("Rose", 25, 30),
        Plant("Sunflower", 80, 45),
        Plant("Cactus", 15, 120)]
    for plant in plants:
        plant.show()

#!/usr/bin/env python3

class Plant:
    def __init__(self, name: str, height: float, age: int):
        self.name = name
        self.height = height
        self.ages = age

    def show(self) -> None:
        print(f"{self.name}: {self.height}cm, {self.ages} days old")

    def grow(self) -> None:
        self.height = round(self.height + 0.8, 1)

    def age(self) -> None:
        self.ages += 1


if __name__ == "__main__":
    plant1 = Plant("Rose", 25.0, 30)
    print("=== Garden Plant Growth ===")
    plant1.show()
    h_init = plant1.height

    for jour in range(1, 8):
        print("=== Day ", jour, "===")
        plant1.grow()
        plant1.age()
        plant1.show()
    print("Growth this week: ", round(plant1.height - h_init, 1), "cm")

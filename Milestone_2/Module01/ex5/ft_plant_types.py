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


class Flower(Plant):
    def __init__(self, name: str, height: float, age: int, color: str):
        super().__init__(name, height, age)
        self.color = color
        self.bloomed = False

    def bloom(self) -> None:
        self.bloomed = True

    def show(self) -> None:
        super().show()
        print(f" color: {self.color}")
        if (self.bloomed):
            print(f" {self.name} is blooming beautifully!")
        else:
            print(f" {self.name} has not bloomed yet")


class Tree(Plant):
    def __init__(
            self, name: str,
            height: float,
            age: int,
            trunk_diameter: float
            ):
        super().__init__(name, height, age)
        self.trunk_diameter = trunk_diameter
        self.produce = False

    def produce_shade(self) -> None:
        self.produce = True

    def show(self) -> None:
        super().show()


class Vegetable(Plant):
    def __init__(
            self, name: str,
            height: float,
            age: int,
            harvest_season: str,
            nutritional_value: int = 0):
        super().__init__(name, height, age)
        self.season = harvest_season
        self.nutrition = nutritional_value

    def grow(self) -> None:
        self.height = round(self.height + 2.1, 1)
        self.nutrition += 1

    def age(self) -> None:
        super().age()

    def show(self) -> None:
        super().show()
        print(f" Harvest season: {self.season}")
        print(f" Nutritional value: {self.nutrition}")


if __name__ == "__main__":
    print("=== Garden Plant Types ===")
    print("=== Flower")
    flower = Flower("Rose", 15.0, 10, "red")
    flower.show()
    print("[asking the rose to bloom]")
    flower.bloom()
    flower.show()
    print("")

    print("=== Tree")
    tree = Tree("Oak", 200.0, 365, 5.0)
    tree.show()
    print(f"Trunk diameter: {tree.trunk_diameter}cm")
    print("[asking the oak to produce shade]")
    tree.produce_shade()
    if tree.produce:
        print(
            f"Tree {tree.name} now produces a shade of "
            f"{tree.height}cm long and {tree.trunk_diameter}cm wide."
            )
    print("")

    print("=== Vegetable")
    vegetable = Vegetable("Tomato", 5.0, 10, "April")
    vegetable.show()
    print("[make tomato grow and age for 20 days]")
    for i in range(0, 20):
        vegetable.grow()
        vegetable.age()
    vegetable.show()

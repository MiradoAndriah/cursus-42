#!/usr/bin/env python3

class Plant:
    class Stats:
        def __init__(self):
            self._grow_count = 0
            self._age_count = 0
            self._show_count = 0

        def show(self):
            print(f"Stats: {self._grow_count} grow, ", end="")
            print(f"{self._age_count} age, {self._show_count} show")

    def __init__(self, name: str, height: float, age: int):
        self.name = name
        self.height = height
        self.ages = age
        self.stats = Plant.Stats()

    @staticmethod
    def check_year_old(age: int) -> bool:
        return age > 365

    @classmethod
    def anonymous(cls):
        return cls(name="Unknown plant", height=0.0, age=0)

    def grow(self) -> None:
        self.height = round(self.height + 0.8, 1)
        self.stats._grow_count += 1

    def age(self) -> None:
        self.ages += 1
        self.stats._age_count += 1

    def show(self):
        print(f"{self.name}: {self.height:.1f}cm, {self.ages} days old")
        self.stats._show_count += 1


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

    def grow(self):
        self.height = round(self.height + 8.0)


class Seed(Flower):
    def __init__(
            self,
            name: str,
            height: float,
            age: int,
            color: str,
            number_of_seed: int
    ):
        super().__init__(name, height, age, color)
        self.number_of_seed = number_of_seed

    def show(self):
        super().show()
        print(f" Seeds: {self.number_of_seed}")

    def grow(self):
        self.height = round(self.height + 30.0)
        self.stats._grow_count += 1

    def age(self):
        self.ages += 20
        self.stats._age_count += 1


class Tree(Plant):
    class Stats(Plant.Stats):
        def __init__(self):
            super().__init__()
            self.count_shade = 0

        def show(self):
            super().show()
            print(f" {self.count_shade} shade")

    def __init__(
            self, name: str,
            height: float,
            age: int,
            trunk_diameter: float
            ):
        super().__init__(name, height, age)
        self.trunk_diameter = trunk_diameter
        self.produce = False
        self.stats: Tree.Stats = Tree.Stats()

    def produce_shade(self) -> None:
        self.produce = True
        self.stats.count_shade += 1

    def show(self) -> None:
        super().show()
        print(f" Trunk diameter: {self.trunk_diameter}")


def display_static(plant: Plant) -> None:
    plant.stats.show()


if __name__ == "__main__":
    print("=== Garden statistics ===")
    print("=== Check year-old")
    print(f"Is 30 days more than a year? -> {Plant.check_year_old(30)}")
    print(f"Is 400 days more than a year? -> {Plant.check_year_old(400)}\n")
    print("=== Flower")
    rose = Flower("Rose", 15.0, 10, "red")
    rose.show()
    print("[statistics for Rose]")
    display_static(rose)
    print("[asking the rose to grow and bloom]")
    rose.grow()
    rose.bloom()
    rose.show()
    print("[statistics for Rose]")
    display_static(rose)
    print("")
    print("=== Tree")
    oak = Tree("Oak", 200.0, 365, 5.0)
    oak.show()
    print("[statistics for Oak]")
    display_static(oak)
    print("[asking the oak to produce shade]")
    oak.produce_shade()
    if (oak.produce):
        print(f"Tree {oak.name} now produces a shade of ", end="")
        print(f"{oak.height} long and {oak.trunk_diameter} wide.")
    print("[statistics for Oak]")
    display_static(oak)
    print("")
    print("=== Seed")
    Sunflower = Seed("Sunflower", 80.0, 45, "yellow", 0)
    Sunflower.show()
    print("[make sunflower grow, age and bloom]")
    Sunflower.grow()
    Sunflower.bloom()
    Sunflower.age()
    Sunflower.number_of_seed = 42
    Sunflower.show()
    print("[statistics for Sunflower]")
    display_static(Sunflower)
    print("")
    print("=== Anonymous")
    anonymous = Plant.anonymous()
    anonymous.show()
    print("[statistics for Unknown plant]")
    display_static(anonymous)

from abc import ABC, abstractmethod
from ex0.creatures import Creature


class HealCapability(ABC):
    @abstractmethod
    def heal(self) -> str:
        pass


class Sproutling(Creature, HealCapability):
    def __init__(self) -> None:
        super().__init__("Sproutling", "Grass")

    def attack(self) -> str:
        return (f"{self.name} uses Vine Whip!")

    def describe(self) -> str:
        return super().describe()

    def heal(self) -> str:
        return (f"{self.name} heals itself for a small amount")


class Bloomelle(Creature, HealCapability):
    def __init__(self) -> None:
        super().__init__("Bloomelle", "Grass/Fairy")

    def attack(self) -> str:
        return (f"{self.name} uses Petal Dance!")

    def describe(self) -> str:
        return super().describe()

    def heal(self) -> str:
        return (f"{self.name} heals itself and others for a large amount")

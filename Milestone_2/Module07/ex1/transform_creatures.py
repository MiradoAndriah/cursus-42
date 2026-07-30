from abc import ABC, abstractmethod
from ex0.creatures import Creature


class TransformCapability(ABC):
    def __init__(self, transformed: bool = False):
        self.transformed = transformed

    @abstractmethod
    def transform(self) -> str:
        pass

    @abstractmethod
    def revert(self) -> str:
        pass


class Shiftling(Creature, TransformCapability):
    def __init__(self) -> None:
        Creature.__init__(self, "Shiftling", "Normal")
        TransformCapability.__init__(self)

    def attack(self) -> str:
        if self.transformed:
            return (f"{self.name} performs a boosted strike!")
        return (f"{self.name}  attacks normally.")

    def describe(self) -> str:
        return super().describe()

    def transform(self) -> str:
        self.transformed = True
        return (f"{self.name} shifts into a sharper form!")

    def revert(self) -> str:
        return (f"{self.name} returns to normal")


class Morphagon(Creature, TransformCapability):
    def __init__(self) -> None:
        Creature.__init__(self, "Morphagon", "Normal/Dragon")
        TransformCapability.__init__(self)

    def attack(self) -> str:
        if self.transformed:
            return (f"{self.name} unleashes a devastating morph strike!")
        return (f"{self.name}  attacks normally.")

    def describe(self) -> str:
        return super().describe()

    def transform(self) -> str:
        self.transformed = True
        return (f"{self.name} morphs into a dragonic battle form!")

    def revert(self) -> str:
        return (f"{self.name} stabilizes its form.")

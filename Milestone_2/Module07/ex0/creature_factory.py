from abc import ABC, abstractmethod
from .creatures import Creature, Flameling, Pyrodon, Aquabub, Torragon


class CreatureFactory(ABC):
    @abstractmethod
    def create_base(self) -> Creature:
        pass

    @abstractmethod
    def create_evolved(self) -> Creature:
        pass


class FlameFactory(CreatureFactory):
    def create_base(self) -> Creature:
        flameling = Flameling()
        return flameling

    def create_evolved(self) -> Creature:
        pyrodon = Pyrodon()
        return pyrodon


class AquaFactory(CreatureFactory):
    def create_base(self) -> Creature:
        aquabub = Aquabub()
        return aquabub

    def create_evolved(self) -> Creature:
        torragon = Torragon()
        return torragon

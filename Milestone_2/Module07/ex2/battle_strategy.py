from abc import ABC, abstractmethod
from ex0.creatures import Creature
from ex1.transform_creatures import TransformCapability
from ex1.heal_creatures import HealCapability


class InvalidStrategyError(Exception):
    pass


class BattleStrategy(ABC):
    @abstractmethod
    def is_valid(self, creature: Creature) -> bool:
        pass

    @abstractmethod
    def act(self, creature: Creature, opponent: Creature) -> None:
        pass

    def check_valid(self, creature: Creature) -> None:
        if self.is_valid(creature) is False:
            strategy_name = type(self).__name__.replace("Strategy", "").lower()
            raise InvalidStrategyError(
                f"Invalid Creature '{creature.name}' "
                f"for this {strategy_name} strategy"
                )


class NormalStrategy(BattleStrategy):
    def is_valid(self, creature: Creature) -> bool:
        return isinstance(creature, Creature)

    def act(self, creature: Creature, opponent: Creature) -> None:
        self.check_valid(creature)
        print(creature.attack())


class AggressiveStrategy(BattleStrategy):
    def is_valid(self, creature: Creature) -> bool:
        return (
            isinstance(creature, Creature)
            and isinstance(creature, TransformCapability)
            )

    def act(self, creature: Creature, opponent: Creature) -> None:
        self.check_valid(creature)
        assert isinstance(creature, TransformCapability)
        print(creature.transform())
        print(creature.attack())
        print(creature.revert())


class DefensiveStrategy(BattleStrategy):
    def is_valid(self, creature: Creature) -> bool:
        return (
            isinstance(creature, Creature) and
            isinstance(creature, HealCapability)
        )

    def act(self, creature: Creature, opponent: Creature) -> None:
        assert isinstance(creature, HealCapability)
        self.check_valid(creature)
        print(creature.attack())
        print(creature.heal())

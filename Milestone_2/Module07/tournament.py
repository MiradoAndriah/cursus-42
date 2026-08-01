from typing import List, Tuple
from ex0 import CreatureFactory, FlameFactory, AquaFactory
from ex1 import HealingCreatureFactory, TransformCreatureFactory
from ex2 import (
    BattleStrategy,
    NormalStrategy,
    AggressiveStrategy,
    DefensiveStrategy,
    InvalidStrategyError,
)

Opponent = Tuple[CreatureFactory, BattleStrategy]


def battle(opponents: List[Opponent]) -> None:
    print("*** Tournament ***")
    print(f"{len(opponents)} opponents involved")

    for i in range(len(opponents)):
        for j in range(i + 1, len(opponents)):
            factory_a, strategy_a = opponents[i]
            factory_b, strategy_b = opponents[j]

            creature_a = factory_a.create_base()
            creature_b = factory_b.create_base()

            print("* Battle *")
            print(creature_a.describe())
            print(" vs.")
            print(creature_b.describe())
            print(" now fight!")

            try:
                strategy_a.act(creature_a, creature_b)
                strategy_b.act(creature_b, creature_a)
            except InvalidStrategyError as e:
                print(f"Battle error, aborting tournament: {e}")
                return


class Tournament:
    def __init__(self) -> None:
        self.rank = -1

    def run(
            self, label: str, combatants: str,
            opponents: List[Opponent]
            ) -> None:
        self.rank += 1
        print(f"Tournament {self.rank} ({label})")
        print(f" [ {combatants} ]")
        battle(opponents)
        print()


if __name__ == "__main__":
    tournament = Tournament()
    normal = NormalStrategy()
    aggressive = AggressiveStrategy()
    defensive = DefensiveStrategy()

    tournament.run(
        "basic",
        "(Flameling+Normal), (Healing+Defensive)",
        [
            (FlameFactory(), normal),
            (HealingCreatureFactory(), defensive),
        ],
    )

    tournament.run(
        "error",
        "(Flameling+Aggressive), (Healing+Defensive)",
        [
            (FlameFactory(), aggressive),
            (HealingCreatureFactory(), defensive),
        ],
    )

    tournament.run(
        "multiple",
        "(Aquabub+Normal), (Healing+Defensive), (Transform+Aggressive)",
        [
            (AquaFactory(), normal),
            (HealingCreatureFactory(), defensive),
            (TransformCreatureFactory(), aggressive),
        ],
    )

#!/usr/bin/env python3
import random

ACHIEVEMENTS_LIST = [
    "First Steps", "Boss Slayer", "Speed Runner", "Untouchable",
    "Collector Supreme", "World Savior", "Master Explorer", "Strategist",
    "Crafting Genius", "Survivor", "Sharp Mind", "Treasure Hunter",
    "Unstoppable", "Hidden Path Finder"
    ]


def gen_player_achievements() -> set[str]:
    k = random.randint(5, 10)
    selection = random.sample(ACHIEVEMENTS_LIST, k)
    return set(selection)


if __name__ == "__main__":
    players = ["Alice", "Bob", "Charlie", "Dylan"]
    liste = []
    print("=== Achievement Tracker System ===\n")

    for player in players:
        achivements = gen_player_achievements()
        liste += [(player, achivements)]
        print(f"Player {player}: {achivements}")
    print()

    all_achievements = set.union(*[value[1] for value in liste])
    print(f"All distinct achievements: {all_achievements}\n")
    common = set.intersection(*[value[1] for value in liste])
    print(f"Common achievements: {common}\n")

    for name, value in liste:
        other_set = []
        for player, achivement in liste:
            if name != player:
                other_set += [achivement]
        only = value.difference(*other_set)
        print(f"Only {name} has: {only}")
    print()

    for name, value in liste:
        missing = all_achievements.difference(value)
        print(f"{name} is missing: {missing}")

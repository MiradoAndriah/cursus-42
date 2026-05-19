#!/usr/bin/env python3
import random


def main() -> None:
    init_lisy = [
        'Alice', 'bob',
        'Charlie', 'dylan',
        'Emma', 'Gregory',
        'john', 'kevin', 'Liam'
        ]
    print(f"Initial list of players: {init_lisy}")

    comprehension1 = [name.capitalize() for name in init_lisy]
    print(f"New list with all names capitalized: {comprehension1}")

    comprehension2 = [name for name in init_lisy if name[0].isupper()]
    print(f"New list of capitalized names only: {comprehension2}\n")

    score_dict = {name: random.randint(0, 999) for name in comprehension1}
    print(f"Score dict: {score_dict}")

    score_avarage = round((sum(score_dict.values()) / len(score_dict)), 2)
    print(f"Score average is {score_avarage}")

    hight_score = {k: n for k, n in score_dict.items() if n > score_avarage}
    print(f"High scores: {hight_score}")


if __name__ == "__main__":
    print("=== Game Data Alchemist ===\n")
    main()

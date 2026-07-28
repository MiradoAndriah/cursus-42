from ..elements import create_air
from ..potions import strength_potion
from elements import create_fire


def lead_to_gold() -> str:
    return (
        "Recipe transmuting Lead to Gold: brew "
        f"'{create_air()}' and '{strength_potion()}' mixed with "
        f"'{create_fire()}'"
    )

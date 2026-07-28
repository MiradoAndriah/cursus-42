from .dark_spellbook import dark_spell_allowed_ingredients


def validate_ingredients(ingredients: str) -> str:
    allowed = dark_spell_allowed_ingredients()
    lower_ingredien = ingredients.lower()
    for element in allowed:
        if element in lower_ingredien:
            return (f"{ingredients} - VALID")
    return (f"{ingredients} - INVALID")

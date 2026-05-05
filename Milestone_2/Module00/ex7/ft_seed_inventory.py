def ft_seed_inventory(seed_type: str, nb: int, quantity: str) -> None:
    seed = seed_type.capitalize()
    if quantity == "packets":
        print(seed, "seeds:", str(nb), quantity, "available")
    elif quantity == "grams":
        print(seed, "seeds:", str(nb), quantity, "total")
    elif quantity == "area":
        print(seed, "seeds:", str(nb), quantity, "square meters")

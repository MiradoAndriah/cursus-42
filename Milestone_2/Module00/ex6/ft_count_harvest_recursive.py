def day(start: int, end: int) -> None:
    if start > end:
        return
    print("Day ", start)
    day(start + 1, end)


def ft_count_harvest_recursive() -> None:
    end = int(input("Days until harvest: "))
    day(1, end)
    print("Harvest time!")

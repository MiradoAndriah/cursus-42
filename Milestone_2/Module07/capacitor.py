from ex1 import HealingCreatureFactory, TransformCreatureFactory


def testing_heal() -> None:
    print("Testing Creature with healing capability")

    print(" base:")
    heal_a = HealingCreatureFactory()
    base = heal_a.create_base()
    print(base.describe())
    print(base.attack())
    print(base.heal())

    print(" evolved:")
    heal_b = HealingCreatureFactory()
    evolue = heal_b.create_evolved()
    print(evolue.describe())
    print(evolue.attack())
    print(evolue.heal())

    print()


def testin_transform() -> None:
    print("Testing Creature with transform capability")

    print(" base:")
    transform_a = TransformCreatureFactory()
    base = transform_a.create_base()
    print(base.describe())
    print(base.attack())
    print(base.transform())
    print(base.attack())
    print(base.revert())

    print(" evolved:")
    transform_b = TransformCreatureFactory()
    evolue = transform_b.create_evolved()
    print(evolue.describe())
    print(evolue.attack())
    print(evolue.transform())
    print(evolue.attack())
    print(evolue.revert())


if __name__ == "__main__":
    testing_heal()
    testin_transform()

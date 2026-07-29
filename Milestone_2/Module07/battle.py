from ex0 import CreatureFactory, FlameFactory, AquaFactory


def battle(factory_a: CreatureFactory, factory_b: CreatureFactory) -> None:
    creature_a = factory_a.create_base()
    creature_b = factory_b.create_base()
    print("Testing battle")
    print(f"{creature_a.describe()}\n vs.\n{creature_b.describe()}\n fight!")

    print(creature_a.attack())
    print(creature_b.attack())


def Testing_factory(factory: CreatureFactory) -> None:
    print("Testing factory")
    base = factory.create_base()
    evolue = factory.create_evolved()
    print(base.describe())
    print(base.attack())
    print(evolue.describe())
    print(evolue.attack())
    print()


if __name__ == "__main__":
    flame = FlameFactory()
    aqua = AquaFactory()
    Testing_factory(flame)
    Testing_factory(aqua)
    battle(flame, aqua)

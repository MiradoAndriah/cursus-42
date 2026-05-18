#!/usr/bin/env python3
import random
import typing


def gen_event() -> typing.Generator[tuple[str, str], None, None]:
    players = ["alice", "bob", "charlie", "dylan"]
    actions = [
        "run", "eat",
        "sleep", "grab",
        "move", "climb",
        "swim", "release", "use"
        ]
    while True:
        name = random.choice(players)
        action = random.choice(actions)
        yield (name, action)


def consume_event(liste: list[tuple[str, str]]) -> typing.Generator[tuple[str, str], None, None]:
    while liste:
        list_remain = random.choice(liste)
        liste.remove(list_remain)
        yield list_remain


if __name__ == "__main__":
    gen = gen_event()
    for i in range(1000):
        event = next(gen)
        print(f"Event {i}: Player {event[0]} did {event[1]}")
    event_list = []
    for i in range(10):
        event_list += [next(gen)]
    print(f"Built list of 10 events: {event_list}")

    list_remain = consume_event(event_list)
    for event in list_remain:
        print(f"Got event from list: {event}")
        print(f"Remains in list: {event_list}")

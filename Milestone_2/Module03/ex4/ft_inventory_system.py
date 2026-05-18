#!/usr/bin/env python3
import sys

if __name__ == "__main__":
    print("=== Inventory System Analysis ===")
    params = sys.argv[1:]
    inventory = {}
    for param in params:
        spliter = param.split(":")
        if len(spliter) != 2:
            print(f"Error - invalid parameter {param!r}")
        elif spliter[0] in inventory:
            print(f"Redundant item {spliter[0]!r} - discarding")
        else:
            try:
                inventory[spliter[0]] = int(spliter[1])
            except ValueError as e:
                print(f"Quantity error for {spliter[0]!r}: {e}")
    print(f"Got inventory: {inventory}")
    items = list(inventory.keys())
    print(f"Item list: {items}")
    Total = sum(inventory.values())
    print(f"Total quantity of the {len(items)} items: {Total}")
    if len(inventory) > 0:
        for key in inventory:
            value = inventory[key]
            print(f"Item {key} represents {round((value / Total * 100), 1)}%")
        most = list(inventory.keys())[0]
        least = list(inventory.keys())[0]
        for key in inventory:
            if inventory[key] > inventory[most]:
                most = key
            if inventory[key] < inventory[least]:
                least = key
        print(f"Item most abundant: {most} with quantity {inventory[most]}")
        print(f"Item least abundant: {least} with quantity {inventory[least]}")
    inventory.update({"magic_item": 1})
    print(f"Updated inventory: {inventory}")

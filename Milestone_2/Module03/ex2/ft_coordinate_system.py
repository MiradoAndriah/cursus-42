#!/usr/bin/env python3
import math

def get_player_pos() -> float:
    while True:
        data = input("Enter new coordinates as floats in format 'x,y,z': ")
        split = data.split(",")
        if len(split) != 3:
            print("Invalid syntax")
            continue
        try:
            to_float = ()
            for i in split:
                to_float += (float(i),)
            return to_float
        except ValueError as e:
            print(f"Error on parameter '{i}': {e}")

if __name__ == "__main__":
    print("=== Game Coordinate System ===\n")
    print("Get a first set of coordinates")
    data = get_player_pos()
    print(f"Got a first tuple: {data}")
    print(f"It includes: X={data[0]}, Y={data[1]}, Z={data[2]} ")
    x2, y2, z2 = 0, 0, 0
    x1, y1, z1 = data
    dist = math.sqrt((x2 - x1)**2 + (y2 - y1)**2 + (z2 - z1)**2)
    print(f"Distance to center: {dist:.4f}\n")

    print("Get a first set of coordinates")
    data2 = get_player_pos()
    x2, y2, z2 = data2
    dist2 = math.sqrt((x2 - x1)**2 + (y2 - y1)**2 + (z2 - z1)**2)
    print(f"Distance between the 2 sets of coordinates: {dist2:.4f}")

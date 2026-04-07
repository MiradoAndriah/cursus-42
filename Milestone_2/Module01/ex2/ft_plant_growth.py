#!/usr/bin/env python3

import sys
sys.path.append("../ex1")

from ft_garden_data import Plant  # type: ignore

def grow(plant):
    plant.height = round(plant.height + 0.8, 1)
    plant.age += 1
    print(plant.name, ":", plant.height, "cm,", plant.age, "days old")

if __name__ == "__main__" :
    plant1 = Plant("Rose",25.0,30)
    print("=== Garden Plant Growth ===")
    plant1.show()
    h_init = plant1.height

    for jour in range(1,8) :
        print("=== Day " ,jour, "===")
        grow(plant1)
    print("Growth this week: ",plant1.height  - h_init,"cm")
    

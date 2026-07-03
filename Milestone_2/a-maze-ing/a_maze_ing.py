#!/usr/bin/env python3

import sys
from config import parse_config
from generator import MazeGenerator
from writer import write_maze


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("error, The argument must be")
    config = parse_config(sys.argv[1])
    maze = MazeGenerator(config["WIDTH"],config["HEIGHT"],config["ENTRY"], config["EXIT"],config["SEED"])
    maze.generate()
    chemin = maze.get_solution()
    write_maze(maze.get_grid(), maze.entry, maze.exit, maze.get_solution(), "output_maze.txt")
    
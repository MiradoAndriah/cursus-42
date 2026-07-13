#!/usr/bin/env python3

import sys
from config import parse_config
from generator import MazeGenerator
from writer import write_maze
from display import display_maze, COLORS, RESET
from display_mlx import init_window, draw_maze, start_loop, draw_rect
import os


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("error, The argument must be")
        sys.exit()
    colors_index=0
    show_path = False
    config = parse_config(sys.argv[1])
    maze = MazeGenerator(config["WIDTH"],config["HEIGHT"],config["ENTRY"], config["EXIT"],config["SEED"])
    maze.generate()
    chemin = maze.get_solution()
    write_maze(maze.get_grid(), maze.entry, maze.exit, chemin, config["OUTPUT_FILE"])
    #display_maze(maze.get_grid(), maze.entry, maze.exit, config["WIDTH"], config["HEIGHT"], chemin, show_path, COLORS[colors_index])
    init_window(config["WIDTH"], config["HEIGHT"])
    draw_maze(maze.get_grid(), maze.entry, maze.exit, config["WIDTH"], config["HEIGHT"], chemin, show_path)
    start_loop()
    # while True:
    #     print("=== A-Maze-ing ===")
    #     print("1. Re_generate a new maze")
    #     print("2. Show/hide path from entry to exit")
    #     print("3. Rotate maze colors")
    #     print("4. Exit")
    #     try:
    #         choice = input("Choice? (1-4): ")
    #         if choice == "1":
    #             config["SEED"] += 1
    #             maze = MazeGenerator(config["WIDTH"],config["HEIGHT"],config["ENTRY"], config["EXIT"],config["SEED"])    
    #             maze.generate()
    #             draw_maze(maze.get_grid(), maze.entry, maze.exit, config["WIDTH"], config["HEIGHT"], chemin, show_path)
                
    #         elif choice == "2":
    #             show_path = not show_path
    #             draw_maze(maze.get_grid(), maze.entry, maze.exit, 
    #             config["WIDTH"], config["HEIGHT"], 
    #             chemin, show_path)
    #         elif choice == "3":
    #             colors_index = (colors_index + 1) % len(COLORS)
    #             draw_maze(maze.get_grid(), maze.entry, maze.exit, config["WIDTH"], config["HEIGHT"], chemin, show_path)
    #         elif choice == "4":
    #             break
    #         else:
    #             os.system('clear')
    #             print(f"\n{COLORS[8]}ERROR:{RESET} choice have to be between 1-4\n")

    #     except KeyboardInterrupt:
    #         raise ValueError("end of program")
            
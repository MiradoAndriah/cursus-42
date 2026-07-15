#!/usr/bin/env python3

import sys
from config import parse_config
from generator import MazeGenerator
from writer import write_maze
from display_mlx import Renderer, CELL_SIZE, MARGIN_BOTTOM



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
    render = Renderer(config["WIDTH"] * CELL_SIZE, config["HEIGHT"] * CELL_SIZE + MARGIN_BOTTOM)
    """stockage des valeur de la labyrinthe"""
    render.grid = maze.get_grid()
    render.entry = maze.entry
    render.exit = maze.exit
    render.maze_width = config["WIDTH"]
    render.maze_height = config["HEIGHT"]
    render.chemin = chemin
    render.seed = config["SEED"]
    render.draw_maze(maze.get_grid(), maze.entry, maze.exit,
                        config["WIDTH"], config["HEIGHT"], chemin, show_path)
    render.flush()
    render.mlx.mlx_loop(render.mlx_ptr)

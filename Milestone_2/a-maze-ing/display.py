import os


NORTH = 1
EAST = 2
SOUTH = 4
WEST = 8

COLORS = [
    "\033[37m",
    "\033[32m",
    "\033[36m",
    "\033[39m",
    "\033[33m",
    "\033[34m",
    "\033[38m",
    "\033[35m",
    "\033[31m",

]
RESET = "\033[0m"

def display_maze(grid, entry, exit, width, height, chemin, show_path=False, colors=COLORS[1]):
    if isinstance(chemin, str):
        path = [entry]
        x, y = entry

        for direction in chemin:
            if direction == 'N':
                y -= 1
            elif direction == 'S':
                y += 1
            elif direction == 'E':
                x += 1
            elif direction == 'W':
                x -= 1

            path.append((x, y))

        chemin = path
    os.system('clear')
    for y in range(height):
        for x in range(width):
            print(f"{colors}+{RESET}", end="")
            if grid[y][x] & NORTH != 0:
                print(f"{colors}--{RESET}", end="")
            else:
                print("  ", end="")
        print(f"{colors}+{RESET}")
        
        for x in range(width):
            if grid[y][x] & WEST != 0:
                print(f"{colors}|{RESET}", end="")
            else:
                print(" ", end="")
            if (x, y) == entry:
                print(f"{COLORS[1]}██{RESET}", end="")
            elif (x, y) == exit:
                print(f"{COLORS[8]}██{RESET}", end="")
            elif show_path and (x, y) in chemin:
                print(". ", end="")
            elif grid[y][x] == 15:
                print("\033[42m██\033[0m", end="")
            else:
                print("  ", end="")
        print(f"{colors}|{RESET}")
    
    for x in range(width):
        print(f"{colors}+{RESET}", end="")
        if grid[height-1][x] & SOUTH != 0:
            print(f"{colors}--{RESET}", end="")
        else:
            print("  ", end="")
    print(f"{colors}+{RESET}")
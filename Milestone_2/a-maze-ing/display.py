NORTH = 1
EAST = 2
SOUTH = 4
WEST = 8

def display_maze(grid, entry, exit, width, height, chemin, show_path=False):
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

    for y in range(height):
        for x in range(width):
            print("+", end="")
            if grid[y][x] & NORTH != 0:
                print("--", end="")
            else:
                print("  ", end="")
        print("+")
        
        for x in range(width):
            if grid[y][x] & WEST != 0:
                print("|", end="")
            else:
                print(" ", end="")
            if (x, y) == entry:
                print("E ", end="")
            elif (x, y) == exit:
                print("X ", end="")
            elif show_path and (x, y) in chemin:
                print(". ", end="")
            else:
                print("  ", end="")
        print("|")
    
    for x in range(width):
        print("+", end="")
        if grid[height-1][x] & SOUTH != 0:
            print("--", end="")
        else:
            print("  ", end="")
    print("+")
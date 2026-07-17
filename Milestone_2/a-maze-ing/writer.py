import sys


def write_maze(grid, entry, exit, solution, output_file):
    try:
        with open(output_file, 'w') as f:
            for line in grid:
                for cellule in line:
                    f_hexa = format(cellule, 'X')
                    f.write(f_hexa)
                f.write("\n")
            
            f.write("\n")
            f.write(f"{entry[0]},{entry[1]}\n")
            f.write(f"{exit[0]},{exit[1]}\n")
            f.write(solution)
    except Exception as e:
        print(f"ERROR: {e}")
        sys.exit(1)

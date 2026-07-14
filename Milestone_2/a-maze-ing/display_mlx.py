from mlx import mlx
import os

NORTH = 1
EAST = 2
SOUTH = 4
WEST = 8

m = mlx.Mlx()
mlx_ptr = m.mlx_init()
#win = m.mlx_new_window(mlx_ptr, 500, 500, "A-Maze-ing")
win = None

def init_window(width, height):
    global win

    CELL_SIZE = 30

    if win is None:
        win = m.mlx_new_window(
            mlx_ptr,
            width * CELL_SIZE,
            height * CELL_SIZE,
            "A-Maze-ing"
        )

        m.mlx_key_hook(win, key_hook, None)
        m.mlx_hook(win, 33, 0, destroy, None)

# def draw_rect(x, y, width, heigth, color):
#     for dy in range(heigth):
#         for dx in range(width):
#             m.mlx_string_put(mlx_ptr, win, x + dx, y + dy, color)
# draw_rect(50, 50, 100, 50, 0xFF0000)   # rectangle rouge
# draw_rect(200, 100, 80, 80, 0x00FF00)  # rectangle vert


def key_hook(keycode, params):
    print(f"touche pressée : {keycode}")
    if keycode == 65307:
        m.mlx_loop_exit(mlx_ptr)
    return 0

def destroy(params):
    m.mlx_loop_exit(mlx_ptr)
    os._exit(0)
    return 0

def draw_maze(grid, entry, exit, width, height, chemin, show_path):
    CELL_SIZE = 30
    WALL_SIZE = 2
    WALL_COLOR = 0xFFFFFF
    BG_COLOR = 0x000000
    PATH_COLOR = 0x00FFFF
    ENTRY_COLOR = 0x00FF00
    EXIT_COLOR = 0xFF0000
    COLOR_42 = 0x00AA00

    if isinstance(chemin, str):
        path = [entry]
        curr_x, curr_y = entry

        for direction in chemin:
            if direction == 'N':
                curr_y -= 1
            elif direction == 'S':
                curr_y += 1
            elif direction == 'E':
                curr_x += 1
            elif direction == 'W':
                curr_x -= 1
            path.append((curr_x, curr_y))
        chemin = path
    drawn = [False]
    def loop_hook(params):
        if not drawn[0]:
            m.mlx_clear_window(mlx_ptr, win)
            for y in range(height):
                for x in range(width):
                    px = x * CELL_SIZE
                    py = y * CELL_SIZE

                    if (x,y) == entry:
                        #draw_rect(pixel_x, pixel_y, CELL_SIZE, CELL_SIZE, ENTRY_COLOR)
                        m.mlx_string_put(mlx_ptr, win, px+2, py+5, 0x00FF00, "E")
                    if (x, y) == exit:
                        #draw_rect(pixel_x, pixel_y, CELL_SIZE, CELL_SIZE, EXIT_COLOR)
                        m.mlx_string_put(mlx_ptr, win, px+2, py+5, 0xFF0000, "X")
                    if show_path and (x, y) in chemin:
                        #draw_rect(pixel_x, pixel_y, CELL_SIZE, CELL_SIZE, PATH_COLOR)
                        m.mlx_string_put(mlx_ptr, win, px+2, py+5, 0x00FFFF, ".")
                    if grid[y][x] == 15:
                        #draw_rect(pixel_x, pixel_y, CELL_SIZE, CELL_SIZE, COLOR_42)
                        m.mlx_string_put(mlx_ptr, win, px+2, py+5, 0x00FF00, "##")
                    if grid[y][x] & NORTH != 0:
                        #draw_rect(pixel_x, pixel_y, CELL_SIZE, WALL_SIZE, WALL_COLOR)
                        m.mlx_string_put(mlx_ptr, win, px, py, 0xFFFFFF, "+---")
                    if grid[y][x] & SOUTH != 0:
                        #draw_rect(pixel_x, pixel_y + CELL_SIZE - WALL_SIZE, CELL_SIZE, WALL_SIZE, WALL_COLOR)
                        m.mlx_string_put(mlx_ptr, win, px, py, 0xFFFFFF, "+---")
                    if grid[y][x] & WEST != 0:
                        #draw_rect(pixel_x, pixel_y, WALL_SIZE, CELL_SIZE, WALL_COLOR)
                        m.mlx_string_put(mlx_ptr, win, px, py, 0xFFFFFF, "|")
                    if grid[y][x] & EAST != 0:
                        #draw_rect(pixel_x + CELL_SIZE - WALL_SIZE, pixel_y, WALL_SIZE, CELL_SIZE, WALL_COLOR)
                        m.mlx_string_put(mlx_ptr, win, px+CELL_SIZE-8, py, 0xFFFFFF, "|")
            drawn[0] = True
        return 0
    m.mlx_loop_hook(mlx_ptr, loop_hook, None)
    m.mlx_loop(mlx_ptr)


# if __name__ == "__main__":
#     m.mlx_key_hook(win, key_hook, None)
#     m.mlx_hook(win, 33, 0, destroy, None)
#     m.mlx_loop(mlx_ptr)
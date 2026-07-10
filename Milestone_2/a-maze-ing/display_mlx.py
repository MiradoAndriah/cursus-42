from mlx import mlx
import os

m = mlx.Mlx()
mlx_ptr = m.mlx_init()
win = m.mlx_new_window(mlx_ptr, 500, 500, "A-Maze-ing")

def draw_rect(x, y, width, heigth, color):
    for dy in range(heigth):
        for dx in range(width):
            m.mlx_pixel_put(mlx_ptr, win, x + dx, y + dy, color)


def key_hook(keycode, params):
    # print(f"touche pressée : {keycode}")
    if keycode == 65307:
        m.mlx_loop_exit(mlx_ptr)
    return 0

def destroy(params):
    m.mlx_loop_exit(mlx_ptr)
    os._exit(0)
    return 0


m.mlx_key_hook(win, key_hook, None)
m.mlx_hook(win, 33, 0, destroy, None)
draw_rect(50, 50, 100, 50, 0xFF0000)   # rectangle rouge
draw_rect(200, 100, 80, 80, 0x00FF00)  # rectangle vert
m.mlx_loop(mlx_ptr)
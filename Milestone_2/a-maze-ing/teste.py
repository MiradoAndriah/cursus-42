from mlx import mlx
import os

m = mlx.Mlx()
mlx_ptr = m.mlx_init()
win = m.mlx_new_window(mlx_ptr, 500, 500, "Test")

def key_hook(keycode, param):
    if keycode == 65307:
        m.mlx_loop_exit(mlx_ptr)
    return 0

def destroy(param):
    os._exit(0)
    return 0

def loop_hook(param):
    m.mlx_string_put(mlx_ptr, win, 100, 100, 0xFF0000, "Hello MLX!")
    return 0

m.mlx_key_hook(win, key_hook, None)
m.mlx_hook(win, 33, 0, destroy, None)
m.mlx_loop_hook(mlx_ptr, loop_hook, None)
m.mlx_loop(mlx_ptr)
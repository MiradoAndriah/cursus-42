from mlx import Mlx
import os

NORTH = 1
EAST = 2
SOUTH = 4
WEST = 8
CELL_SIZE = 30
MARGIN_BOTTOM = 40

class Renderer:
    def __init__(self, width: int, height: int) -> None:
        self.width: int = width
        self.height: int = height
        self.mlx: Mlx = Mlx()
        self.mlx_ptr = self.mlx.mlx_init()
        self.win = self.mlx.mlx_new_window(self.mlx_ptr, width, height, "A_MAZE_ING")
        """creation d'image"""
        self.img = self.mlx.mlx_new_image(self.mlx_ptr, width, height)
        self.data: memoryview
        self.bpp: int
        self.sl: int
        self.data, self.bpp, self.sl, _ = \
            self.mlx.mlx_get_data_addr(self.img)
        """les hooks"""
        self.mlx.mlx_key_hook(self.win, self.key_hook, None)
        self.mlx.mlx_hook(self.win, 33, 0, self.destroy, None)

        """les donner du labyrinth"""
        self.grid = None
        self.entry = None
        self.exit = None
        self.maze_width = None
        self.maze_height = None
        self.chemin = None
        self.show_path = False
        self.seed = 0

        
    def put_pixel(self, x: int, y: int, color: int) -> None:
        if 0 <= x < self.width and 0 <= y < self.height:
            off: int = y * self.sl + x * (self.bpp // 8)
            self.data[off:off+4] = color.to_bytes(4, 'little')
        
    def flush(self) -> None:
        self.mlx.mlx_put_image_to_window(self.mlx_ptr, self.win, self.img, 0, 0)
    
    def draw_rect(self, x, y, width, height, color):
        for dy in range(height):
            for dx in range(width):
                self.put_pixel(x + dx, y + dy, color)

    def redraw(self):
        self.clear()
        self.draw_maze(self.grid, self.entry, self.exit,
                      self.maze_width, self.maze_height,
                      self.chemin, self.show_path)
        self.flush()
        
        self.mlx.mlx_clear_window(self.mlx_ptr, self.win)
        self.flush()
        self.mlx.mlx_string_put(
        self.mlx_ptr, self.win,
        10,
        self.height - 25,
        0xFFFFFFFF,
        "a:regen  w:path  d:color  esc:quit"
        )
    
    def clear(self):
        self.mlx.mlx_destroy_image(self.mlx_ptr, self.img)
        self.img = self.mlx.mlx_new_image(self.mlx_ptr, self.width, self.height)
        self.data, self.bpp, self.sl, _ = self.mlx.mlx_get_data_addr(self.img)
    
    def key_hook(self, keycode, params):
        if keycode == 0:
            return 0
        if keycode == 65307:
            self.mlx.mlx_loop_exit(self.mlx_ptr)
        elif keycode == 97:
            self.seed += 1
            from generator import MazeGenerator

            new_maze = MazeGenerator(self.maze_width, self.maze_height,
                                     self.entry, self.exit, self.seed)
            new_maze.generate()
            self.grid = new_maze.get_grid()
            self.chemin = new_maze.get_solution()
            self.redraw()
        elif keycode == 119:
            self.show_path = not self.show_path
            self.redraw()
        else:
            self.mlx.mlx_string_put(
                self.mlx_ptr, self.win,
                10, self.height - 25,
                0xFFFF0000,
                "ERROR: key invalide, press a or w or d or esc"
                )
        return 0

    def destroy(self, params):
        os._exit(0)
        return 0
    def draw_maze(self, grid, entry, exit, width, height, chemin, show_path):
        WALL_SIZE = 2
        WALL_COLOR  = 0xFFFFFFFF   # blanc ← ajouter FF devant
        ENTRY_COLOR = 0xFF00FF00   # vert
        EXIT_COLOR  = 0xFFFF0000   # rouge  
        PATH_COLOR  = 0xFF00FFFF   # cyan
        COLOR_42    = 0xFF005500   # vert foncé

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
        
        for y in range(height):
            for x in range(width):
                pixel_x = x * CELL_SIZE
                pixel_y = y * CELL_SIZE

                if (x,y) == entry:
                    self.draw_rect(pixel_x, pixel_y, CELL_SIZE, CELL_SIZE, ENTRY_COLOR)
                    
                if (x, y) == exit:
                    self.draw_rect(pixel_x, pixel_y, CELL_SIZE, CELL_SIZE, EXIT_COLOR)
                if show_path and (x, y) in chemin:
                    self.draw_rect(pixel_x, pixel_y, CELL_SIZE, CELL_SIZE, PATH_COLOR)
                if grid[y][x] == 15:
                    self.draw_rect(pixel_x, pixel_y, CELL_SIZE, CELL_SIZE, COLOR_42)
                if grid[y][x] & NORTH != 0:
                    self.draw_rect(pixel_x, pixel_y, CELL_SIZE, WALL_SIZE, WALL_COLOR)
                if grid[y][x] & SOUTH != 0:
                    self.draw_rect(pixel_x, pixel_y + CELL_SIZE - WALL_SIZE, CELL_SIZE, WALL_SIZE, WALL_COLOR)
                if grid[y][x] & WEST != 0:
                    self.draw_rect(pixel_x, pixel_y, WALL_SIZE, CELL_SIZE, WALL_COLOR)
                if grid[y][x] & EAST != 0:
                    self.draw_rect(pixel_x + CELL_SIZE - WALL_SIZE, pixel_y, WALL_SIZE, CELL_SIZE, WALL_COLOR)
        return 0

if __name__ == "__main__":
    from generator import MazeGenerator
    maze = MazeGenerator(20, 15, (0,0), (19,14), 42)
    maze.generate()
    chemin = maze.get_solution()

    render = Renderer(20 * 30, 15 * 30)
    render.draw_maze(maze.get_grid(), maze.entry, maze.exit,
                        20, 15, chemin, False)
    render.flush()
    render.mlx.mlx_loop(render.mlx_ptr)
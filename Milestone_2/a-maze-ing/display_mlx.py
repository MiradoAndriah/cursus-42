from mlx import Mlx
import os

NORTH = 1
EAST = 2
SOUTH = 4
WEST = 8
MARGIN_BOTTOM = 40
WALL_COLORS = [
    0xFFFFFFFF,   # blanc
    0xFF00FF00,   # vert
    0xFFFFFF00,   # jaune
    0xFFFF00FF,   # magenta
    0xFF00FFFF,   # cyan
]

class Renderer:
    def __init__(self, maze_width: int, maze_height: int) -> None:
        self.mlx = Mlx()
        self.mlx_ptr = self.mlx.mlx_init()

        """calculer cell_size"""
        _, screen_w, screen_h = self.mlx.mlx_get_screen_size(self.mlx_ptr)
        cell_w = screen_w // maze_width
        cell_h = (screen_h - MARGIN_BOTTOM) // maze_height
        self.cell_size = min(cell_w, cell_h, 30)
        self.cell_size = max(self.cell_size, 5)

        """calculer taille fenêtre"""
        self.width = maze_width * self.cell_size
        self.height = maze_height * self.cell_size + MARGIN_BOTTOM
        self.maze_width = maze_width
        self.maze_height = maze_height

        """créer fenêtre et image avec la bonne taille"""
        self.win = self.mlx.mlx_new_window(self.mlx_ptr, self.width, self.height, "A_MAZE_ING")
        self.img = self.mlx.mlx_new_image(self.mlx_ptr, self.width, self.height)
        self.data, self.bpp, self.sl, _ = self.mlx.mlx_get_data_addr(self.img)

        """hooks"""
        self.mlx.mlx_key_hook(self.win, self.key_hook, None)
        self.mlx.mlx_hook(self.win, 33, 0, self.destroy, None)

        """données labyrinthe"""
        self.grid = None
        self.entry = None
        self.exit = None
        self.chemin = None
        self.show_path = False
        self.seed = 0
        self.color_index = 0
        self.wall_color = 0xFFFFFFFF
    

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
        self.mlx.mlx_clear_window(self.mlx_ptr, self.win)
        self.draw_maze(self.grid, self.entry, self.exit,
                      self.maze_width, self.maze_height,
                      self.chemin, self.show_path)
        self.flush()
        
        # self.flush()
        
    
    def clear(self):
        size = self.height * self.sl
        self.data[:size] = bytes(size)
    
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
            
            self.redraw()
            new_maze.generate()
            self.grid = new_maze.get_grid()
            self.chemin = new_maze.get_solution()
            self.redraw()
        elif keycode == 119:
            self.show_path = not self.show_path
            self.redraw()
        
        elif keycode == 100:
            self.color_index = (self.color_index + 1) % len(WALL_COLORS)
            self.wall_color = WALL_COLORS[self.color_index]
            self.redraw()
        return 0

    def destroy(self, params):
        os._exit(0)
        return 0
    def draw_maze(self, grid, entry, exit, width, height, chemin, show_path):
        WALL_SIZE = max(1, self.cell_size // 15)
        CELL_SIZE = self.cell_size
        WALL_COLOR  = self.wall_color   # blanc ← ajouter FF devant
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
                    dot_size = max(4, self.cell_size // 5)
                    cx = pixel_x + CELL_SIZE // 2 - dot_size // 2
                    cy = pixel_y + CELL_SIZE // 2 - dot_size // 2
                    self.draw_rect(cx, cy, dot_size, dot_size, PATH_COLOR)
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
        
        self.mlx.mlx_string_put(
        self.mlx_ptr, self.win,
        10,
        self.height - 25,
        0xFFFFFFFF,
        "a:regen  w:show/hide path  d:Change_color  esc:quit"
        )

        return 0

"""
display.py – Terminal rendering of the maze using ANSI colour codes.

Each maze cell is drawn as a 3×3 block of characters in the terminal.
The centre character shows the cell type (entry, exit, path, 42-pattern, empty).
Walls are drawn with block characters on the edges.

ANSI colour codes used:
  \\033[Xm  = set colour X
  \\033[0m  = reset colour
"""

import os
import sys
from typing import Optional

# ─── ANSI colour helpers ─────────────────────────────────────────────────────

RESET  = "\033[0m"
BOLD   = "\033[1m"

# Foreground colours
FG_WHITE  = "\033[97m"
FG_CYAN   = "\033[96m"
FG_GREEN  = "\033[92m"
FG_YELLOW = "\033[93m"
FG_RED    = "\033[91m"
FG_BLUE   = "\033[94m"

# Background colours
BG_BLACK  = "\033[40m"
BG_WHITE  = "\033[107m"
BG_BLUE   = "\033[44m"
BG_GREEN  = "\033[42m"
BG_RED    = "\033[41m"
BG_YELLOW = "\033[103m"

WALL_CHAR  = " "   # character used to paint a wall block
OPEN_CHAR  = " "   # character used for open passage
PATH_CHAR  = "·"   # character shown on the solution path
ENTRY_CHAR = "E"
EXIT_CHAR  = "X"
FT_CHAR    = " "   # "42" pattern cell


def _cell_bg(
    col: int,
    row: int,
    entry: tuple[int, int],
    exit_: tuple[int, int],
    path_cells: set[tuple[int, int]],
    forty_two: set[tuple[int, int]],
    wall_colour: str,
) -> str:
    """Return the background colour string for a given cell."""
    if (col, row) == entry:
        return BG_GREEN
    if (col, row) == exit_:
        return BG_RED
    if (col, row) in forty_two:
        return BG_YELLOW
    if (col, row) in path_cells:
        return BG_BLUE
    return wall_colour   # open passage uses the chosen wall background


def render(
    grid: list[list[int]],
    entry: tuple[int, int],
    exit_: tuple[int, int],
    solution: str,
    show_path: bool,
    forty_two: set[tuple[int, int]],
    wall_colour: str = BG_WHITE,
    open_colour: str = BG_BLACK,
) -> None:
    """
    Print the maze to stdout using ANSI block characters.

    Args:
        grid:        2D wall bitmask grid.
        entry:       (col, row) entry cell.
        exit_:       (col, row) exit cell.
        solution:    Path string (N/E/S/W).
        show_path:   If True, highlight the solution path.
        forty_two:   Set of (col, row) cells forming the "42" pattern.
        wall_colour: ANSI BG code for walls (default: white).
        open_colour: ANSI BG code for open passages (default: black).
    """
    height = len(grid)
    width  = len(grid[0]) if height else 0

    # Bit constants
    NORTH, EAST, SOUTH, WEST = 0, 1, 2, 3

    # Build path cells set from the solution string
    path_cells: set[tuple[int, int]] = set()
    if show_path and solution:
        DR = {NORTH: -1, SOUTH: 1, EAST: 0, WEST: 0}
        DC = {NORTH:  0, SOUTH: 0, EAST: 1, WEST: -1}
        DIR_MAP = {'N': NORTH, 'S': SOUTH, 'E': EAST, 'W': WEST}
        c, r = entry
        path_cells.add((c, r))
        for ch in solution:
            d = DIR_MAP[ch]
            r += DR[d]
            c += DC[d]
            path_cells.add((c, r))

    # We draw each cell as 3 rows of 3 chars.
    # row_chars[screen_row] = list of char strings
    # Total screen rows = height * 2 + 1 (for the border lines)
    # We use a simpler line-by-line approach:

    lines: list[str] = []

    for r in range(height):
        # ── top border of this row of cells ──────────────────────────────
        top_line = ""
        for c in range(width):
            v = grid[r][c]
            n_wall = (v >> NORTH) & 1   # 1 = closed

            # Top-left corner pixel
            top_line += wall_colour + WALL_CHAR + RESET

            # Top edge: wall if North closed
            if n_wall:
                top_line += wall_colour + WALL_CHAR + RESET
            else:
                top_line += open_colour + OPEN_CHAR + RESET

        # Rightmost corner
        top_line += wall_colour + WALL_CHAR + RESET
        lines.append(top_line)

        # ── middle row of this row of cells ──────────────────────────────
        mid_line = ""
        for c in range(width):
            v = grid[r][c]
            w_wall = (v >> WEST) & 1
            e_wall = (v >> EAST) & 1

            # Left border of cell
            if w_wall:
                mid_line += wall_colour + WALL_CHAR + RESET
            else:
                mid_line += open_colour + OPEN_CHAR + RESET

            # Cell interior
            if (c, r) == entry:
                mid_line += BG_GREEN + FG_WHITE + BOLD + ENTRY_CHAR + RESET
            elif (c, r) == exit_:
                mid_line += BG_RED + FG_WHITE + BOLD + EXIT_CHAR + RESET
            elif (c, r) in forty_two:
                mid_line += BG_YELLOW + FG_BLACK + FT_CHAR + RESET
            elif show_path and (c, r) in path_cells:
                mid_line += BG_BLUE + FG_WHITE + PATH_CHAR + RESET
            else:
                mid_line += open_colour + OPEN_CHAR + RESET

        # Rightmost wall
        mid_line += wall_colour + WALL_CHAR + RESET
        lines.append(mid_line)

    # ── bottom border of the last row ────────────────────────────────────
    bot_line = ""
    for c in range(width):
        v = grid[height - 1][c]
        s_wall = (v >> SOUTH) & 1
        bot_line += wall_colour + WALL_CHAR + RESET
        if s_wall:
            bot_line += wall_colour + WALL_CHAR + RESET
        else:
            bot_line += open_colour + OPEN_CHAR + RESET
    bot_line += wall_colour + WALL_CHAR + RESET
    lines.append(bot_line)

    # Clear screen then print
    os.system("clear" if os.name == "posix" else "cls")
    print("\n".join(lines))


# ─── Available wall colour palettes ─────────────────────────────────────────

WALL_COLOURS = [BG_WHITE, BG_GREEN, BG_YELLOW, BG_RED, BG_BLUE]
COLOUR_NAMES = ["White", "Green", "Yellow", "Red", "Blue"]


def colour_name(bg_code: str) -> str:
    """Return a human-readable name for a BG colour code."""
    try:
        return COLOUR_NAMES[WALL_COLOURS.index(bg_code)]
    except ValueError:
        return "Unknown"


# ─── FG_BLACK missing above – define it ─────────────────────────────────────
FG_BLACK = "\033[30m"

"""
mazegen.generator - Maze generation module (reusable).

Wall encoding (hex digit per cell):
  Bit 0 (LSB) = North wall
  Bit 1       = East wall
  Bit 2       = South wall
  Bit 3       = West wall

  1 = wall closed, 0 = wall open
"""

import random
from collections import deque
from typing import Optional


# ─── Direction constants ─────────────────────────────────────────────────────

NORTH = 0   # bit 0
EAST  = 1   # bit 1
SOUTH = 2   # bit 2
WEST  = 3   # bit 3

OPPOSITE = {NORTH: SOUTH, SOUTH: NORTH, EAST: WEST, WEST: EAST}

# Row/col delta when moving in a direction
DR = {NORTH: -1, SOUTH: 1, EAST: 0, WEST: 0}
DC = {NORTH:  0, SOUTH: 0, EAST: 1, WEST: -1}

DIR_LETTER = {NORTH: 'N', EAST: 'E', SOUTH: 'S', WEST: 'W'}


# ─── "42" pixel font (5 rows × 3 cols each digit) ────────────────────────────

DIGIT_4 = [
    "#.#",
    "#.#",
    "###",
    "..#",
    "..#",
]

DIGIT_2 = [
    "###",
    "..#",
    "###",
    "#..",
    "###",
]


# ─── MazeGenerator ───────────────────────────────────────────────────────────

class MazeGenerator:
    """
    Generates a maze using recursive backtracking (DFS).

    The maze is stored as a 2D grid of integers (grid[row][col]).
    Each integer encodes the CLOSED walls of that cell as a 4-bit value:
      bit0=North, bit1=East, bit2=South, bit3=West.

    Args:
        width:   Number of columns.
        height:  Number of rows.
        entry:   (col, row) of the entry cell.
        exit_:   (col, row) of the exit cell.
        perfect: If True, generate a perfect maze (one unique path).
        seed:    Random seed for reproducibility.

    Example::

        mg = MazeGenerator(width=20, height=15,
                           entry=(0, 0), exit_=(19, 14),
                           perfect=True, seed=42)
        mg.generate()
        grid   = mg.grid          # list[list[int]]
        path   = mg.solution      # e.g. "SSEENWW..."
        cells  = mg.forty_two     # set of (col, row) cells forming "42"
    """

    def __init__(
        self,
        width: int,
        height: int,
        entry: tuple[int, int],
        exit_: tuple[int, int],
        perfect: bool = True,
        seed: Optional[int] = None,
    ) -> None:
        """Initialise the maze generator."""
        self.width   = width
        self.height  = height
        self.entry   = entry    # (col, row)
        self.exit_   = exit_    # (col, row)
        self.perfect = perfect
        self.seed    = seed

        # grid[row][col] = bitmask of CLOSED walls (0-15)
        self.grid: list[list[int]] = []
        self.solution: str = ""
        self.forty_two: set[tuple[int, int]] = set()

    # ── public ───────────────────────────────────────────────────────────────

    def generate(self) -> None:
        """Generate the maze. Call this before accessing grid/solution."""
        rng = random.Random(self.seed)

        self._init_grid()           # all walls closed
        self._carve_passages(rng)   # DFS spanning tree
        self._open_borders()        # open entry/exit outer wall
        self.forty_two = self._stamp_42()   # place "42" pattern

        if not self.perfect:
            self._add_loops(rng)    # extra openings for loops

        self.solution = self._bfs_path()    # shortest path

    # ── private helpers ───────────────────────────────────────────────────────

    def _init_grid(self) -> None:
        """Create grid where every cell has all 4 walls closed (value=0xF=15)."""
        self.grid = [[0xF] * self.width for _ in range(self.height)]

    def _in_bounds(self, r: int, c: int) -> bool:
        """Return True if (r, c) is inside the grid."""
        return 0 <= r < self.height and 0 <= c < self.width

    def _remove_wall(self, r: int, c: int, direction: int) -> None:
        """Open the wall between (r,c) and its neighbour in `direction`."""
        self.grid[r][c] &= ~(1 << direction)
        nr, nc = r + DR[direction], c + DC[direction]
        self.grid[nr][nc] &= ~(1 << OPPOSITE[direction])

    def _carve_passages(self, rng: random.Random) -> None:
        """
        Iterative DFS (recursive backtracker).
        Starts from the entry cell and visits every cell exactly once,
        carving passages. The result is a spanning tree = perfect maze.
        """
        ec, er = self.entry
        visited: set[tuple[int, int]] = set()
        stack: list[tuple[int, int]] = [(er, ec)]
        visited.add((er, ec))

        while stack:
            r, c = stack[-1]
            # Collect unvisited neighbours
            neighbours: list[tuple[int, int, int]] = []
            for d in [NORTH, EAST, SOUTH, WEST]:
                nr, nc = r + DR[d], c + DC[d]
                if self._in_bounds(nr, nc) and (nr, nc) not in visited:
                    neighbours.append((d, nr, nc))

            if neighbours:
                d, nr, nc = rng.choice(neighbours)
                self._remove_wall(r, c, d)
                visited.add((nr, nc))
                stack.append((nr, nc))
            else:
                stack.pop()

    def _open_borders(self) -> None:
        """
        Open the external border wall at entry and exit.
        Detect which outer edge the point lies on and open that wall.
        """
        for (col, row) in [self.entry, self.exit_]:
            if row == 0:
                self.grid[row][col] &= ~(1 << NORTH)
            elif row == self.height - 1:
                self.grid[row][col] &= ~(1 << SOUTH)
            elif col == 0:
                self.grid[row][col] &= ~(1 << WEST)
            elif col == self.width - 1:
                self.grid[row][col] &= ~(1 << EAST)

    def _stamp_42(self) -> set[tuple[int, int]]:
        """
        Place "42" as fully-walled (isolated) cells near the maze centre.
        Pattern: 5 rows × 7 cols.  Returns the set of (col, row) cells used.
        Returns empty set if the maze is too small.
        """
        pat_w, pat_h = 7, 5
        cells: set[tuple[int, int]] = set()

        if self.width < pat_w + 2 or self.height < pat_h + 2:
            return cells   # too small

        start_r = (self.height - pat_h) // 2
        start_c = (self.width  - pat_w) // 2

        # Combine digit4 + gap column + digit2 into one 5x7 grid
        full_pattern = [
            [DIGIT_4[row][col] for col in range(3)]
            + ['.']
            + [DIGIT_2[row][col] for col in range(3)]
            for row in range(5)
        ]

        for dr in range(pat_h):
            for dc in range(pat_w):
                if full_pattern[dr][dc] == '#':
                    r = start_r + dr
                    c = start_c + dc
                    # Fully close this cell
                    self.grid[r][c] = 0xF
                    # Also close neighbouring cells' walls that face this cell
                    for d in [NORTH, EAST, SOUTH, WEST]:
                        nr, nc = r + DR[d], c + DC[d]
                        if self._in_bounds(nr, nc):
                            self.grid[nr][nc] |= (1 << OPPOSITE[d])
                    cells.add((c, r))   # stored as (col, row)

        return cells

    def _add_loops(self, rng: random.Random, ratio: float = 0.10) -> None:
        """
        For non-perfect mazes: randomly remove some internal walls to add loops.
        Only removes walls between internal neighbours; never touches "42" cells.
        """
        count = int(self.width * self.height * ratio)
        attempts = 0
        added = 0
        while added < count and attempts < count * 10:
            attempts += 1
            r = rng.randint(0, self.height - 2)
            c = rng.randint(0, self.width  - 2)
            d = rng.choice([EAST, SOUTH])
            nr, nc = r + DR[d], c + DC[d]
            # Don't touch "42" cells
            if (c, r) in self.forty_two or (nc, nr) in self.forty_two:
                continue
            self._remove_wall(r, c, d)
            added += 1

    def _bfs_path(self) -> str:
        """
        BFS from entry to exit on the INTERNAL grid (no virtual border nodes).
        Returns the path as a string of N/E/S/W letters, or "" if unreachable.
        """
        ec, er = self.entry
        xc, xr = self.exit_

        # parent[(r,c)] = (prev_r, prev_c, direction) or None for start
        parent: dict[
            tuple[int, int],
            Optional[tuple[int, int, int]]
        ] = {(er, ec): None}

        queue: deque[tuple[int, int]] = deque([(er, ec)])

        while queue:
            r, c = queue.popleft()
            if (r, c) == (xr, xc):
                break
            v = self.grid[r][c]
            for d in [NORTH, EAST, SOUTH, WEST]:
                if not (v >> d) & 1:   # wall is open
                    nr, nc = r + DR[d], c + DC[d]
                    if self._in_bounds(nr, nc) and (nr, nc) not in parent:
                        parent[(nr, nc)] = (r, c, d)
                        queue.append((nr, nc))

        if (xr, xc) not in parent:
            return ""

        # Reconstruct path backwards
        path_dirs: list[str] = []
        cur: tuple[int, int] = (xr, xc)
        while parent[cur] is not None:
            pr, pc, d = parent[cur]   # type: ignore[misc]
            path_dirs.append(DIR_LETTER[d])
            cur = (pr, pc)
        path_dirs.reverse()
        return "".join(path_dirs)

"""
a_maze_ing.py – Main entry point for the A-Maze-ing project.

Usage:
    python3 a_maze_ing.py config.txt

The program:
  1. Reads the configuration file.
  2. Generates a maze using MazeGenerator.
  3. Writes the maze to the output file.
  4. Displays the maze in the terminal with an interactive menu.
"""

import os
import sys

from config import parse_config
from writer import write_maze
from display import (
    render,
    WALL_COLOURS,
    COLOUR_NAMES,
    BG_BLACK,
    BG_WHITE,
)

# Support both: running from project root and after pip install
_here = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(_here, "mazegen_pkg"))
from generator import MazeGenerator  # noqa: E402


# ─── Minimum maze size to stamp "42" ────────────────────────────────────────
MIN_W_FOR_42 = 9
MIN_H_FOR_42 = 7


def run(config_path: str) -> None:
    """
    Main execution function.

    Args:
        config_path: Path to the configuration file.
    """
    # ── 1. Parse config ──────────────────────────────────────────────────────
    try:
        cfg = parse_config(config_path)
    except (FileNotFoundError, ValueError) as e:
        print(f"[ERROR] {e}", file=sys.stderr)
        sys.exit(1)

    # ── 2. State shared between re-generations ───────────────────────────────
    wall_colour   = BG_WHITE
    show_path     = False
    current_seed  = cfg["seed"]

    def generate_and_display() -> MazeGenerator:
        """Generate a new maze and display it. Returns the generator."""
        nonlocal current_seed
        mg = MazeGenerator(
            width=cfg["width"],
            height=cfg["height"],
            entry=cfg["entry"],
            exit_=cfg["exit_"],
            perfect=cfg["perfect"],
            seed=current_seed,
        )
        mg.generate()

        # Warn if maze is too small for "42"
        if cfg["width"] < MIN_W_FOR_42 or cfg["height"] < MIN_H_FOR_42:
            print(
                "[INFO] Maze is too small to display the '42' pattern.",
                file=sys.stderr,
            )

        # Write output file
        try:
            write_maze(
                cfg["output_file"],
                mg.grid,
                cfg["entry"],
                cfg["exit_"],
                mg.solution,
            )
        except OSError as e:
            print(f"[ERROR] Cannot write output file: {e}", file=sys.stderr)
            sys.exit(1)

        # Display
        render(
            mg.grid,
            cfg["entry"],
            cfg["exit_"],
            mg.solution,
            show_path,
            mg.forty_two,
            wall_colour,
            BG_BLACK,
        )

        return mg

    # ── 3. First generation ──────────────────────────────────────────────────
    mg = generate_and_display()

    # ── 4. Interactive menu ──────────────────────────────────────────────────
    colour_index = 0   # index into WALL_COLOURS list

    while True:
        print("\n==== A-Maze-ing ====")
        print("1. Re-generate a new maze")
        print(f"2. {'Hide' if show_path else 'Show'} path from entry to exit")
        print(f"3. Rotate maze wall colour (current: {COLOUR_NAMES[colour_index]})")
        print("4. Quit")

        choice = input("Choice (1-4): ").strip()

        if choice == "1":
            # Increment seed so each re-generation is different
            if current_seed is not None:
                current_seed += 1
            mg = generate_and_display()

        elif choice == "2":
            show_path = not show_path
            render(
                mg.grid,
                cfg["entry"],
                cfg["exit_"],
                mg.solution,
                show_path,
                mg.forty_two,
                wall_colour,
                BG_BLACK,
            )

        elif choice == "3":
            colour_index = (colour_index + 1) % len(WALL_COLOURS)
            wall_colour = WALL_COLOURS[colour_index]
            render(
                mg.grid,
                cfg["entry"],
                cfg["exit_"],
                mg.solution,
                show_path,
                mg.forty_two,
                wall_colour,
                BG_BLACK,
            )

        elif choice == "4":
            print("Goodbye!")
            break

        else:
            print("Invalid choice. Please enter 1, 2, 3, or 4.")


# ─── Entry point ─────────────────────────────────────────────────────────────

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print(f"Usage: python3 {sys.argv[0]} <config_file>", file=sys.stderr)
        sys.exit(1)

    run(sys.argv[1])

"""
writer.py – Write the maze grid to the output file in the required format.

Format:
  - One hex digit per cell, row by row, one row per line.
  - An empty line.
  - Entry coordinates (col,row).
  - Exit coordinates (col,row).
  - Shortest path string (N/E/S/W letters).
  - Every line ends with \n.
"""


def write_maze(
    filepath: str,
    grid: list[list[int]],
    entry: tuple[int, int],
    exit_: tuple[int, int],
    solution: str,
) -> None:
    """
    Write the maze to `filepath`.

    Args:
        filepath: Destination file path.
        grid:     2D list [row][col] of wall bitmasks (0-15).
        entry:    (col, row) of the entry cell.
        exit_:    (col, row) of the exit cell.
        solution: Path string from entry to exit (e.g. "SSEENWW").

    Raises:
        OSError: If the file cannot be written.
    """
    with open(filepath, "w") as f:
        # Grid rows – each cell as one uppercase hex digit
        for row in grid:
            f.write("".join(format(cell, "X") for cell in row) + "\n")

        # Empty separator line
        f.write("\n")

        # Entry coordinates
        f.write(f"{entry[0]},{entry[1]}\n")

        # Exit coordinates
        f.write(f"{exit_[0]},{exit_[1]}\n")

        # Shortest path
        f.write(solution + "\n")

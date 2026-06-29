"""
config.py – Parse and validate the configuration file.

Format: one KEY=VALUE per line, lines starting with # are comments.

Mandatory keys:
  WIDTH, HEIGHT, ENTRY, EXIT, OUTPUT_FILE, PERFECT

Optional keys:
  SEED      (integer)
  ALGORITHM (backtracker | prim)   – bonus
"""

from typing import Any


# Keys that must be present in the config file
REQUIRED_KEYS = {"WIDTH", "HEIGHT", "ENTRY", "EXIT", "OUTPUT_FILE", "PERFECT"}


def parse_config(filepath: str) -> dict[str, Any]:
    """
    Read a config file and return a validated dictionary.

    Args:
        filepath: Path to the config text file.

    Returns:
        Dict with typed values:
          width (int), height (int),
          entry (tuple[int,int]), exit_ (tuple[int,int]),
          output_file (str), perfect (bool),
          seed (int | None), algorithm (str)

    Raises:
        FileNotFoundError: If the file does not exist.
        ValueError: If any required key is missing or a value is invalid.
    """
    raw: dict[str, str] = {}

    try:
        with open(filepath, "r") as f:
            for lineno, line in enumerate(f, 1):
                line = line.strip()
                # Skip empty lines and comments
                if not line or line.startswith("#"):
                    continue
                if "=" not in line:
                    raise ValueError(
                        f"Line {lineno}: expected KEY=VALUE, got: {line!r}"
                    )
                key, _, value = line.partition("=")
                raw[key.strip().upper()] = value.strip()
    except FileNotFoundError:
        raise FileNotFoundError(f"Config file not found: {filepath!r}")

    # Check all required keys are present
    missing = REQUIRED_KEYS - raw.keys()
    if missing:
        raise ValueError(f"Missing required config keys: {', '.join(sorted(missing))}")

    # Parse each value with a clear error message
    try:
        width = int(raw["WIDTH"])
        height = int(raw["HEIGHT"])
    except ValueError:
        raise ValueError("WIDTH and HEIGHT must be integers.")

    if width < 2 or height < 2:
        raise ValueError("WIDTH and HEIGHT must be at least 2.")

    entry = _parse_coords("ENTRY", raw["ENTRY"], width, height)
    exit_ = _parse_coords("EXIT",  raw["EXIT"],  width, height)

    if entry == exit_:
        raise ValueError("ENTRY and EXIT must be different cells.")

    perfect_str = raw["PERFECT"].lower()
    if perfect_str not in ("true", "false"):
        raise ValueError("PERFECT must be True or False.")
    perfect = perfect_str == "true"

    # Optional keys
    seed: int | None = None
    if "SEED" in raw:
        try:
            seed = int(raw["SEED"])
        except ValueError:
            raise ValueError("SEED must be an integer.")

    algorithm = raw.get("ALGORITHM", "backtracker").lower()
    if algorithm not in ("backtracker", "prim"):
        raise ValueError("ALGORITHM must be 'backtracker' or 'prim'.")

    return {
        "width":       width,
        "height":      height,
        "entry":       entry,
        "exit_":       exit_,
        "output_file": raw["OUTPUT_FILE"],
        "perfect":     perfect,
        "seed":        seed,
        "algorithm":   algorithm,
    }


def _parse_coords(
    key: str,
    value: str,
    width: int,
    height: int,
) -> tuple[int, int]:
    """Parse 'x,y' and validate that it is inside the maze."""
    try:
        parts = value.split(",")
        if len(parts) != 2:
            raise ValueError()
        col, row = int(parts[0]), int(parts[1])
    except ValueError:
        raise ValueError(f"{key} must be in format x,y (e.g. 0,0). Got: {value!r}")

    if not (0 <= col < width and 0 <= row < height):
        raise ValueError(
            f"{key} ({col},{row}) is outside the maze bounds "
            f"(0..{width-1}, 0..{height-1})."
        )
    return (col, row)

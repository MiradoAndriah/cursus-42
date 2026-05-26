#!/usr/bin/env python3
import sys
import typing


def main() -> None:
    if len(sys.argv) != 2:
        if sys.argv[0][:2] == "./":
            print(f"Usage: {sys.argv[0][2:]} <file>")
        else:
            print(f"Usage: {sys.argv[0]} <file>")
        sys.exit()
    print("=== Cyber Archives Recovery & Preservation ===")
    filename = sys.argv[1]
    try:
        f: typing.IO[str] = open(filename, "r")
        print(f"Accessing file {filename!r}")
        print("---\n")
        print(f.read())
        print("\n---")
        f.close()
        print(f"File {filename!r} closed.")
    except Exception as e:
        print(f"Accessing file {filename!r}")
        print(f"Error opening file {filename!r}: {e}")


if __name__ == "__main__":
    main()

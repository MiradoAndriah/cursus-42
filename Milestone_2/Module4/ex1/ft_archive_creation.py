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
        print(f"File {filename!r} closed.\n")
    except Exception as e:
        sys.stderr.write(f"Accessing file {filename!r}")
        sys.stderr.write(f"Error opening file {filename!r}: {e}")

    print("Transform data:")
    file: typing.IO[str] = open(filename, "r")
    content = file.read()
    split = content.split("\n")
    new_line = []
    print("---\n")
    for line in split:
        new_line += [line + "#"]
        print(line + "#")
    print("\n---")
    file.close()
    name = input("Enter new file name (or empty): ")
    if name:
        print(f"Saving data to {name!r}")
        new_file: typing.IO[str] = open(name, "w")
        for line in new_line:
            new_file.write(line + "\n")
        new_file.close()
        print(f"Data saved in file {name!r}.")
    else:
        print("Not saving data.")


if __name__ == "__main__":
    main()

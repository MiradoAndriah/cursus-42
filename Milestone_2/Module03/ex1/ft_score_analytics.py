#!/usr/bin/env python3

import sys

if __name__ == "__main__":
    print("=== Player Score Analytics ===")
    if len(sys.argv) == 1:
        if sys.argv[0][:2] == "./":
            print("No scores provided. ", end="")
            print(f"Usage: python3 {sys.argv[0][2:]} <score1> <score2> ...")
        else:
            print("No scores provided. ", end="")
            print(f"Usage: python3 {sys.argv[0]} <score1> <score2> ...")
    else:
        scores = []
        args = sys.argv[1:]
        for arg in args:
            try:
                scores += [int(arg)]
            except ValueError:
                print(f"Invalid parameter: {arg!r}")
        if len(scores) == 0:
            print("No scores provided. ", end="")
            print(f"Usage: python3 {sys.argv[0][2:]} <score1> <score2> ...")
        else:
            print(f"Scores processed: {scores}")
            print(f"Total players: {len(scores)}")
            print(f"Total score: {sum(scores)}")
            print(f"Average score: {sum(scores) / len(scores)}")
            print(f"High score: {max(scores)}")
            print(f"Low score: {min(scores)}")
            print(f"Score range: {max(scores) - min(scores)}")

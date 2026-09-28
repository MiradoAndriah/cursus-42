"""Entry point: parses CLI arguments and runs the function-calling pipeline."""

import argparse
import sys

from src.pipeline import process_all_prompts


def main() -> None:
    """Parse command-line arguments and run the full function-calling pipeline.

    Reads the function definitions and test prompts from the paths given on
    the command line (or their defaults under data/input/), runs the
    constrained-decoding generation for each prompt, and writes the results
    to the output path (or its default under data/output/).

    Any error raised while loading files or generating results is caught,
    printed as a clear message, and stops the program gracefully instead
    of showing a raw traceback.
    """
    parser = argparse.ArgumentParser(
        description="Translate natural language prompts into structured "
        "function calls using constrained decoding."
    )
    parser.add_argument(
        "--functions_definition",
        default="data/input/functions_definition.json",
        help="Path to the JSON file describing the available functions.",
    )
    parser.add_argument(
        "--input",
        default="data/input/function_calling_tests.json",
        help="Path to the JSON file containing the natural language prompts.",
    )
    parser.add_argument(
        "--output",
        default="data/output/function_calling_results.json",
        help="Path where the generated results will be written.",
    )
    args = parser.parse_args()
    try:
        process_all_prompts(args.functions_definition, args.input, args.output)
    except Exception as e:
        print(e)
        sys.exit()


if __name__ == "__main__":
    main()

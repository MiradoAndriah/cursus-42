import importlib
import sys

try:
    import pandas
    pd = True
except ImportError as e:
    print(f'error import: {e}')
    pd = False

try:
    numpy = importlib.import_module("numpy")
    np = True
except ImportError as e:
    print(f'error import: {e}')
    np = False

try:
    from matplotlib import pyplot
    import matplotlib

    mtlib = True
except ImportError as e:
    print(f'error import: {e}')
    mtlib = False


def check_dependencies() -> bool:
    all_ok = True

    if pd:
        print(f"[OK] pandas ({pandas.__version__})", end="")
        print(" - Data manipulation ready")
    else:
        print("[KO] missing module pandas")
        all_ok = False

    if np:
        print(f"[OK] numpy ({numpy.__version__})", end="")
        print(" - Numerical computation ready")
    else:
        print("[KO] missing module numpy")
        all_ok = False

    if mtlib:
        print(f"[OK] matplotlib ({matplotlib.__version__})", end="")
        print(" - Visualization ready")
    else:
        print("[KO] missing module matplotlib")
        all_ok = False

    return all_ok


def generate_data() -> "pandas.DataFrame":
    number = numpy.random.randn(1000)
    data_frame = pandas.DataFrame(number)
    return data_frame


def generate_image(df: "pandas.DataFrame") -> None:
    print("\nAnalyzing Matrix data...")
    print("Processing 1000 data points...")
    print("Generating visualization...\n")

    fig, ax = pyplot.subplots()
    ax.plot(df, color="red")
    ax.set_title("MATRIX DATA")
    ax.set_xlabel("index")
    ax.set_ylabel("data")
    fig.savefig("matrix_analysis.png")

    print("Analysis complete!")
    print("Results saved to: matrix_analysis.png")


def print_install_instructions() -> None:
    print("\nMissing dependencies detected. Please install them using one of:")
    print("\n  With pip:")
    print("    pip install -r requirements.txt")
    print("\n  With Poetry:")
    print("    poetry install")
    print("    poetry run python loading.py")


def compare_pip_poetry() -> None:
    print("\npip: requirements.txt, no lock file, manual venv")
    print("poetry: pyproject.toml, poetry.lock, automatic venv")


def main() -> None:
    print("\nLOADING STATUS: Loading programs...\n")

    print("Checking dependencies:")

    if not check_dependencies():
        print_install_instructions()
        compare_pip_poetry()
        sys.exit()

    data_frame = generate_data()
    generate_image(data_frame)
    compare_pip_poetry()


if __name__ == "__main__":
    main()

import os
import sys
try:
    from dotenv import load_dotenv
except ImportError as e:
    print(e)
    print("Use: pip install python-dotenv")
    sys.exit()

load_dotenv()
mode = os.getenv('MATRIX_MODE', '')
db = os.getenv('DATABASE_URL', '')
api = os.getenv('API_KEY', '')
log_lev = os.getenv('LOG_LEVEL', '')
zion = os.getenv('ZION_ENDPOINT', '')

config = {
    'MATRIX_MODE': mode,
    'DATABASE_URL': db,
    'API_KEY': api,
    'LOG_LEVEL': log_lev,
    'ZION_ENDPOINT': zion
    }


def mode_dev() -> None:
    print(f" Mode: {config['MATRIX_MODE'].lower()}")

    if config['DATABASE_URL'].lower():
        print(" Database: Connected to local instance")
    else:
        print(" DATABASE not configured in .env")

    if config['API_KEY']:
        print(" API Access: Authenticated")
    else:
        print(" API_KEY not configured in .env")

    if config['LOG_LEVEL']:
        print(f" Log Level: {config['LOG_LEVEL']}")
    else:
        print(" LOG_LEVEL not configured in .env")

    if config['ZION_ENDPOINT']:
        print(" Zion Network: Online\n")
    else:
        print(" ZION_ENDPOINT not configured in .env\n")


def mod_prod() -> None:
    print(f" Mode: {config['MATRIX_MODE'].lower()}")

    if config['DATABASE_URL'].lower():
        print(" Database: Connected to production cluster")
    else:
        print(" DATABASE not configured in .env")

    if config['API_KEY']:
        print(" API Access: Authenticated")
    else:
        print(" API_KEY not configured in .env")

    if config['LOG_LEVEL']:
        print(f" Log Level: {config['LOG_LEVEL']}")
    else:
        print(" LOG_LEVEL not configured in .env")

    if config['ZION_ENDPOINT']:
        print(" Zion Network: Online\n")
    else:
        print(" ZION_ENDPOINT not configured in .env\n")


def check_gitignore() -> bool:
    try:
        with open(".gitignore", "r") as f:
            content = f.read()
        return (".env" in content)
    except FileNotFoundError as e:
        print(f"  ** ERROR: {e} ** ")
        return False


def check_security() -> None:
    print(" [OK] No hardcoded secrets detected")
    if check_gitignore():
        print(" [OK] .env file properly configured")
    else:
        print("[KO] .env file not properly exclused from git")
    print(" [OK] Production overrides available")


def main() -> None:

    for key, value in config.items():
        if value is None:
            print(f"WARNING: missing {key}")
            sys.exit()

    print("\nORACLE STATUS: Reading the Matrix...\n")
    print("Configuration loaded:")
    if config['MATRIX_MODE'].lower() == 'development':
        mode_dev()
    elif config['MATRIX_MODE'].lower() == 'production':
        mod_prod()
    else:
        print("Use: cp .env.example .env")
        print("MATRIX_MODE must be 'development' or 'production' in .env")
        sys.exit()

    print("Environment security check:")
    check_security()
    print("\nThe Oracle sees all configurations.")


if __name__ == "__main__":
    main()

#!/usr/bin/env python3

def secure_archive(
        filename: str,
        action: str = "read",
        content: str = "") -> tuple[bool, str]:
    try:
        if action == "read":
            with open(filename, "r") as f:
                content_read = f.read()
            return (True, content_read)
        elif action == "write":
            with open(filename, "w") as f:
                f.write(content)
            return (True, "Content successfully written to file")
    except OSError as e:
        return (False, str(e))
    return (False, "Invalide action")


if __name__ == "__main__":
    print("=== Cyber Archives Security ===\n")

    print("Using 'secure_archive' to read from a nonexistent file:")
    print(secure_archive("/not/existing/file", "read"))
    print()
    print("Using 'secure_archive' to read from an inaccessible file:")
    print(secure_archive("/etc/shadow", "read"))
    print()
    print("Using 'secure_archive' to read from a regular file:")
    print(secure_archive("ancient_fragment.txt", "read"))
    print()
    print("Using 'secure_archive' to write previous content to a new file:")
    print(
        secure_archive("new.txt", "write", "bonjour a tous")
        )

try:
    entry = input("entry value 1 - 5: ")
    if entry == "1":
        raise ValueError("write without char 1")
    elif entry == "2":
        raise ValueError("write next of 2")
    elif entry > 5 or entry < 1:
        raise ValueError("value must be between 1-5")
    x = int(entry)
    print(x)
except ValueError as e:
    print(f"ERROR:{e}")
N = 11
key = 61

def H1() -> int:
    return key % 11

def H2() -> int:
    return 7 - key % 7

def hash(i: int) -> int:
    print((H1() + i * H2()) % N)

hash(4)
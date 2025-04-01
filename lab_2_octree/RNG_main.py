import random
import string


def my_print(*args, separator=", ", end="\n"):
    parts = []
    for arg in args:
        if isinstance(arg, (list, tuple)):
            parts.extend(map(str, arg))
        else:
            parts.append(str(arg))

    print(separator.join(parts), end=end)


def cprint(*args, end="\n"):
    my_print(*args, separator=",", end=end)


def sprint(*args, end="\n"):
    my_print(*args, separator=" ", end=end)


def csprint(*args, end="\n"):
    my_print(*args, separator=", ", end=end)


def scprint(*args, end="\n"):
    my_print(*args, separator=" ,", end=end)


# n_list
n = random.randint(0, 10)  # Number of inputs


sprint(n)

for _ in range(n):
    x = random.randint(-10, 10)  # range of point
    y = random.randint(-10, 10)  # range of point
    z = random.randint(-10, 10)  # range of point
    print(f"{x},{y},{z}")

# n_list queries
n = random.randint(0, 10)  # Number of queries
exists = "e"  # P -> Bool
insert = "i"  # P
find_closest = (
    "c"  # P,int -> *P -> if (nulltpr) {return - <int>::min();}  else { return *P; }
)
options = [exists, insert, find_closest]

for _ in range(n):
    query = random.choice(options)
    print(f"{query}")
    x = random.randint(-10, 10)  # range of point
    y = random.randint(-10, 10)  # range of point
    z = random.randint(-10, 10)  # range of point
    print(f"{x},{y},{z}")

    if query == find_closest:
        r = random.randint(0, 10)  # radius
        print(f"{r}")


print()

# -------------------------------------------------------------------------
# DO NOT TOUCH THESE LINES
# -------------------------------------------------------------------------

my_sol = "main.cpp"
brute_sol = "main_brute.cpp"

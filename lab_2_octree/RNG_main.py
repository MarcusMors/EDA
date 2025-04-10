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
n = random.randint(2, 100)  # Number of inputs


sprint(n)
m = random.randint(-3, 3)
minimum = -10 + m
maximum = 10 + m

for i in range(n):
    x = random.randint(minimum, maximum)  # range of point
    y = random.randint(minimum, maximum)  # range of point
    z = random.randint(minimum, maximum)  # range of point
    if i == 0:
        print(f"{minimum},{minimum},{minimum}")
    if i == n - 1:
        print(f"{maximum},{maximum},{maximum}")
    print(f"{x},{y},{z}")


# n_list queries
n = random.randint(5, 25)  # Number of queries
exists = "e"  # P -> Bool
insert = "i"  # P
find_closest = (
    "c"  # P,int -> *P -> if (nulltpr) {return - <int>::min();}  else { return *P; }
)
options = [exists, insert, find_closest]

for _ in range(n):
    query = random.choice(options)
    print(f"{query}")
    x = random.randint(minimum, maximum)  # range of point
    y = random.randint(minimum, maximum)  # range of point
    z = random.randint(minimum, maximum)  # range of point
    print(f"{x},{y},{z}")

    if query == find_closest:
        r = random.randint(0, (maximum + abs(minimum)) // 2)  # radius
        print(f"{r}")


print()

# -------------------------------------------------------------------------
# DO NOT TOUCH THESE LINES
# -------------------------------------------------------------------------

my_sol="main.cpp"
brute_sol="main_brute.cpp"

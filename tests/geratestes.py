#!/bin/python3

import random
pairs = set()
n=17
while len(pairs) < n:
    x = random.randint(0, (n*n)-1)
    y = random.randint(0, (n*n)-1)
    pairs.add((x, y))

print("1")
print(n)
for i, (x, y) in enumerate(pairs):
    print(f"{x} {y}")

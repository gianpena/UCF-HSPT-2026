pancakes = int(input())

from math import log2,ceil

n = ceil(log2(pancakes+2) - 1)
n = int(n)

ans = (1 << (n+1)) - 2
print(ans-pancakes)

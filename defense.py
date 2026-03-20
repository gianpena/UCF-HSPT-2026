MOD = int(1e9+7)

def f(n):
    return (2 * n**2 + 4 * n + 2) % MOD

n = int(input())

val1 = f(n)

print(val1)

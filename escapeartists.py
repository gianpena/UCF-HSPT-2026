from math import cos,tan

pi = 3.141592653589793
n,s = map(int, input().split())

theta = pi * (n-2) / n

r2 = s / 2 / cos(theta/2)
r1 = s / 2 * tan(theta/2)

print(f'{r2-r1:.8f}')

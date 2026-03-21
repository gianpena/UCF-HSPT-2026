n,m = map(int, input().split())

difficulties = list(map(int, input().split()))
p = []
s = 0
for d in difficulties:
    s += d
    p.append(s)

def rangesum(i,j):
    ans = p[j]
    if i:
        ans -= p[i-1]
    return ans

for i in range(m):
    query = list(input().split())
    match query[0]:
        case 'sum':
            a,b = map(int, query[1:])
            a -= 1; b -= 1
            print(rangesum(a,b))
        case 'swap':
            a = int(query[1])
            a -= 1
            p[a] -= difficulties[a]
            p[a] += difficulties[a+1]
            difficulties[a], difficulties[a+1] = difficulties[a+1], difficulties[a]

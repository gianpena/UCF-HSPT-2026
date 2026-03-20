from functools import cache

n = int(input())
prices = [tuple(map(int, input().split())) for _ in range(n)]
q = int(input())

def window(s, e):
    def begin(p):
        ans = n
        l,r = 0,n-1
        while l <= r:
            m = l + ((r-l)>>1)
            if prices[m][0] >= p:
                ans = m
                r = m-1
            else:
                l = m+1
        
        return ans

    def end(p):
        ans = n
        l,r = 0,n-1
        while l <= r:
            m = l + ((r-l)>>1)
            if prices[m][0] <= p:
                ans = m
                l = m+1
            else:
                r = m-1
        
        return ans
    
    return begin(s), end(e)

@cache
def log2(n):
    ans = -1
    while n:
        ans += 1
        n >>= 1
    return ans

range_min = [[float('inf') for j in range(log2(n)+1)] for i in range(n)]
range_max = [[float('-inf') for j in range(log2(n)+1)] for i in range(n)]

for i in range(n):
    range_min[i][0] = prices[i][1]
for l in range(1,log2(n)+1):
    last = n-(1<<l)
    for i in range(last+1):
        range_min[i][l] = min(range_min[i][l-1], range_min[i+(1<<(l-1))][l-1])

for i in range(n):
    range_max[i][0] = prices[i][1]
for l in range(1,log2(n)+1):
    last = n-(1<<l)
    for i in range(last+1):
        range_max[i][l] = max(range_max[i][l-1], range_max[i+(1<<(l-1))][l-1])

def stonks(p,l,r):
    s = log2(r-l+1)
    highest = max(range_max[l][s], range_max[r-(1<<s)+1][s])
    lowest = min(range_min[l][s], range_min[r-(1<<s)+1][s])

    return lowest <= p <= highest

for _ in range(q):
    p, s, e = map(int, input().split())
    l,r = window(s,e)
    if n in [l,r]:
        print('Not Necessarily Stonks!')
        continue
    
    if l<=r and stonks(p, l, r):
        print('Stonks!')
    else:
        print('Not Necessarily Stonks!')

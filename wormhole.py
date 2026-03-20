from heapq import heappush, heappop

n = int(input())
edges = []
sum_cost = 0

for i in range(1,n):
    cost = 2*i+1
    sum_cost += cost

print(sum_cost)
for k in range(n-2,0,-1):
    sum_cost -= k
    print(sum_cost)

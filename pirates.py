x1,y1,x2,y2 = map(int, input().split())
def inside(x,y):
    return x1 <= x <= x2 and y1 <= y <= y2

n = int(input())
all_aboard = True
for i in range(n):
    x,y = map(int, input().split())
    all_aboard = all_aboard and inside(x,y)

print('A boat full of pirates!' if all_aboard else 'Pirate overboard!')

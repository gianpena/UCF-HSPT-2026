import sys
n = int(input())
truck_bed = [list(input()) for _ in range(n)]
q = int(input())

VERTICAL_MOVES = ['ACCELERATE', 'BRAKE']
HORIZONTAL_MOVES = ['LEFT', 'RIGHT']

moves = []
for i in range(q):
    moves.append(input())

vertical, horizontal = 0,0
i = 0
while i < q and ((vertical + (moves[i] in VERTICAL_MOVES) == 0) ^ (horizontal + (moves[i] in HORIZONTAL_MOVES) == 0)):
    vertical += (moves[i] in VERTICAL_MOVES)
    horizontal += (moves[i] in HORIZONTAL_MOVES)
    i += 1


def simulate_vertical(top):
    arr = [0] * n
    for col in range(n):
        count = sum(truck_bed[i][col] == '#' for i in range(n))
        arr[col] = count
    
    for col in range(n):
        args = (arr[col],) if top else (n-1, n-arr[col]-1, -1)
        for row in range(*args):
            truck_bed[row][col] = '#'
        
        args = (arr[col], n) if top else (n-arr[col]-1, -1, -1)
        for row in range(*args):
            truck_bed[row][col] = '.'

def simulate_horizontal(left):
    arr = [0] * n
    for row in range(n):
        count = sum(truck_bed[row][i] == '#' for i in range(n))
        arr[row] = count
    
    for row in range(n):
        args = (arr[row],) if left else (n-1, n-arr[row]-1, -1)
        for col in range(*args):
            truck_bed[row][col] = '#'
        
        args = (arr[row], n) if left else (n-arr[row]-1, -1, -1)
        for col in range(*args):
            truck_bed[row][col] = '.'

def ans():
    print('\n'.join([''.join(row) for row in truck_bed]))
    sys.exit(0)

if vertical:
    simulate_vertical(moves[i-1] == 'BRAKE')
else:
    simulate_horizontal(moves[i-1] == 'RIGHT')

if i == q:
    ans()

if moves[i] in VERTICAL_MOVES:
    simulate_vertical(moves[i] == 'BRAKE')
else:
    simulate_horizontal(moves[i] == 'RIGHT')

i += 1
if i == q:
    ans()

top,left = -1,-1
while i < q:
    if moves[i] in VERTICAL_MOVES:
        top = moves[i] == 'BRAKE'
    else:
        left = moves[i] == 'RIGHT'
    i += 1

if top != -1:
    simulate_vertical(top)
if left != -1:
    simulate_horizontal(left)

ans()
from sys import stdin
n = int(stdin.readline().strip())
p = {}

for k in range(n):
    x1, y1, x2, y2 = list(map(int, stdin.readline().strip().split()))
    for i in range(x1, x2):
        for j in range(y1, y2):
            p[f'{i}{j}'] = k

for i in range(n):
    print(list(k for k in p.values()).count(i))

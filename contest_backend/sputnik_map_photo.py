from sys import stdin
n = int(stdin.readline())
p = {}

for k in range(n):
    x1, y1, x2, y2 = list(map(int, stdin.readline().split()))
    for i in range(x1, x2):
        for j in range(y1, y2):
            p['{}{}'.format(i, j)] = k

for i in range(n):
    print(list(k for k in p.values()).count(i))

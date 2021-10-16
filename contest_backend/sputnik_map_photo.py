from sys import stdin
n = int(stdin.readline().strip())
p = {}

for k in range(n):
    x1, y1, x2, y2 = [int(n) for n in stdin.readline().split(" ")]
    for i in range(x1, x2):
        for j in range(y1, y2):
            p[str(i) + str(j)] = k

for i in range(n):
    print(list(k for k in p.values()).count(i))

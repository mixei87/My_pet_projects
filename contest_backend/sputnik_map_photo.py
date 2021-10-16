from sys import stdin
n = int(stdin.readline().strip())
val = []
key = []

for k in range(n):
    x1, y1, x2, y2 = list(map(int, stdin.readline().strip().split()))
    for i in range(x1, x2):
        for j in range(y1, y2):
            q = f'{i}{j}'
            if q in key:
                val[key.index(q)] = k
            else:
                key.append(q)
                val.append(k)

for i in range(n):
    print(val.count(i))

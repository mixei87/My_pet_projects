from sys import stdin
n = int(stdin.readline())
key = []

for k in range(n):
    x1, y1, x2, y2 = [int(e) for e in stdin.readline().split()]
    for i in range(x1, x2):
        for j in range(y1, y2):
            q = f'{i}{j}'
            qq = [m for m in key if m[0] == q]
            if len(qq) == 0:
                key.append([q, k])
            else:
                key[key.index(qq[0])] = [q, k]

tmp = [i[1] for i in key]
for i in range(n):
    print(tmp.count(i))

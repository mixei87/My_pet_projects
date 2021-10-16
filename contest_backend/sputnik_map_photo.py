from sys import stdin
n = int(stdin.readline().strip())
p = []

for k in range(n):
    x1, y1, x2, y2 = list(map(int, stdin.readline().strip().split()))
    for i in range(x1, x2):
        for j in range(y1, y2):
            flag = True
            for m in p:
                if m[0] == i and m[1] == j:
                    p.remove(m)
                    p.append((i, j, k))
                    flag = False
                    break
            if flag:
                p.append((i, j, k))

tmp = [i[2] for i in p]
for i in range(n):
    print(tmp.count(i))

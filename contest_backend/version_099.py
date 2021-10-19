from sys import stdin

a, b, c = [int(i) for i in stdin.readline().split()]
q = int(stdin.readline())
rule = [[int(i) for i in stdin.readline().split()] for j in range(q)]

alphabet = {1: 'i', 2: 'j', 3: 'k'}
not_right = []
for i, j, k, m in ((i, j, k, m) for i in range(1, a+1) for j in range(1, b+1) for k in range(1, c+1) for m in rule):
    if (globals()[alphabet[m[0]]] >= m[1] and globals()[alphabet[m[2]]] < m[3]
            and (i, j, k) not in not_right):
        not_right.append((i, j, k))
print(a*b*c - len(not_right))

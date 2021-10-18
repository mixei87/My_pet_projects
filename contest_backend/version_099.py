from sys import stdin

a, b, c = [int(i) for i in stdin.readline().split()]
q = int(stdin.readline())
rule = [[int(i) for i in stdin.readline().split()] for j in range(q)]

not_right = []
for i in range(1, a+1):
    for r in [[j, k] for j in range(1, b+1) for k in range(1, c+1)]:
        t = [i, r[0], r[1]]
        for m in rule:
            if m[0] == 1:
                x = t[0]
            elif m[0] == 2:
                x = t[1]
            elif m[0] == 3:
                x = t[2]
            if m[2] == 1:
                y = t[0]
            elif m[2] == 2:
                y = t[1]
            elif m[2] == 3:
                y = t[2]
            if x >= m[1] and y < m[3]:
                if t not in not_right:
                    not_right.append(t)
print(a*b*c - len(not_right))

from sys import stdin

n, m = [int(i) for i in stdin.readline().split()]
glass = [[j for j in stdin.readline().strip()] for i in range(n)]
k = int(stdin.readline())
coctails = [(m[2], int(m[1])) for m in [
    [j for j in stdin.readline().split()] for i in range(k)]]

num = n-2
for i in coctails:
    for j in range(i[1]):
        for k in range(m):
            if glass[num][k] == ' ':
                glass[num][k] = i[0]
        num -= 1

for i in glass:
    for j in i:
        print(j, end='')
    print()

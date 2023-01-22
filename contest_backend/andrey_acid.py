from sys import stdin

n = int(stdin.readline())
a = list(map(int, stdin.readline().strip().split()))

for i in range(1, n):
    if a[i] < a[i-1]:
        print(-1)
        break
else:
    print(a[n-1]-a[0])

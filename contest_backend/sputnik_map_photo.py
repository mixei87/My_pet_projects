from sys import stdin
n = int(stdin.readline().strip())
photo_pixels = {}

for k in range(n):
    x1, y1, x2, y2 = list(map(int, stdin.readline().strip().split()))
    for i in filter(lambda x: x != 0, range(x1, x2+1)):
        for j in filter(lambda y: y != 0, range(y1, y2+1)):
            photo_pixels[(i, j)] = k
del x1, y1, x2, y2, k
tmp = [0] * n
for j in photo_pixels.values():
    tmp[j] += 1
del photo_pixels
for i in tmp:
    print(i)

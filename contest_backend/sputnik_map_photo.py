from sys import stdin
n = int(stdin.readline().strip())
photo_pixels = {}

for k in range(n):
    x1, y1, x2, y2 = list(map(int, stdin.readline().strip().split()))
    for i in filter(lambda x: x != 0, range(x1, x2+1)):
        for j in filter(lambda y: y != 0, range(y1, y2+1)):
            photo_pixels[(i, j)] = k

tmp = [i for i in photo_pixels.values()]
for i in range(n):
    counter = tmp.count(i)
    print(counter)
    for j in range(counter):
        tmp.remove(i)

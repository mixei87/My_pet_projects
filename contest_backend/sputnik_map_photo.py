from sys import stdin
n = int(stdin.readline().strip())
photo_pixels = {}
coord = []

for k in range(n):
    coord.append(list(map(int, stdin.readline().strip().split())))
    for i in filter(lambda x: x != 0, range(coord[k][0], coord[k][2]+1)):
        for j in filter(lambda y: y != 0, range(coord[k][1], coord[k][3]+1)):
            photo_pixels[(i, j)] = k

for i in range(n):
    print(tuple(k for k in photo_pixels.values()).count(i))

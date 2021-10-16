from sys import stdin
n = int(stdin.readline().strip())
photo_pixels = {}
for k in range(n):
    x1, y1, x2, y2 = list(map(int, stdin.readline().strip().split()))
    for i in range(x1, x2):
        for j in range(y1, y2):
            photo_pixels[str(i)+str(j)] = k
for i in range(n):
    print(list(k for k in photo_pixels.values()).count(i))

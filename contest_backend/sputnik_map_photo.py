from sys import stdin
n = int(stdin.readline().strip())
photo_pixels = {}

for k in range(n):
    x1, y1, x2, y2 = list(map(int, stdin.readline().strip().split()))
    for i in range(x1, x2+1):
        for j in range(y1, y2+1):
            if i != 0 and j != 0:
                photo_pixels[(i, j)] = k

actual_number_square = [k for k in photo_pixels.values()]
for i in range(n):
    print(actual_number_square.count(i))

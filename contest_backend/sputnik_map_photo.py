from sys import stdin
n = int(stdin.readline().strip())
photo_pixels = {}

for k in range(n):
    x1, y1, x2, y2 = tuple(map(int, stdin.readline().strip().split()))
    for i in range(x1, x2+1):
        for j in range(y1, y2+1):
            if i != 0 and j != 0:
                photo_pixels[(i, j)] = k


actual_number_square = {}
for k in photo_pixels.values():
    res = actual_number_square.get(k)
    if res == None:
        actual_number_square[k] = 1
    else:
        actual_number_square[k] = res + 1

for i in range(n):
    print(actual_number_square.get(i, 0))

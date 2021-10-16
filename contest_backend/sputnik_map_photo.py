from sys import stdin
n = int(stdin.readline().strip())
coordinates = [list(map(int, stdin.readline().strip().split()))
               for i in range(n)]

photo_pixels = set()
actual_number_square = []
for k in reversed(coordinates):
    x1, y1, x2, y2 = k[0], k[1], k[2], k[3]
    count = 0
    for i in filter(lambda x: x != 0, range(x1, x2+1)):
        for j in filter(lambda y: y != 0, range(y1, y2+1)):
            if (i, j) not in photo_pixels:
                photo_pixels.add((i, j))
                count += 1
    actual_number_square.append(count)

for i in reversed(actual_number_square):
    print(i)

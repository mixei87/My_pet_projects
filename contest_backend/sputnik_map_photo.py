from sys import stdin
n = int(stdin.readline().strip())
coordinates = [list(map(int, stdin.readline().strip().split()))
               for i in range(n)]

photo_pixels = {}
N = n
for k in reversed(coordinates):
    x1, y1, x2, y2 = k[0], k[1], k[2], k[3]
    count = 0
    n -= 1
    for i in filter(lambda x: x != 0, range(x1, x2+1)):
        for j in filter(lambda y: y != 0, range(y1, y2+1)):
            if (i, j) not in photo_pixels:
                count += 1
                photo_pixels[(i, j)] = (n, count)


actual_number_square = {}
for number, counter in photo_pixels.values():
    res = actual_number_square.get(number)
    if res == None or counter > res:
        actual_number_square[number] = counter

for i in range(N):
    print(actual_number_square.get(i, 0))

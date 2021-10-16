from sys import stdin
n = int(stdin.readline().strip())
coord = []
photo_pixels = {}

for k in range(n):
    coord.append(list(map(int, stdin.readline().strip().split())))
    for i in filter(lambda x: x != 0, range(coord[k][0], coord[k][2]+1)):
        for j in filter(lambda y: y != 0, range(coord[k][1], coord[k][3]+1)):
            photo_pixels[(i, j)] = k


actual_number_square = {}
for number in photo_pixels.values():
    res = actual_number_square.get(number)
    if res == None:
        actual_number_square[number] = 1
    else:
        actual_number_square[number] = res + 1

for i in range(n):
    print(actual_number_square.get(i, 0))

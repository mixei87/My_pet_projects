from sys import stdin
n = int(stdin.readline().strip())

co = []
for m in range(n):
    co.append(list(map(int, stdin.readline().strip().split())))

photo_pixels = {str(i)+str(j): k for k in range(n) for i in filter(lambda x: x != 0, range(
    co[k][0], co[k][2]+1)) for j in filter(lambda y: y != 0, range(co[k][1], co[k][3]+1))}

for i in range(n):
    print(list(k for k in photo_pixels.values()).count(i))

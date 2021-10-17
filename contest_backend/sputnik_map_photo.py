from sys import stdin
n = int(stdin.readline())


class Photo:
    __slots__ = ('coord', 'num')

    def __init__(self):
        self.coord = []
        self.num = []


t_c = [[int(e) for e in stdin.readline().split()] for _ in range(n)]
photo = Photo()
for k in range(n):
    for i in range(t_c[k][0], t_c[k][2]):
        for j in range(t_c[k][1], t_c[k][3]):
            str_c = str(i)+str(j)
            if str_c not in photo.coord:
                photo.coord.append(str_c)
                photo.num.append(k)
            else:
                photo.num[photo.coord.index(str_c)] = k

for i in range(n):
    print(photo.num.count(i))

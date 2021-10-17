from sys import stdin
n = int(stdin.readline())


class Photo:
    __slots__ = ('coord', 'num')

    def __init__(self):
        self.coord = []
        self.num = []


t_c = [[int(e) for e in stdin.readline().split()] for k in range(n)]
photo = Photo()
for k in reversed(t_c):
    counter = 0
    for i in range(k[0], k[2]):
        for j in range(k[1], k[3]):
            str_c = str(i)+str(j)
            if str_c not in photo.coord:
                photo.coord.append(str_c)
                counter += 1
    photo.num.append(counter)
for i in reversed(photo.num):
    print(i)

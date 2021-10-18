from sys import stdin
n = int(stdin.readline())


class Photo:
    __slots__ = ('num')

    def __init__(self):
        self.num = [[]]


t_c = [[int(e) for e in stdin.readline().split()]
       for k in range(n)]
photo = Photo()
for k in reversed(t_c):
    counter = 0
    tmp = list(filter(lambda x: x not in photo.num, [f'{i}{j}' for i in range(
        k[0], k[2]) for j in range(k[1], k[3])]))
    photo.num.extend(tmp)
    photo.num[0].append(len(tmp))
[print(i) for i in reversed(photo.num[0])]

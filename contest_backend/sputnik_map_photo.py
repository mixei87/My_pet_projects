from sys import stdin
n = int(stdin.readline())


class Photo:
    __slots__ = ('listPhoto')

    def __init__(self):
        self.listPhoto = {}


t_c = tuple(int(e) for k in range(n) for e in stdin.readline().split())
photo = Photo()
photo.listPhoto = {f'{i}{j}': k for k in range(n) for i in range(
    t_c[k*4], t_c[k*4 + 2]) for j in range(t_c[k*4 + 1], t_c[k*4 + 3])}

for i in range(n):
    print([k for k in photo.listPhoto.values()].count(i))

from sys import stdin
# from sys import getsizeof
n = int(stdin.readline())


class Photo:
    __slots__ = ('listPhoto')

    def __init__(self):
        self.listPhoto = {}


t_c = [[int(e) for e in stdin.readline().split()] for _ in range(n)]
photo = Photo()
photo.listPhoto = {f'{i}{j}': k for k in range(n) for i in range(
    t_c[k][0], t_c[k][2]) for j in range(t_c[k][1], t_c[k][3])}

for i in range(n):
    print([k for k in photo.listPhoto.values()].count(i))

# print(getsizeof(photo))

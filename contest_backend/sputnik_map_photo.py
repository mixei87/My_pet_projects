from sys import stdin
n = int(stdin.readline())


class Photo:
    __slots__ = ('name', 'listPhoto')

    def __init__(self, name=""):
        self.name = name
        self.listPhoto = {}


photo = Photo('mymap')
for k in range(n):
    x1, y1, x2, y2 = [int(e) for e in stdin.readline().split()]
    for i in range(x1, x2):
        for j in range(y1, y2):
            photo.listPhoto[f'{i}{j}'] = k

for i in range(n):
    print([k for k in photo.listPhoto.values()].count(i))

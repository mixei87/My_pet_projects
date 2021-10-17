from dataclasses import dataclass
from sys import stdin
n = int(stdin.readline())


class Photo:
    __slots__ = ('name', 'listPhoto')

    def __init__(self, name=""):
        self.name = name
        self.listPhoto = []


@dataclass
class dataPhoto:
    __slots__ = ('x', 'y', 'counter')
    x: int
    y: int
    counter: int


photo = Photo('mymap')
for k in range(n):
    x1, y1, x2, y2 = [int(e) for e in stdin.readline().split()]
    for i in range(x1, x2):
        for j in range(y1, y2):
            trt = [a for a in photo.listPhoto if a.x == i and a.y == j]
            if len(trt) == 0:
                photo.listPhoto.extend([dataPhoto(i, j, k)])
            else:
                trt[0].counter = k

tmp = [i.counter for i in photo.listPhoto]
for i in range(n):
    print(tmp.count(i))

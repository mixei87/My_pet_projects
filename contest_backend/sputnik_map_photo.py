from sys import stdin
n = int(stdin.readline())


class Photo:
    __slots__ = ('map_coords', 'set_coords', 'tmp_coords', 'res')

    def __init__(self):
        self.map_coords = []
        self.set_coords = set()
        self.tmp_coords = []
        self.res = []


photo = Photo()
photo.map_coords = [tuple([int(i) for i in stdin.readline().split()])
                    for k in range(n)]


def square_new(rect):
    return (rect[2]-rect[0])*(rect[3]-rect[1])


def square_intersection(temp, curr):
    x1_t, y1_t, x2_t, y2_t = temp[0], temp[1], temp[2], temp[3]
    x1, y1, x2, y2 = curr[0], curr[1], curr[2], curr[3]
    a = b = 0
    if x1_t < x1 <= x2 < x2_t:
        a = x2 - x1
    elif x1 <= x1_t <= x2 <= x2_t:
        a = x2 - x1_t
    elif x1_t <= x1 <= x2_t <= x2:
        a = x2_t - x1
    elif x1 <= x1_t <= x2_t <= x2:
        a = x2_t - x1_t
    if y1_t <= y1 <= y2 <= y2_t:
        b = y2 - y1
    elif y1 <= y1_t <= y2 <= y2_t:
        b = y2 - y1_t
    elif y1_t <= y1 <= y2_t <= y2:
        b = y2_t - y1
    else:
        b = y2_t - y1_t
    if a < 0 or b < 0:
        return 0
    return a * b


photo.set_coords = set()
for current in reversed(photo.map_coords):
    s_new = square_new(current)
    # ненулевая площадь
    if s_new:
        photo.tmp_coords = []
        for template in photo.set_coords:
            s_new -= square_intersection(template, current)

            # !!! fix condition
            if current > template:
                photo.tmp_coords.append(template)
        for template in photo.tmp_coords:
            photo.set_coords.remove(template)
        photo.set_coords.add(current)
    photo.res.append(s_new)
    # for tmp in [f'{i}{j}' for i in range(map_coords[0], map_coords[2]) for j in range(map_coords[1], map_coords[3])]:
    #     if tmp not in photo.tpl:
    #         photo.tpl += (tmp,)
    #         photo.num.append(k)
    #     else:
    #         photo.num[photo.tpl.index(tmp)] = k
for k in reversed(photo.res):
    print(k)

reader = open('input_sputnik_map_photo.txt', 'r')
n = int(reader.readline())


class Photo:
    __slots__ = ('map_coords', 'set_coords',
                 'tmp_add_coords', 'tmp_remove_coords', 'tmp_sides', 'res', 'sides')

    def __init__(self):
        self.map_coords = []
        self.set_coords = set()
        self.tmp_add_coords = []
        self.tmp_remove_coords = []
        self.tmp_sides = []
        self.res = []
        self.sides = {}


photo = Photo()
photo.map_coords = [tuple([int(i) for i in reader.readline().split()])
                    for k in range(n)]


def square_rect(rect):
    return (rect[2]-rect[0])*(rect[3]-rect[1])


def length_one_coordinate(z1_t, z2_t, z1, z2):
    len = 0
    if z1_t < z1 <= z2 < z2_t:
        len = z2 - z1
    elif z1 <= z1_t <= z2 <= z2_t:
        len = z2 - z1_t
    elif z1_t <= z1 <= z2_t <= z2:
        len = z2_t - z1
    elif z1 <= z1_t <= z2_t <= z2:
        len = z2_t - z1_t
    return len


def square_intersection(temp, curr):
    x1_t, y1_t, x2_t, y2_t = temp[0], temp[1], temp[2], temp[3]
    x1, y1, x2, y2 = curr[0], curr[1], curr[2], curr[3]
    a = length_one_coordinate(x1_t, x2_t, x1, x2)
    b = length_one_coordinate(y1_t, y2_t, y1, y2)
    if a < 0 or b < 0:
        return 0
    return a * b


def change_rect(temp, curr):
    '''разбить исходную область на 1, 2 или 3 новых области'''
    x1_t, y1_t, x2_t, y2_t = temp[0], temp[1], temp[2], temp[3]
    x1, y1, x2, y2 = curr[0], curr[1], curr[2], curr[3]
    # одна область
    if x1 <= x1_t < x2 < x2_t and y1 <= y1_t <= y2_t <= y2:
        photo.tmp_add_coords.append((x2, y1_t, x2_t, y2_t))
    elif x1_t < x1 < x2_t <= x2 and y1 <= y1_t <= y2_t <= y2:
        photo.tmp_add_coords.append((x1_t, y1_t, x1, y2_t))
    elif x1 <= x1_t <= x2_t <= x2 and y1 <= y1_t < y2 < y2_t:
        photo.tmp_add_coords.append((x1_t, y2, x2_t, y2_t))
    elif x1 <= x1_t <= x2_t <= x2 and y1_t < y1 < y2_t <= y2:
        photo.tmp_add_coords.append((x1_t, y1_t, x2_t, y1))
    # две области
    elif x1_t < x1 < x2 < x2_t and y1 <= y1_t <= y2_t <= y2:
        photo.tmp_add_coords.append((x1_t, y1_t, x1, y2_t))
        photo.tmp_add_coords.append((x2, y1_t, x2_t, y2_t))
    elif x1 <= x1_t <= x2_t <= x2 and y1_t < y1 < y2 < y2_t:
        photo.tmp_add_coords.append((x1_t, y1_t, x2_t, y1))
        photo.tmp_add_coords.append((x1_t, y2, x2_t, y2_t))
    elif x1 <= x1_t < x2 < x2_t and y1 <= y1_t < y2 < y2_t:
        photo.tmp_add_coords.append((x1_t, y2, x2, y2_t))
        photo.tmp_add_coords.append((x2, y1_t, x2_t, y2_t))
    elif x1 <= x1_t < x2 < x2_t and y1_t < y1 < y2_t <= y2:
        photo.tmp_add_coords.append((x1_t, y1_t, x2, y1))
        photo.tmp_add_coords.append((x2, y1_t, x2_t, y2_t))
    elif x1_t < x1 < x2_t <= x2 and y1 <= y1_t < y2 < y2_t:
        photo.tmp_add_coords.append((x1_t, y1_t, x1, y2_t))
        photo.tmp_add_coords.append((x1, y2, x2_t, y2_t))
    elif x1_t < x1 < x2_t <= x2 and y1_t < y1 < y2_t <= y2:
        photo.tmp_add_coords.append((x1_t, y1_t, x1, y2_t))
        photo.tmp_add_coords.append((x1, y1_t, x2_t, y1))
    # 3 области
    elif x1 <= x1_t < x2 < x2_t and y1_t < y1 < y2 < y2_t:
        photo.tmp_add_coords.append((x1_t, y1_t, x2, y1))
        photo.tmp_add_coords.append((x1_t, y2, x2, y2_t))
        photo.tmp_add_coords.append((x2, y1_t, x2_t, y2_t))
    elif x1_t < x1 < x2_t <= x2 and y1_t < y1 < y2 < y2_t:
        photo.tmp_add_coords.append((x1_t, y1_t, x1, y2_t))
        photo.tmp_add_coords.append((x1, y1_t, x2_t, y1))
        photo.tmp_add_coords.append((x1, y2, x2_t, y2_t))
    elif x1_t < x1 < x2 < x2_t and y1_t < y1 < y2_t <= y2:
        photo.tmp_add_coords.append((x1_t, y1_t, x1, y2_t))
        photo.tmp_add_coords.append((x1, y1_t, x2, y1))
        photo.tmp_add_coords.append((x2, y1_t, x2_t, y2_t))
    elif x1_t < x1 < x2 < x2_t and y1 <= y1_t < y2 < y2_t:
        photo.tmp_add_coords.append((x1_t, y1_t, x1, y2_t))
        photo.tmp_add_coords.append((x1, y2, x2, y2_t))
        photo.tmp_add_coords.append((x2, y1_t, x2_t, y2_t))
    photo.tmp_remove_coords.append(template)


def find_sides_rect(arr):
    return (arr[0], arr[1], arr[2], arr[1]), (arr[0], arr[1], arr[0], arr[3]),\
        (arr[0], arr[3], arr[2], arr[3]), (arr[2], arr[1], arr[2], arr[3])


for current in reversed(photo.map_coords):
    if current not in photo.set_coords:
        s_new = square_rect(current)
    else:
        s_new = 0
    # проверка на ненулевую площадь
    if s_new:
        for template in photo.set_coords:
            s_inter = square_intersection(template, current)
            # если есть пересечение
            if s_inter:
                s_new -= s_inter
                # если фигуры одинаковые или новая полностью входит в старую
                if s_new == 0:
                    break
                change_rect(template, current)
        else:
            for template in photo.tmp_remove_coords:
                photo.set_coords.remove(template)
                # !!! FIX
                #  надо удалять соответсвующие стороны в словаре
                # find_sides_rect(template)
            for template in photo.tmp_add_coords:
                for side in find_sides_rect(template):
                    if side in photo.sides:
                        pass
                        # !!! FIX
                        # нужно соединить 2 прямоугольника в один и:
                        # обновить словарь с новыми сторонами
                        # удалить координаты старого прямоугольника из сета
                        # добавить координаты нового прямоугольника в сет
                        break
                    else:
                        photo.tmp_sides.append(side)
                else:
                    photo.sides.update({key: val for key, val in zip(
                        photo.tmp_sides, (template + end for end in (('d',), ('l',), ('u',), ('r',))))})
                    photo.tmp_sides.clear()
                    photo.set_coords.add(template)
            photo.set_coords.add(current)
        photo.tmp_remove_coords.clear()
        photo.tmp_add_coords.clear()
    photo.res.append(s_new)
for k in reversed(photo.res):
    print(k)

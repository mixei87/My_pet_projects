from random import randint


def random_x1y1x2y2():
    x1 = randint(-1e9, 0)
    y1 = randint(-1e9, 0)
    x2 = randint(0, 1e9)
    y2 = randint(0, 1e9)

    return x1, y1, x2, y2


writer = open('input_sputnik_map_photo.txt', 'w')
n = randint(1, 5)
writer.write(f'{n}\n')
for i in range(n):
    for j in random_x1y1x2y2():
        writer.write(f'{j} ')
    writer.write(f'\n')
writer.close()

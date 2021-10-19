from random import randint


def random_n(n):
    return randint(1, n)


def random_xy():
    x, y = 0, 0
    while (x == y):
        x = randint(1, 3)
        y = randint(1, 3)
    return x, y


def random_xykm():
    dict_abc = {1: 'n_a', 2: 'n_b', 3: 'n_c'}
    x, y = random_xy()
    k = random_n(globals()[dict_abc[x]])
    m = random_n(globals()[dict_abc[y]])
    return x, k, y,  m


writer = open('input.txt', 'w')
n_a, n_b, n_c = random_n(80), random_n(80), random_n(80)
writer.write(f'{(n_a)} {n_b} {n_c}\n')
q = randint(1, 4)
writer.write(f'{q}\n')
for i in range(q):
    for j in random_xykm():
        writer.write(f'{j} ')
    writer.write(f'\n')
writer.close()

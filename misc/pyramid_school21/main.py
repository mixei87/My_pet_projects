def print_symbols(countsymbols):
    for i in range(len(countsymbols[0])):
        for j in range(countsymbols[1][i]):
            print(countsymbols[0][i], end='')
    print('')

def recurs_one_step(x, n, i, countsymbols):
    if n == 1 and i == 1:
        print_symbols(countsymbols)
        return countsymbols
    if n > 1 and i == 1:
        countsymbols[1][0] += n // 2 + 2
        countsymbols = recurs_one_step(x, n - 1, n + 1, countsymbols)
        countsymbols[1][0] -= n // 2 + 2
        countsymbols[1][2] += (n // 2 + 2) * 2
        print_symbols(countsymbols)
        return countsymbols
    countsymbols[1][0] += 1
    recurs_one_step(x, n, i - 1, countsymbols)
    countsymbols[1][0] -= 1
    if n == x and 2 < i <= x + 2:
        if countsymbols[1][6] == 0:
            countsymbols[1][6] = (countsymbols[1][2] + 2 - x) // 2
        else:
            countsymbols[1][6] += 1
        countsymbols[1][2] = countsymbols[1][6] + (x + 1) % 2
        if x != 1 and i == (n + 1) // 2 + 2:
            countsymbols[1][4] = 1
            if x < 4:
                countsymbols[1][3] = x-1
            else:
                countsymbols[1][3] = x - 2
                countsymbols[1][5] = 1
        else:
            countsymbols[1][3] = x
            countsymbols[1][4] = 0
            countsymbols[1][5] = 0
    else:
        countsymbols[1][2] += 2
    print_symbols(countsymbols)
    return countsymbols

def pyramid(n):
    if type(n) != int:
        print('Можно вводить только целое число')
        return
    if n < 1:
        print('Значение меньше 1')
        return
    countsymbols = [[' ', '/', '*', '|', '$', '|', '*', '\\'], [0, 1, 1, 0, 0, 0, 0, 1]]
    recurs_one_step(n, n, n + 2, countsymbols)

pyramid(int(input('Введите целое число: ')))

# ''' Дан массив n*m: состоит только из 0 или 1. Найти минимальное количество обменов
#     значений для соблюдения условия: каждая строка и каждый столбец должны быть
#     отсортированы по значениям от 0 до 1'''
from sys import stdin
from copy import deepcopy


def print_arr(*arr):
    '''печать массива'''
    print('-' * 100)
    for i in range(n):
        for num in arr:
            for j in range(m):
                print('% 4d' % num[i][j], end=' ')
            print(' | ', end='')
        print()


def change_B(arrB, key):
    '''матрица удалённости элементов от угла'''
    count = 0
    for i in range(n):
        for j in range(m):
            if key:
                # нашли матрицу удалённости от нижнего правого угла
                arrB[i][j] = (n - i) * (m - j) - 1
            else:
                # нашли матрицу удалённости от верхнего левого угла
                arrB[i][j] = (i + 1) * (j + 1) - 1


def change_local_C0(y, x, arrC, op='+'):
    arg = 1
    if op == '-':
        arg *= -1
    for r in range(y, n):
        for t in range(x, m):
            if r != y or t != x:
                arrC[r][t] += arg


def change_local_C1(y, x, arrC, op='+'):
    arg = 1
    if op == '-':
        arg *= -1
    for r in range(y, -1, -1):
        for t in range(x, -1, -1):
            if r != y or t != x:
                arrC[r][t] += arg


def change_all_C(arr0, arr1):
    for i in range(n):
        for j in range(m):
            if A[i][j] == 1:
                change_local_C1(i, j, arr1, '+')
            else:
                change_local_C0(i, j, arr0, '+')


def change_D0(arrC0):
    for i in range(n):
        for j in range(m):
            if A[i][j] == 0:
                D0[i][j] = B0[i][j] - arrC0[i][j]
            else:
                D0[i][j] = 0


def change_D1(arrC1):
    for i in range(n):
        for j in range(m):
            if A[i][j] == 1:
                D1[i][j] = B1[i][j] - arrC1[i][j]
            else:
                D1[i][j] = 0


def max_index0():
    '''максимальный индекс в массиве D'''
    flag_exit = 0
    for i in range(n-1, -1, -1):
        for j in range(m-1, -1, -1):
            if not flag_exit:
                if A[i][j] == 0:
                    max_i, max_j = i, j
                    flag_exit = 1
            else:
                if A[i][j] == 0:
                    if D0[i][j] > D0[max_i][max_j]:
                        max_i, max_j = i, j
                    elif D0[i][j] == D0[max_i][max_j]:
                        tmp_arr = deepcopy(C0)
                        change_local_C0(i, j, tmp_arr, '-')
                        change_D0(tmp_arr)
                        sumD0_0 = sum([sum(i) for i in D0])

                        tmp_arr = deepcopy(C0)
                        change_local_C0(max_i, max_j, tmp_arr, '-')
                        change_D0(tmp_arr)
                        sumD0_1 = sum([sum(i) for i in D0])
                        if sumD0_0 < sumD0_1:
                            max_i, max_j = i, j
    return max_i, max_j


def max_index1():
    '''максимальный индекс в массиве D'''
    flag_exit = 0
    for i in range(n):
        for j in range(m):
            if not flag_exit:
                if A[i][j] == 1:
                    max_i, max_j = i, j
                    flag_exit = 1
            else:
                if A[i][j] == 1:
                    if D1[i][j] > D1[max_i][max_j]:
                        max_i, max_j = i, j
                    elif D1[i][j] == D1[max_i][max_j]:
                        tmp_arr = deepcopy(C1)
                        change_local_C1(i, j, tmp_arr, '-')
                        change_D1(tmp_arr)
                        sumD1_0 = sum([sum(i) for i in D1])

                        tmp_arr = deepcopy(C1)
                        change_local_C1(max_i, max_j, tmp_arr, '-')
                        change_D1(tmp_arr)
                        sumD1_1 = sum([sum(i) for i in D1])
                        if sumD1_0 < sumD1_1:
                            max_i, max_j = i, j
    return max_i, max_j


def check_arr(arr):
    '''проверка массива D'''
    if max([max(arr[i]) for i in range(len(arr))]):
        return True  # max массива не равен 0, значит перестановки не окончены
    return False


n, m = map(int, stdin.readline().strip().split())
A = [[int(j) for j in stdin.readline().strip()] for i in range(n)]
B0 = [[0] * m for i in range(n)]
C0 = [[0] * m for i in range(n)]
D0 = [[0] * m for i in range(n)]
B1 = [[0] * m for i in range(n)]
C1 = [[0] * m for i in range(n)]
D1 = [[0] * m for i in range(n)]

change_B(B0, 0)
change_B(B1, 1)
change_all_C(C0, C1)

change_D0(C0)
change_D1(C1)

# print_arr(A, C0, C1, D0, D1)
count = 0
while check_arr(D0) or check_arr(D1):
    i1, j1 = max_index1()
    change_local_C0(i1, j1, C0, '+')
    change_local_C1(i1, j1, C1, '-')
    i0, j0 = max_index0()
    # print(i0, j0, i1, j1)
    A[i0][j0], A[i1][j1] = A[i1][j1], A[i0][j0]
    change_local_C0(i0, j0, C0, '-')
    change_local_C1(i0, j0, C1, '+')
    change_D0(C0)
    change_D1(C1)
    count += 1
    # print_arr(A, C0, C1, D0, D1)

print(count)

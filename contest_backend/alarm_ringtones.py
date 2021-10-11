from sys import stdin

N, X, K = [int(i) for i in stdin.readline().split()]

A = sorted([int(i) for i in stdin.readline().split()])
B = {}
for i in A:
    B[i % X] = B.get(i % X, i)
C = sorted([i for i in B.values()])


def bynary_search(first, last):
    difference = (last - first) // 2

    if difference == 0:
        middle = last
    else:
        middle = first + difference
    res = 0
    for i in C:
        res += max(((middle - i) // X) + 1, 0)

    if last - first <= 1:
        if K == res:
            return middle
        return 0

    if K <= res:
        last = middle
    else:
        first = middle
    return bynary_search(first, last)


max_time = max(C) + X * K // len(C) + 1
print(bynary_search(0, max_time))

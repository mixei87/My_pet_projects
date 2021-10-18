from sys import stdin

a = [int(i) for i in stdin.readline().split()]


def mediana(arr):
    return sorted(arr)[1]


def change(arr):
    num = set()
    val = mediana(arr)
    for k in range(3):
        if arr[k] == val:
            num.add(k)
    for i, j in [(i, j)for i in range(3) for j in range(3) if i != j]:
        tmp_arr = arr[:]
        tmp_arr[i] -= tmp_arr[j]
        val = mediana(tmp_arr)
        for k in range(3):
            if tmp_arr[k] == val:
                num.add(k)
    return num


vals = change(a)
for i in range(3):
    if i in vals:
        print('YES')
    else:
        print('NO')

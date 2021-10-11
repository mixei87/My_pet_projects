from sys import stdin

n, m = map(int, stdin.readline().strip().split())

summ = n*m
unique_num = set()

row_last = [0 for i in range(m+1)]
col_last = [0 for i in range(n+1)]

count = 0
flag_vert, flag_horiz, flag_common = 0, 0, 0
while n != 1 or m != 1:
    if n >= m:
        # horizontal
        if not flag_vert:
            if count == 0:
                for i in range(1, m+1):
                    row_last[i] = (n-1)*m + 2*i
                    if row_last[i] > summ:
                        unique_num.add(row_last[i])
            else:
                for i in range(1, m+1):
                    row_last[i] *= 2
                    if row_last[i] > summ:
                        unique_num.add(row_last[i])
        elif not flag_common:
            one_num = col_last[1]+col_last[n]
            if one_num > summ:
                unique_num.add(one_num)
        else:
            one_num *= 2
            if one_num > summ:
                unique_num.add(one_num)
        if not flag_horiz:
            flag_horiz = 1
        n //= 2
    else:
        # vertical
        if not flag_horiz:
            if count == 0:
                for i in range(1, n+1):
                    col_last[i] = m * (2*i - 1) + 1
                    if col_last[i] > summ:
                        unique_num.add(col_last[i])
            else:
                for i in range(1, n+1):
                    col_last[i] *= 2
                    if col_last[i] > summ:
                        unique_num.add(col_last[i])
        elif not flag_common:
            one_num = row_last[1]+row_last[m]
            if one_num > summ:
                unique_num.add(one_num)
        else:
            one_num *= 2
            if one_num > summ:
                unique_num.add(one_num)
        if not flag_vert:
            flag_vert = 1
        m //= 2
    if count == 0:
        count = 1
    if flag_horiz and flag_vert and not flag_common:
        flag_common = 1

summ += len(unique_num)
print(summ)

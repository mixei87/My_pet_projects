import string as str
from sys import stdin
from collections import defaultdict

letters = {i for i in str.ascii_uppercase}
s = stdin.readline().strip()

dict_s = defaultdict(int)
for i in s:
    dict_s[i] += 1
dict_s_sort_keys = sorted(dict_s, key=dict_s.get, reverse=True)
dict_s_sort = {}
for i in dict_s_sort_keys:
    dict_s_sort[i] = dict_s[i]

unique_dict_values = defaultdict(int)
for val in dict_s_sort.values():
    unique_dict_values[val] += 1

counter = 0
r = []
substring = []
for key, val in dict_s_sort.items():
    num = unique_dict_values[val]
    if counter == 0:
        if num == 1:
            r.append(key)
        else:
            substring = []
            substring.append(key)
            counter = num - 1
    else:
        substring.append(key)
        counter -= 1
        if counter == 0:
            l = len(substring)
            mid = (l-1)//2
            k = 1
            if l % 2 == 1:
                k = -1
            r.append(substring[mid])
            for i in range(1, l):
                mid += k*i
                r.append(substring[mid])
                k *= -1

letters -= set(r)
T = ''
for i in r:
    T = T + i + T
    p = T.find(s)
    if p != -1:
        for j in letters:
            r.append(j)
        for j in r:
            print(j, end='')
        print('\n', p+1, sep='')
        break
else:
    print('No solution')

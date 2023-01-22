from re import L
from sys import stdin
import string

s = stdin.readline().replace('\n', '')
low_letters = string.ascii_lowercase
up_letters = string.ascii_uppercase
min_press = len(s)
s.replace(' ', '')
count_low, count_up = 0, 0
flag_first = 1
num_str = []
for i in s:
    if i in low_letters:
        count_low += 1
        if count_up != 0:
            num_str.append(count_up)
            count_up = 0
    elif i in up_letters:
        count_up += 1
        if not flag_first:
            if count_low != 0:
                num_str.append(count_low)
                count_low = 0
        else:
            flag_first = 0
            count_low = 0

if count_up != 0:
    num_str.append(count_up)
if count_low != 0 and flag_first == 0:
    num_str.append(count_low)

if len(num_str):
    path1 = 0
    path2 = 0
    path1_tmp = 0
    path2_tmp = 2
    counter = 0
    # print(num_str)
    for i in num_str:
        if counter % 2 == 0 and counter != 0:
            path1 += min(path1_tmp, 4)
            path1_tmp = 0
            path2 = min(path1+2, path2)
        elif counter % 2 == 1 and counter != 1:
            path2 += min(path2_tmp, 4)
            path2_tmp = 0
            path1 = min(path1, path2)
        path1_tmp += i * ((counter+1) % 2)
        path2_tmp += i * (counter % 2)
        counter += 1

    if counter % 2 == 1 or counter == 2:
        path1 += min(path1_tmp, 4)
    if counter % 2 == 0 or counter == 1:
        path2 += min(path2_tmp, 4)
    path = min(path1, path2)
    min_press += path

print(min_press)

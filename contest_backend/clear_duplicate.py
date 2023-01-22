'''Array sorted by not descending. Need remove all duplicates with minimum of memory'''
from sys import stdin
n = int(stdin.readline())
if n:
    old_num = int(stdin.readline())
    print(old_num)
    for i in range(n-1):
        new_num = int(stdin.readline())
        if new_num != old_num:
            old_num = new_num
            print(old_num)

from sys import stdin
from collections import defaultdict

n = int(stdin.readline())
delivery_id = list(map(int, stdin.readline().strip().split()))
parent_id = list(map(int, stdin.readline().strip().split()))
k = int(stdin.readline())
if k >= 1:
    a = list(map(int, stdin.readline().strip().split()))


def find_block_box(key_p, num=None):
    num = num or set()
    val_p = boxes.get(key_p)
    if val_p[0] == 0:
        return
    elif val_p[0] in num or val_p[0] == key_p:
        return key_p
    num.add(val_p[0])
    return find_block_box(val_p[0], num)


boxes = {}
count = 1
for i in range(n):
    settings = []
    num_palet = 0
    if parent_id[i] == 0:
        num_palet = count
        count += 1
    settings.append(parent_id[i])
    settings.append(delivery_id[i])
    settings.append(num_palet)
    boxes[i+1] = settings

box_block = set()
for i in range(n):
    tmp = find_block_box(i+1)
    if tmp:
        box_block.add(tmp)


def find_palet(key_p, num=None):
    num = num or set()
    val_p = boxes.get(key_p)
    if val_p[0] == 0:
        return val_p[2]
    elif val_p[0] in num:
        return
    num.add(key_p)
    return find_palet(val_p[0], num)


palet = defaultdict(set)
for key, val in boxes.items():
    if val[2] != 0:
        palet[val[2]].add(key)
    else:
        tmp = find_palet(key)
        if tmp:
            palet[tmp].add(key)

palet_complete = set()
for key, val in palet.items():
    palet_complete.add(key)
    for i in val:
        if delivery_id[i-1] in a:
            palet_complete.discard(key)
            break

print(len(palet_complete))
for i in palet_complete:
    print(i, end=' ')

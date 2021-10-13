from sys import stdin
# from copy import deepcopy

n = int(stdin.readline())
board_plane = [[x for x in stdin.readline().strip()] for i in range(n)]
m = int(stdin.readline())
group_passengers = [[x for x in stdin.readline().strip().split()]
                    for i in range(m)]

half_row_chairs = {'1_x':  [[1, 2, 3], 'left', ['aisle', 'window']], '1_y': [[1], 'right', ['aisle', 'window']],
                   '2_x': [[1], 'left', ['window']], '2_y': [[1, 2, 3], 'right', ['aisle', 'window']],
                   '3_x':  [[1], 'left', ['aisle', 'window']], '3_y': [[1], 'right', ['aisle']],
                   '4_x': [[1, 2, 3], 'left', ['aisle', 'window']], '4_y': [[1, 2, 3], 'right', ['aisle', 'window']]}

keys = set((i, j, k) for i in range(3, 0, -1) for j in (
    'left', 'right') for k in ('aisle', 'window'))

# keys = deepcopy(standart_keys)

# init of capacity_passsengers
capacity_passsengers = {}
for key_half_row, value in half_row_chairs.items():
    if len(keys):
        combination_capacity = [(i, value[1], k)
                                for i in value[0] for k in value[2]]
        for i in combination_capacity:
            if len(keys):
                if i in keys:
                    capacity_passsengers[i] = key_half_row
                    keys.remove(i)
            else:
                break
    else:
        break

for k, v in capacity_passsengers.items():
    print(f'{k}: {v}')

# for i in board_plane:
#     for j in i:
#         print(j, end='')
#     print()

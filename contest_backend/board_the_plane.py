from sys import stdin
# from copy import deepcopy

n = int(stdin.readline())
board_plane = [[x for x in stdin.readline().strip()] for i in range(n)]
m = int(stdin.readline())

group_passengers = [tuple(map(lambda x: int(x[1]) if x[0] == 0 else x[1], enumerate(
    stdin.readline().strip().split()))) for i in range(m)]


def print_board_plane():
    for i in board_plane:
        for j in i:
            print(j, end='')
        print()


half_row_chairs = {}
for i in range(len(board_plane)):
    for j in range(2):
        count_chairs = 0
        place_priority = []
        for k in range(3):
            m = j*4 + k
            if board_plane[i][m] == '.':
                count_chairs += 1
                if j == 0 and m == 0 or j == 1 and m == 6:
                    place_priority.append('window')
                elif j == 0 and m == 2 or j == 1 and m == 4:
                    place_priority.append('aisle')
        if count_chairs == 2 and board_plane[i][j*4 + 1] == '#':
            count_chairs = 1
        if j == 0:
            side_board = 'left'
        else:
            side_board = 'right'
        half_row_chairs[f'{i+1}_{j}'] = [
            [x for x in range(1, count_chairs+1)], side_board, place_priority]

# test_half_row_chairs = {'1_0':  [[1, 2, 3], 'left', ['aisle', 'window']], '1_1': [[1], 'right', ['aisle', 'window']],
#                         '2_0': [[1], 'left', ['window']], '2_1': [[1, 2, 3], 'right', ['aisle', 'window']],
#                         '3_0':  [[1], 'left', ['aisle', 'window']], '3_1': [[1], 'right', ['aisle']],
#                         '4_0': [[1, 2, 3], 'left', ['aisle', 'window']], '4_1': [[1, 2, 3], 'right', ['aisle', 'window']]}


# for k, v in half_row_chairs.items():
#     print(f'{k}: {v}')
# print('-' * 70)


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

print_board_plane

print(group_passengers)

for i in group_passengers:
    if i in capacity_passsengers:
        print(i)
    else:
        print('Cannot fulfill passengers requirements')

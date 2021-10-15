from sys import stdin

n = int(stdin.readline())
board_plane = [[x for x in stdin.readline().strip()] for i in range(n)]
m = int(stdin.readline())

group_passengers = [tuple(map(lambda x: int(x[1]) if x[0] == 0 else x[1], enumerate(
    stdin.readline().strip().split()))) for i in range(m)]


def print_board_plane():
    for i in range(len(board_plane)):
        for j in range(len(board_plane[i])):
            print(board_plane[i][j], end='')
            if board_plane[i][j] == 'X':
                board_plane[i][j] = '#'
        print()


def count_one_half_row(y, x):
    count_chairs = 0
    place_priority = []
    k = x*4
    for m in range(k, k+3):
        if board_plane[y][m] == '.':
            count_chairs += 1
            if x == 0 and m == 0 or x == 1 and m == 6:
                place_priority.append('window')
            elif x == 0 and m == 2 or x == 1 and m == 4:
                place_priority.append('aisle')
    if count_chairs == 2 and board_plane[y][x*4 + 1] == '#':
        count_chairs = 1
    if x == 0:
        side_board = 'left'
    else:
        side_board = 'right'
    key = f'{y+1}_{x}'
    if count_chairs > 0:
        half_row_chairs[key] = [
            [x for x in range(1, count_chairs+1)], side_board, place_priority]
    else:
        if key in half_row_chairs:
            del half_row_chairs[key]


half_row_chairs = {}
for i in range(len(board_plane)):
    for j in range(2):
        count_one_half_row(i, j)


def combine_capacity(val):
    return [(i, val[1], k) for i in val[0] for k in val[2]]


def fill_capacity_pass_for_1_row(k_half_row, val_half_row):
    for i in combine_capacity(val_half_row):
        if capacity_passengers.get(i) == None:
            capacity_passengers[i] = []
        capacity_passengers[i].append(k_half_row)


# init of capacity_passsengers
capacity_passengers = {}
for key_half_row, value_half_row in half_row_chairs.items():
    fill_capacity_pass_for_1_row(key_half_row, value_half_row)

letters_on_row = {0: 'A', 1: 'B', 2: 'C', 4: 'D', 5: 'E', 6: 'F'}
seats_on_row = {'left': {'window': 0, 'aisle': 2},
                'right': {'aisle': 4, 'window': 6}}


def fill_places_on_board(row, col, group_p):
    col_x = seats_on_row[group_p[1]][group_p[2]]
    reserve_cols = []
    if group_p[0] == 1:
        board_plane[row][col_x] = 'X'
        reserve_cols.append(col_x)
    elif group_p[0] == 2:
        col += 1
        if col > col_x:
            col, col_x = col_x, col
        for j in range(col, col_x + 1):
            board_plane[row][j] = 'X'
            reserve_cols.append(j)
    elif group_p[0] == 3:
        for j in range(3):
            board_plane[row][col+j] = 'X'
            reserve_cols.append(col+j)
    return reserve_cols


for group in group_passengers:
    if group in capacity_passengers:
        finded_row = capacity_passengers[group][0]
        # удаляем из capacity_passsengers старые значения
        combination_capacity = combine_capacity(half_row_chairs[finded_row])
        # функция поиска и заполнения свободных мест в указанной области самолета: capacity_passengers[group]
        y, x = map(int, finded_row.split('_'))
        y -= 1
        m = x*4
        reserve_columns = fill_places_on_board(y, m, group)
        places = [str(y+1) + letters_on_row[j] for j in reserve_columns]
        print(f'Passengers can take seats:', *places)
        print_board_plane()
        # новая разметка вместимости этой области самолёта
        count_one_half_row(y, x)
        # надо внести в capacity_passsengers все недостающие ключи
        if finded_row in half_row_chairs:
            new_combination_capacity = combine_capacity(
                half_row_chairs[finded_row])
        else:
            new_combination_capacity = []
        for i in combination_capacity:
            if i not in new_combination_capacity:
                if len(capacity_passengers[i]) > 1:
                    capacity_passengers[i].remove(finded_row)
                else:
                    del capacity_passengers[i]
    else:
        print('Cannot fulfill passengers requirements')

from sys import stdin

n = int(stdin.readline())
board_plane = []
for i in range(n):
    tmp_list = []
    for j in stdin.readline().strip():
        tmp_list.append(j)
    board_plane.append(tmp_list)

print(n)
board_plane[1][6] = 'X'
for i in board_plane:
    for j in i:
        print(j, end='')
    print()

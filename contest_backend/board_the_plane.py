from sys import stdin

n = int(stdin.readline())
board_plane = [[x for x in stdin.readline().strip()] for i in range(n)]
m = int(stdin.readline())
group_passengers = [[x for x in stdin.readline().strip().split()]
                    for i in range(m)]

# board_plane[1][6] = 'X'

for i in board_plane:
    for j in i:
        print(j, end='')
    print()

from sys import stdin
n = int(stdin.readline())

listPhoto = {}
t_c = [[int(e) for e in stdin.readline().split()] for _ in range(n)]
listPhoto = {str(i)+str(j): k for k in range(n) for i in range(
    t_c[k][0], t_c[k][2]) for j in range(t_c[k][1], t_c[k][3])}

for i in range(n):
    print([k for k in listPhoto.values()].count(i))

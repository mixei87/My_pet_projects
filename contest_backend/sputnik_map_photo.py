from sys import stdin
n = int(stdin.readline())

t_c = [[int(e) for e in stdin.readline().split()] for _ in range(n)]
del stdin
photo = {str(i)+str(j): k for k in range(n) for i in range(
    t_c[k][0], t_c[k][2]) for j in range(t_c[k][1], t_c[k][3])}
del t_c
for i in range(n):
    print(len([photo.pop(key)
          for key, val in list(photo.items()) if val == i]))

from sys import stdin
a = {}
for i in stdin.readline().strip():
    a[i] = a.get(i, 0) + 1
b = {}
for i in stdin.readline().strip():
    if i in a:
        b[i] = b.get(i, 0) + 1
    else:
        print(0)
        break
else:
    if a == b:
        print(1)
    else:
        print(0)

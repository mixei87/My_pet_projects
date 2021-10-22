from sys import stdin
a = [i for i in stdin.readline().strip()]
b = None
for b in stdin.readline().strip():
    if b in a:
        a.remove(b)
    else:
        print(0)
        break
else:
    if len(a) == 0 and not isinstance(b, int):
        print(1)
    else:
        print(0)

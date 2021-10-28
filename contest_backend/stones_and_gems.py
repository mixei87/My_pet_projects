from sys import stdin
j, s = [stdin.readline().strip() for i in range(2)]
gems = set(j)
counter = 0
for k in s:
    if k in gems:
        counter += 1
print(counter)

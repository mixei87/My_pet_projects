from sys import stdin

n = int(stdin.readline())
count = max_count = 0
for i in range(n):
    if int(stdin.readline()):
        count += 1
        max_count = max(count, max_count)
    else:
        count = 0
print(max_count)

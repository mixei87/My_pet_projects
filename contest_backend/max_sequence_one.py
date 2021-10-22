from sys import stdin

n = int(stdin.readline())
max_count = {0}
count = 0
for i in range(n):
    if int(stdin.readline()):
        count += 1
    elif count:
        max_count.add(count)
        count = 0
print(max(count, max(max_count)))

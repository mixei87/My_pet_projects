from sys import stdin

k = int(stdin.readline().strip())
a = list(map(int, stdin.readline().strip().split()))
b = list(map(int, stdin.readline().strip().split()))

a_remind = []
for i in range(len(a)):
    a_remind.append(a[i])

sum_all = 0
for i in a:
    sum_all += i
sum_min = 0
for i in b:
    sum_min += i

for i in range(len(b)):
    if b[i] == 0:
        b[i] = 1

if sum_min == 0:
    sum_min = 1
box_max = sum_all//sum_min
sum_min = sum_all//box_max


def max_list(a_remind):
    count_max = 0
    max = a_remind[count_max]
    for i in range(1, len(a_remind)):
        if a_remind[i] > max:
            count_max = i
    return count_max


print(box_max, sum_min)

for i in range(box_max):
    num_shar = sum_min
    list_shar = []
    for j in range(len(a)):
        for k in range(a[j]//box_max):
            list_shar.append(j+1)
            a_remind[j] -= 1
            num_shar -= 1
    while num_shar != 0:
        shar = max_list(a_remind)
        list_shar.append(shar+1)
        a_remind[shar] -= 1
        num_shar -= 1
    list_shar.sort()
    for j in list_shar:
        print(str(j) + ' ', end='')
    print()

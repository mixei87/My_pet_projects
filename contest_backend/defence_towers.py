from sys import stdin

n, m = [int(i) for i in stdin.readline().split()]
a = tuple(reversed([int(i) for i in stdin.readline().split()]))
b = tuple(sorted([int(i) for i in stdin.readline().split()], reverse=True))

min_b = b[-1]
max_shadow = 0
sun_places = []
for i in a:
    len_sun = i-max_shadow
    if len_sun >= min_b:
        sun_places.append(len_sun)
    if i > max_shadow:
        max_shadow = i

count = 0
sun_places = sorted(sun_places, reverse=True)
num_sun = 0
end = len(sun_places)
for i in b:
    if num_sun < end:
        if i <= sun_places[num_sun]:
            count += 1
            num_sun += 1
    else:
        break
print(count)

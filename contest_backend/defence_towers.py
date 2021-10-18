from sys import stdin

n, m = [int(i) for i in stdin.readline().split()]
a = [int(i) for i in stdin.readline().split()]
b = [int(i) for i in stdin.readline().split()]

min_b = min(b)
max_shadow = 0
sun_places = []
for i in reversed(a):
    len_sun = i-max_shadow
    if len_sun >= min_b:
        sun_places.append(len_sun)
    if i > max_shadow:
        max_shadow = i

count = 0
for i in sorted(b, reverse=True):
    if len(sun_places):
        max_sun_places = max(sun_places)
        if i <= max_sun_places:
            count += 1
            sun_places.remove(max_sun_places)
    else:
        break
print(count)

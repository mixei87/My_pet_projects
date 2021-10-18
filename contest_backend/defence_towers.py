from sys import stdin

n, m = [int(i) for i in stdin.readline().split()]
a = tuple(reversed([int(i) for i in stdin.readline().split()]))
b = tuple(sorted([int(i) for i in stdin.readline().split()], reverse=True))

min_b = b[-1]
max_shadow = 0
sun_places = {}
for i in a:
    len_shadow = i-max_shadow
    if len_shadow >= min_b:
        sun_places[len_shadow] = sun_places.get(len_shadow, 0) + 1
    if i > max_shadow:
        max_shadow = i

count = 0
for i in b:
    if len(sun_places):
        max_sun_places = max(sun_places)
        if i <= max_sun_places:
            count += 1
            if sun_places[max_sun_places] > 1:
                sun_places[max_sun_places] -= 1
            else:
                del sun_places[max_sun_places]
    else:
        break
print(count)

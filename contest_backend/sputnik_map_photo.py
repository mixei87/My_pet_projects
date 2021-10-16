reader = open('input.txt', 'r')
n = int(reader.readline().strip())
p = {}

for k in range(n):
    x1, y1, x2, y2 = [int(n) for n in reader.readline().split(" ")]
    for i in range(x1, x2):
        for j in range(y1, y2):
            p[str(i) + str(j)] = k
reader.close()

tmp = [k for k in p.values()]
writer = open('output.txt', 'w')
for i in range(n):
    writer.write(f'{tmp.count(i)}\n')
writer.close()

from sys import stdin

cluster_count = 0
serv_clust = {}
for i in range(int(stdin.readline())):
    A, B = map(int, stdin.readline().split())
    tmp = min(serv_clust.get(A, cluster_count),
              serv_clust.get(B, cluster_count))
    serv_clust[A], serv_clust[B] = tmp, tmp
    if tmp == cluster_count:
        cluster_count += 1
Q = int(stdin.readline())
for i in range(Q):
    X, K_count = map(int, stdin.readline().split())
    K = [int(m) for m in stdin.readline().split()]
    res_sum = 0
    res_list = []
    for j in range(K_count):
        if serv_clust[K[j]] == serv_clust[X]:
            res_sum += 1
            res_list.append(K[j])
    print(res_sum, end='')
    for j in range(res_sum):
        print(' ' + str(res_list[j]), sep='', end='')
    if i != Q - 1:
        print()

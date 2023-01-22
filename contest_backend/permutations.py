def find(number, A):
    for x in A:
        if number == x:
            return True
    return False


def generate_permutations(n, m=-1, prefix=None):
    m = n if m == -1 else m
    prefix = prefix or []
    if m == 0:
        for i in prefix:
            print(a[i], end=' ')
        print()
        return
    for number in range(n):
        if find(number, prefix):
            continue
        prefix.append(number)
        generate_permutations(n, m-1,  prefix)
        prefix.pop()


a = [5, 2, 1, 8]

generate_permutations(len(a))

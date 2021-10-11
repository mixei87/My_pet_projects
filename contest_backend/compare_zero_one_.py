from sys import stdin

s1 = stdin.readline().strip()
s2 = stdin.readline().strip()


def binary(ss):
    s = ss[::-1]
    num = 0
    count = 0
    i = 0
    while i < len(s):
        if s[i] == 'e':
            num += 2 ** count
            i += 3
        else:
            i += 4
        count += 1
    return num


num1 = binary(s1)
num2 = binary(s2)
if num1 > num2:
    print('>')
elif num1 < num2:
    print('<')
else:
    print('=')

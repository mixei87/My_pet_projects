from sys import stdin

max_left_brackets = int(stdin.readline())
count_brackets = 2 * max_left_brackets


def brackets(seq_brackets=[], sym=None, left=0, right=0):
    if sym:
        seq_brackets.append(sym)
    if left+right == count_brackets:
        for i in seq_brackets:
            print(i, end='')
        print()
        return
    for i in range(max_left_brackets):

        if left != max_left_brackets:
            left += 1
            brackets(seq_brackets, '(', left, right)
        elif right != max_left_brackets:
            right += 1
            brackets(seq_brackets, ')', left, right)

        max_left_brackets -= 1


brackets()

from sys import stdin, argv


def CheckInput(argv):
  if len(argv) != 1:
    print("Srcipt don't need any args")
    exit(1)


# flag = True
# i = 0
# for string in stdin:
#   string = string.rstrip()
#   if flag == 'Error':
#     break
#   for j in range(len(string)):
#     if j > 4:
#       flag = 'Error'
#       break
#     if (j == 0 or j == i or j == 4-i or j == 4):
#       if string[j] != '*':
#         flag = False
#     else:
#       if string[j] == '*':
#         flag = False3
#   i += 1

# if i != 3:
#   flag = 'Error'
# print(flag, end='')


def MyExit():
  print("Error")
  exit(1)


def CheckStrings():
  n = 0
  for string in stdin:
    n += 1
    if n > 3:
      MyExit()
    string = string.rstrip()
    if len(string) != 5:
      MyExit()
  else:
    if n == 0:
      MyExit()


if __name__ == '__main__':
  CheckInput(argv)
  CheckStrings()

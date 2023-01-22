from sys import stdin, argv


def CheckInput(argv):
  if len(argv) != 1:
    print("Srcipt don't need any args")
    exit(1)


def MyExit():
  print("Error")
  exit(1)


def CheckStrings() -> list:
  n = 0
  strings = [lines.rstrip() for lines in stdin.readlines()]
  if len(strings) != 3:
    MyExit()
  return strings


def CheckToAsterisks(strings):
  i = 0
  for string in strings:
    for j in range(len(string)):
      if j == 5:
        MyExit()
      elif (j == 0 or j == i or j == 4-i or j == 4):
        if string[j] != '*':
          MyExit()
      elif string[j] == '*':
        MyExit()
    i += 1


if __name__ == '__main__':
  CheckInput(argv)
  strings = CheckStrings()
  CheckToAsterisks(strings)

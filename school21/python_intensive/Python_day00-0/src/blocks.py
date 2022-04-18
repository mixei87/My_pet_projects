from sys import argv, stdin

if len(argv) != 2:
  print("Number of arguments isn't 1")
  exit(1)

n = int(argv[1])
for string in stdin:
  if (n <= 0):
    exit(0)
  string = string.rstrip()
  if len(string) == 32:
    flag = True
    for j in range(5):
      if string[j] != '0':
        flag = False
    if string[j+1] == '0':
      flag = False
    if flag == True:
      print(string)
  n -= 1

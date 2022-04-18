from sys import stdin

flag = True
i = 0
for string in stdin:
  string = string.rstrip()
  if flag == 'Error':
    break
  for j in range(len(string)):
    if j > 4:
      flag = 'Error'
      break
    if (j == 0 or j == i or j == 4-i or j == 4):
      if string[j] != '*':
        flag = False
    else:
      if string[j] == '*':
        flag = False
  i += 1

if i != 3:
  flag = 'Error'
print(flag, end='')

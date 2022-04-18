from sys import argv

if len(argv) > 1:
  string = argv[1]
  len_str = len(string)
  flag = True
  for i in range(len_str):
    if string[i] == ' ':
      if flag == False:
        flag = True
    elif flag == True:
      print(string[i], end='')
      flag = False

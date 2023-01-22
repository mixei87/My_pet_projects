from sys import stdin
from argparse import ArgumentParser


def CheckHash(hash_str: str) -> bool:
  if len(hash_str) == 32 and hash_str[:5] == "00000" and hash_str[5] != "0":
    return True
  return False


def CheckInput():
  parser = ArgumentParser(
    description='Input number of validate hashs')
  parser.add_argument('number_strings', metavar='n',
                      type=int, help='Number of strings')
  return parser.parse_args()


def PrintStrings(n):
  for string in stdin:
    if (n <= 0):
      break
    string = string.rstrip()
    if CheckHash(string):
      print(string)
    n -= 1


if __name__ == '__main__':
  args = CheckInput()
  PrintStrings(args.number_strings)

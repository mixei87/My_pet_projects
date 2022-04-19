from sys import argv, stdin
from argparse import ArgumentParser


def CheckHash(hash_str: str) -> bool:
  if len(hash_str) == 32 and hash_str[:5] == "00000" and hash_str != "0":
    return True
  return False


def CheckInput(params: list):
  if len(params) != 2:
    print("Number of arguments isn't 1")
    exit(1)


def PrintStrings():
  # check argument
  n = int(argv[1])
  for string in stdin:
    if (n <= 0):
      break
    string = string.rstrip()
    if CheckHash(string):
      print(string)
    n -= 1


if __name__ == '__main__':
  CheckInput(argv)
  PrintStrings()

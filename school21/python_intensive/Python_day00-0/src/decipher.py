from sys import argv
from argparse import ArgumentParser


def CheckInput():
  parser = ArgumentParser(description='Input message for decrypting')
  parser.add_argument('msg', nargs='*', type=str,
                      help='Message for decrypting')
  return parser.parse_args()


def CreateString(msg: list) -> list:
  return [word for big_str in args.msg for word in big_str.split()]


def PrintDecryptMsg(string: list):
  for word in string:
    if word[0].isalpha():
      print(word[0], end='')


if __name__ == "__main__":
  args = CheckInput()
  string = CreateString(args.msg)
  PrintDecryptMsg(string)

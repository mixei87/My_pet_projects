def main():
    numbers = [x for x in range(3, 31) if x % 3 == 0]
    for number in numbers:
        print(number)


if __name__ == "__main__":
    main()

def main():
    nums = list(range(1, 10))
    for num in nums:
        print(num, end="")
        if num == 1:
            print('st')
        elif num == 2:
            print('nd')
        elif num == 3:
            print('rd')
        else:
            print('th')


if __name__ == "__main__":
    main()

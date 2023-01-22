def main():
    users = []
    if users:
        for user in users:
            if user == 'admin':
                print(f'Hello, {user}, would you like to see a status report?')
            else:
                print(f'Hello, {user.title()}, thank you for logging in again')
    else:
        print("We need to find some users!")


if __name__ == "__main__":
    main()

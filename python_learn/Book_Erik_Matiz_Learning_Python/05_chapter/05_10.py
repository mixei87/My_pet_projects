def main():
    current_users = ['tom', 'marY', 'ada', 'Sasha', 'piter']
    current_users_lower = [user.lower() for user in current_users]
    new_users = ['piter', 'mAry', 'vika', 'natasha', 'john']
    for new_user in new_users:
        if new_user.lower() in current_users_lower:
            print("Nickname isn't available. Please change name")
        else:
            print('Nickname is available')


if __name__ == "__main__":
    main()

from copy import copy, deepcopy


def main():
    users = ['tom', ['mary', ['ada', 'lisa']], 'admin', 'piter']
    new_users_simple_copy_1 = users[:]
    new_users_simple_copy_2 = copy(users)
    new_users_good_copy = deepcopy(users)
    print(users)
    print(new_users_simple_copy_1)
    print(new_users_simple_copy_2)
    print(new_users_good_copy)
    users[0] = 'mike'
    users[1][0] = 'roman'
    users[1][1][0] = 'vika'
    print(users)
    print(new_users_simple_copy_1)
    print(new_users_simple_copy_2)
    print(new_users_good_copy)


if __name__ == "__main__":
    main()

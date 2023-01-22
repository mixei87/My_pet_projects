def print_hello_fullname(fullname):
    print(f"\tHello,\n {fullname}!")


name = "bOris"
surname = "JOhNsoN"
fullname = f"    {name}      {surname}    "
print_hello_fullname(fullname)
print_hello_fullname(fullname.lower())
print_hello_fullname(fullname.upper())
print("-"*50)

print_hello_fullname(fullname.title())
print_hello_fullname(fullname.title().lstrip())
print_hello_fullname(fullname.title().rstrip())
print_hello_fullname(fullname.title().strip())

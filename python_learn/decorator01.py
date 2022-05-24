import functools


def do_twice(func):
  @functools.wraps(func)
  def wrapper_do_twice(*args, **kwargs):
    func(*args, **kwargs)
    return func(*args, **kwargs)
  return wrapper_do_twice


@do_twice
def return_greeting(name):
  print("Готовлюсь приветствовать...")
  return f"Привет, {name}!"


print(return_greeting)
print(return_greeting("Лиза"))

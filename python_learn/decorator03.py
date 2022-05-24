import functools


def debug(func):
  @functools.wraps(func)
  def wrapper_debug(*args, **kwargs):
    args_repr = [repr(a) for a in args]                      # 1
    kwargs_repr = [f"{k}={repr(v)}" for k, v in kwargs.items()]  # 2
    signature = ", ".join(args_repr + kwargs_repr)           # 3
    print(f"Вызываем {func.__name__}({signature})")
    value = func(*args, **kwargs)
    print(f"{repr(func.__name__)} возвращает {repr(value)}")         # 4
    return value
  return wrapper_debug


@debug
def make_greeting(name, age=None):
  if age is None:
    return f"Привет, {name}!"
  else:
    return f"Ого, {name}! Тебе уже {age}, как ты быстро растёшь!"


make_greeting("Ваня", "Misha")
make_greeting("Lisa", age=7)

import functools
import time


def timer(func):
  """Выводит время выполнения декорируемой функции"""
  @functools.wraps(func)
  def wrapper_timer(*args, **kwargs):
    start_time = time.perf_counter()
    value = func(*args, **kwargs)
    end_time = time.perf_counter()
    run_time = end_time - start_time
    print(f"Функция {func.__name__} выполнена за {run_time:.4f} с")
    return value
  return wrapper_timer


@timer
def my_sum(n: int):
  sum = 0
  for i in range(1, n+1):
    sum += i
  print(sum)


my_sum(1)
my_sum(10000)

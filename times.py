import random
import time

import naive
import _sorts

"""This file supplies functions useful in simple benchmarking
    for our various sorting implementations and can be executed
    to run a set of benchmarks.
"""
def setup(length):
    """ Generates a list of non-negative floats less than 100 of length *length*"""
    return [float(random.randrange(100)) for x in range(length)]

def single_run(sort_func, in_order, list_length=10000):
    """ Times sorting of list and assignment to variable."""
    lst = setup(list_length)
    if in_order:
        lst = sorted(lst)
    t0 = time.time()
    lst = sort_func(lst)
    t1 = time.time()
    return t1 - t0

def many_runs(sort_func, iterations=10, in_order=False):
    return [sort_func.__name__] + [(single_run(sort_func, in_order)) for i in range(iterations)]

if __name__ == "__main__":
    sort_functions = [sorted, naive.merge_sort_python, 
            _sorts.mt_merge_c, _sorts.naive_merge_c, _sorts.bubble_c]
    for sort_function in sort_functions:
        results = many_runs(sort_function)
        print(*results, sep='\n')
        print()

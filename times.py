import random
import time

import naive
import _sorts

"""This file supplies functions useful in simple benchmarking
    for our various sorting implementations and can be executed
    to run a simple set of benchmarks.
"""

def setup(length):
    """ Generates a list of non-negative floats less than 100 of length 'length'"""
    return [float(random.randrange(100)) for x in range(length)]

def single_run(sort_func, in_order, list_length=100):
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
    sorted_runs = many_runs(sorted)
    print(*sorted_runs, sep='\n')
    
    _sorts_nm_runs = many_runs(_sorts.naive_merge)
    print(*_sorts_nm_runs, sep='\n')
    
    _sorts_bubble_runs = many_runs(_sorts.bubble)
    print(*_sorts_bubble_runs, sep='\n')
    
    naive_py_runs = many_runs(naive.naive)
    print(*naive_py_runs, sep='\n')

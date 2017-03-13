""" This file defines two functions that, together, define a naively
written merge sort.
"""
def naive(list_in):
    """ Makes recursive calls to split list into 
        sub problems, unless list has few elements.
        Also calls merge to combine solns to said problems.
    """
    if len(list_in) < 2:
        return list_in
    mid = len(list_in) // 2
    return merge(naive(list_in[:mid]), naive(list_in[mid:]))

def merge(left, right):
    """ Combines two sorted lists into one."""
    combined = []
    ii = jj = 0
    imax = len(left)
    jmax = len(right)
    while ii < imax and jj < jmax:
        if left[ii] <= right[jj]:
            combined.append(left[ii])
            ii += 1
        else:
            combined.append(right[jj])
            jj += 1
    combined = combined + left[ii:] + right[jj:]
    return combined

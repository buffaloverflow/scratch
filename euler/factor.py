from functools import reduce
from math import sqrt
def factors(n):
    step = 2 if n%2 else 1
    return set(reduce(list.__add__,
                ([i, n//i] for i in range(1, int(sqrt(n))+1, step) if n % i == 0))) - {n}

def perfect(n):
    return sum(factors(n)) == n

def abundant(n):
    return sum(factors(n)) > n

def deficient(n):
    return sum(factors(n)) < n

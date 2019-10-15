import sys
import itertools
from array import array
import math
import numbers
import collections
import random

def Ca(s,n):
    base = ord('a')
    return "".join((chr(ord(c)- base +n%26 + base) for c in s))

s =Ca("abdh",1)
print(s)








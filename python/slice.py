#https://github.com/fluentpython/example-code/blob/master/14-it-generator/sentence_iter.py

import collections
import itertools

Card = collections.namedtuple('Card',['rank','suit'])

class FrenchDeck:
    ranks = [str(n) for n in range(2,11)] + list('JQA')
    suits = 'spades diamonds clubs hearts'.split()

    def __init_(self):
        #self._cards = [Card(rank,suit) for suit in self.suits
        #                               for rank in self.ranks]
        self._cards = [Card(rank,suit) for (rank,suit) in
                       itertools.product(self.ranks, self.suits)]

    def __len__(self):
        return len(self._cards)

    def __getitem__(self,position):
        return self._cards[position]

class MySeq:
    def __getitem__(self,index):
        return index

# __getitem__() args will be either index when [inetergral]
# or splice object with isinide [:] has slicing semetic
# comma means tuple of slicing object or index mix
s= MySeq()
s[1] # 1 call __getitem__ and return the value
s[1:4] # slice(1, 4, None) # return a slice object with slice args
s[1:4:2] # slice(1, 4, 2)
s[1:4:2,9]# (slice(1, 4, 2), 9) #comma means getitem receis a tuple
s[1:4:2,7:9]# (slice(1, 4, 2), slice(7, 9, None))

# slice object
# incdices method would normalised the tuples of nongeative indexes so taht
# it would support the python like slicing args with missing indexes or negative index
# such that it would ajust the indices to fit within the bounds ao f a given length
# has start , step, stop, and indices method
# seq protocol need __len__ since , it need as len as arg for for indices method to
# normalise the slice object to legal non negative start , stop, step args
slice(None,10,2).indices(5) # (0, 5, 2)
slice(-3,None,None).indices(5) #(2, 5, 1)


# ---------------------------------------------------------------------------
"""
# BEGIN VECTOR_V2_DEMO
    >>> v7 = Vector(range(7))
    >>> v7[-1]  # <1>
    6.0
    >>> v7[1:4]  # <2>
    Vector([1.0, 2.0, 3.0])
    >>> v7[-1:]  # <3>
    Vector([6.0])
    >>> v7[1,2]  # <4>
    Traceback (most recent call last):
      ...
    TypeError: Vector indices must be integers
# END VECTOR_V2_DEMO
"""
from array import array
import reprlib
import math
import numbers
import functools
import operator
import itertools  # <1>


class Vector:
    typecode = 'd'

    def __init__(self, components):
        self._components = array(self.typecode, components)

    def __iter__(self):
        return iter(self._components)

    def __repr__(self):
        components = reprlib.repr(self._components)
        components = components[components.find('['):-1]
        return 'Vector({})'.format(components)

    def __str__(self):
        return str(tuple(self))

    def __bytes__(self):
        return (bytes([ord(self.typecode)]) +
                bytes(self._components))

    def __eq__(self, other):
        return (len(self) == len(other) and
                all(a == b for a, b in zip(self, other)))

    def __hash__(self):
        hashes = (hash(x) for x in self)
        return functools.reduce(operator.xor, hashes, 0)

    def __abs__(self):
        return math.sqrt(sum(x * x for x in self))

    def __bool__(self):
        return bool(abs(self))

    def __len__(self):
        return len(self._components)

    def __getitem__(self, index):
        cls = type(self)
        if isinstance(index, slice):
            return cls(self._components[index])
        elif isinstance(index, numbers.Integral):
            return self._components[index]
        else:
            msg = '{.__name__} indices must be integers'
            raise TypeError(msg.format(cls))

    shortcut_names = 'xyzt'

    def __getattr__(self, name):
        cls = type(self)
        if len(name) == 1:
            pos = cls.shortcut_names.find(name)
            if 0 <= pos < len(self._components):
                return self._components[pos]
        msg = '{.__name__!r} object has no attribute {!r}'
        raise AttributeError(msg.format(cls, name))

# BEGIN VECTOR_V3_SETATTR
    # since we do not want to set attributes for x, y ,z 
    # when we do obj.x = 99 , __setattr__ will get called
    # so that we can control the set atrributes process
    def __setattr__(self, name, value):
        cls = type(self)
        if len(name) == 1:  # <1>
            if name in cls.shortcut_names:  # <2>
                error = 'readonly attribute {attr_name!r}'
            elif name.islower():  # <3>
                error = "can't set attributes 'a' to 'z' in {cls_name!r}"
            else:
                error = ''  # <4>
            if error:  # <5>
                msg = error.format(cls_name=cls.__name__, attr_name=name)
                raise AttributeError(msg)
        # super() provides a way to access the methods of the super class directly
        super().__setattr__(name, value)  # <6>

# END VECTOR_V3_SETATTR


    def angle(self, n):  # <2>
        r = math.sqrt(sum(x * x for x in self[n:]))
        a = math.atan2(r, self[n-1])
        if (n == len(self) - 1) and (self[-1] < 0):
            return math.pi * 2 - a
        else:
            return a

    def angles(self):  # <3>
        return (self.angle(n) for n in range(1, len(self)))

    def __format__(self, fmt_spec=''):
        if fmt_spec.endswith('h'):  # hyperspherical coordinates
            fmt_spec = fmt_spec[:-1]
            coords = itertools.chain([abs(self)],
                                     self.angles())  # <4>
            outer_fmt = '<{}>'  # <5>
        else:
            coords = self
            outer_fmt = '({})'  # <6>
        components = (format(c, fmt_spec) for c in coords)  # <7>
        return outer_fmt.format(', '.join(components))  # <8>

    @classmethod
    def frombytes(cls, octets):
        typecode = chr(octets[0])
        memv = memoryview(octets[1:]).cast(typecode)
        return cls(memv)
# END VECTOR_V5

# ---------------------------------------------------------------------------
# Dynamic Attributes Access
# the __getattr__ method is invoked when the attribute lookup fails
# e.g. obj.x  will first check the object attributes if it has x, if
# not it will check it the class of the object obj_.__class__ and then up 
# the iheritance graph, if the x is not found , then the __getattr__ methond
# defined in the class of the objc will get called with __getattr__(self,'x')




# ---------------------------------------------------------------------------
# reduce
# functools.reduce(func,iter,init)
# initilizer is provided so that when the iterable is empty will just return
# the initializer insted of the TypeError
import functools
functools.reduce(lambda a,b: a*b,range(1,6)) #5!
functools.reduce(lambda a,b: a^b,range(6))

import operator
functools.reduce(operator.xor,range(6))

# zip 
# zip is greate for looping multiple iterable in parallel without using index
# zip would stop when one of the iterable is exhuasted 
import itertools
list(itertools.zip_longest(range(3),'ABC',[1,2,3,4],fillvalue=99))
# [(0, 'A', 1), (1, 'B', 2), (2, 'C', 3), (99, 99, 4)]





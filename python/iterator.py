

# ----------------------------------------------------------------
https://github.com/fluentpython/example-code/blob/master/14-it-generator/sentence_iter.py
# every collection in python is iterable , and iterators are used internelly to support


# how iterator works
"""
When the interpreter needs to iterate over an object x , it will call iter(x)
- iter will check object x has implemented __iter__, and call to iterate the object
- if __iter__ is not found, but __getitem__ is implemented , python will create an
iterator using __getitem__ that get items in order from index 0
- if that fias, python raise TypeError, usually saying this object is not iterable
"""

# if do iteration by hand
s = "ABC"
it = iter(s) # get a iterator from the object
while True:
    try:
        print(next(it)) # repeatedly call next item on the iterator
    except StopIteration: # when there is no item to iterate raise an exception
        del it # release the reference to iterator object
        break
"""
standard interface for an iterator has two method:
__next__:
    returns the next avaliable item, Raise TypeError when exhuasted
__iter__:
    returns the iterator itself
"""

# -----------------------------------------------------------------------
# a classic iterator example
"""
Sentence: iterate over words using the Iterator Pattern, take #1

WARNING: the Iterator Pattern is much simpler in idiomatic Python;
see: sentence_gen*.py.
"""

# BEGIN SENTENCE_ITER
import re
import reprlib

RE_WORD = re.compile(r'\w+')

class Sentence:

    def __init__(self, text):
        self.text = text
        self.words = RE_WORD.findall(text)

    def __repr__(self):
        return 'Sentence(%s)' % reprlib.repr(self.text)

    def __iter__(self):  # <1>
        return SentenceIterator(self.words)  # <2>


class SentenceIterator:

    def __init__(self, words):
        self.words = words  # <3>
        self.index = 0  # <4>

    def __next__(self):
        try:
            word = self.words[self.index]  # <5>
        except IndexError:
            raise StopIteration()  # <6>
        self.index += 1  # <7>
        return word  # <8>

    def __iter__(self):  # <9>
        return self
# END SENTENCE_ITER
# -----------------------------------
def main():
    import sys
    import warnings
    try:
        filename = sys.argv[1]
        word_number = int(sys.argv[2])
    except (IndexError, ValueError):
        print('Usage: %s <file-name> <word-number>' % sys.argv[0])
        sys.exit(1)
    with open(filename, 'rt', encoding='utf-8') as text_file:
        s = Sentence(text_file.read())
    for n, word in enumerate(s, 1):
        if n == word_number:
            print(word)
            break
    else:
        warnings.warn('last word is #%d, "%s"' % (n, word))

if __name__ == '__main__':
    main()

# -----------------------------------------------------------------------
# more pythonic implememnt using generator function
class Sentence:

    def __init__(self, text):
        self.text = text

    def __repr__(self):
        return 'Sentence(%s)' % reprlib.repr(self.text)

    # here is a generator function and will return a generator object
    def __iter__(self):  # <1>
        # generator function does not raise exception
        # will just exit when done producing values
        # finditer will build an iterator over the match object ,yield
        # MatchObject instance
        """
        for match in RE_WORD.finditer(self.text):
            yield match.group(); # show the actual match from the MatchObject
        """
        # instead of using a generator function could use a
        # generator expression instead
        return (match.group() for match in RE_WORD.finditer(self.text))

# -----------------------------------------------------------------------
# how generator function works
"""
(probabily by keep state of the function excution and buffer only the
intermediate result that yield, s.t. it can save space to buffer all the
intermediate result, as to generate result as it goes, not at once)
when call next() on the generator object, excution advanced to the next
yield in the function body, and the next() call evaluaties to the value
yield when the function body is suspended.
when the function body returns, the enclosing generator object raises StopIteration exception
"""
def gen_123():
    yield 1
    yield 2
    yield 3

g = gen_123() # returns a generator object 
next(g) # 1 can generate the next object 
next(g) # 2 
next(g) # 3 
next(g) # SotpIteration 

# -----------------------------------------------------------------------
# another example of generator expression
# BEGIN ARITPROG_CLASS
class ArithmeticProgression:

    def __init__(self, begin, step, end=None):  # <1>
        self.begin = begin
        self.step = step
        self.end = end  # None -> "infinite" series

    def __iter__(self):
        result = type(self.begin + self.step)(self.begin)  # <2>
        forever = self.end is None  # <3>
        index = 0
        while forever or result < self.end:  # <4>
            yield result  # <5>
            index += 1
            result = self.begin + self.step * index  # <6>
# END ARITPROG_CLASS

# can be done with just generator function
# BEGIN ARITPROG_GENFUNC
def aritprog_gen(begin, step, end=None):
    result = type(begin + step)(begin)
    forever = end is None
    index = 0
    while forever or result < end:
        yield result
        index += 1
        result = begin + step * index
# END ARITPROG_GENFUNC

# built in generator functions
import itertools

# itertool.count(start = 0, step = 1)
gen = itertool.count(1,0.5)
next(gen) # 1
next(gen) # 1.5
next(gen) # 2 

# next(it, default_val)
# iterate through iterator until it exhuasted will return the default value

# itertool.takewhile(predicate, gen)
# produce a generator that consume another generator and stop
# when the predicate evaluate to false
gen = itertool.takewhile(lambda n: n < 3, itertool.count(1,0.5))
list(gen) # [1,1.5,2,2.5]

# improve 
# not a generator function since it does not yield
# but it returns a gnerator that can yield 
def aritprog_gen(begin, step, end=None):
    first = type(begin + step)(begin)
    ap_gen = itertool.count(first,step)

    if end is not None: # there is end then cap the ap_gen
        ap_gen = itertool.takewhile(lambda n: n < end,ap_gen)
    return ap_gen

# -----------------------------------------------------------------------
# Filtering generator function
import itertools

# consume two iterable in parallel , yiedld item from it if
# the correspoding item in selector_it is truethy 
itertools.compress(it,selector_it)

# the opposite of takewhile, drop the item while predicate evaluate to true
# then yield the rest remaining items (no further check)
itertools.dropwhile(predicate, it)

# yield if predicate evaluae to true 
filter(predicate, it)

# opposite of filter, yield whatever predicate evaluate to false
itertools.filterfalse(predicate, it)

# yield items from a slice of it
# similar to s[:stop] or s[start:stop:step] excpet it is lazy 
itertools.islice(it, stop)
itertools.islice(it, start,stop,step = 1)


# -----------------------------------------------------------------------
# the mapping gnerator
# Yield accumulate sum, if func is provided then yield the result of applying
# to the first pair of the item, then to the first result and next item
itertools.accumulate(it,[func])
it = itertools.accumulate((1,2,3),lambda a,b: a*b)
list(it) # [1, 2, 6]

# yield tuple of (index, item) where index is counted from the start
# item is taken fromthe iterable
enumerate(iterable, start =0)

# apply func to each item of it , yield the result
# it N iterables are given then the function must take N argument
# iterables will be consumed in parallel
map(func, it1,
    [it2, ...,it3])
l1 = range(5)
l2 = range(1,6)
l3 = range(2,7)
m = map(lambda a,b,c: a + b + c,l1,l2,l3)
list(m) # [3, 6, 9, 12, 15]

# apply func to each item of it , yield the result
# if the it yield iterm iit, then func is appied as func(*iit)
itertools.starmap(func, it)
import operator
list(itertools.starmap(operator.mul, enumerate('abc',1))) #['a', 'bb', 'ccc']
# running avarage
list(itertools.starmap(lambda a,b: b/a, \
    enumerate(itertools.accumulate(range(5)),1))) # [0.0, 0.5, 1.0, 1.5, 2.0] 

# -----------------------------------------------------------------------
# generator function that merge multiple input iterables

# Yield all items from it1 to itN
itertools.chain(iter1,...,itN)

# yi# repeat the item indefinietly unless of number of repeatition is providedeld all items from each iterable it yield one after another
# it should yield iterable items
itertools.chain.from_iterable(it)

# Cartesian product yiled tuples of N items from each iterable 
# input like a neted loop
# repeats allows thei input iterables to be consumed more than once
# as if the provided inputer iterator has been repeated as input argument for repeated times
itertools.product(it1,...,itN, repeats = 1)
# [('a', 0), ('a', 1), ('b', 0), ('b', 1), ('c', 0), ('c', 1)]
list(itertools.product('abc',range(2)))


# yields tuple of N items build from items taken from
# iterables in parallel will stop when the first iterable is exhuasted
zip(it1,...,itrN)

# similar to zip ,but will only stop until the longest iterable
# exhuasted , fill the blank with fillvalue
itertools.zip_longest(it1,...,itN, fillvalue=None)


# -----------------------------------------------------------------------
# generator that expand the input

# yield combinations of out_len items from the items yield from it
# differen way to take out_len items from the iterable without replacement
itertools.combinations(it,out_len)
l = [1,2,3]
list(ltertools.combinations(l,2)) #[(1, 2), (1, 3), (2, 3)]

# same as combinations , but with replacement
itertools.combinations_with_replacement(it,out_len)
list(combinations_with_replacement(l,2)) #[(1, 1), (1, 2), (1, 3), (2, 2), (2, 3), (3, 3)]

# yield number at the start and increase by step infinitely
itertools.count(start=0, step =0)

# yield from it indefinietly through cycling the sequence
itertools.cycle(it)

# yield permutations of out_len items from the items yield from it,
# by default out_len is len(list(it))
itertools.permutations(it,out_len = None)
list(permutations('abc',2))
# [('a', 'b'), ('a', 'c'), ('b', 'a'), ('b', 'c'), ('c', 'a'), ('c', 'b')]
list(permutations('abc',3))
# [('a', 'b', 'c'), ('a', 'c', 'b'), ('b', 'a', 'c'), ('b', 'c', 'a'), ('c', 'a', 'b'), ('c', 'b', 'a')]

# repeat the item indefinietly unless of number of repeatition is provided
itertools.repeat(item,[times])
list(map(operator.mul, range(11), itertools.repeat(5)))
# [0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50]


# -----------------------------------------------------------------------
# rearrange generator function
# yield tule of 2 of items(key,group), where key is the grouping ceriteria,
# group is the generator yielding ht items in the group
# adjacent repeated item will be grouped
# key is predicate that takes argument of each item in the iterable
itertools.groupby(it, key = None)
g = itertools.groupby('aabccdea')
"""
[('a', <itertools._grouper object at 0x1079a1160>),
 ('b', <itertools._grouper object at 0x1079a11d0>),
 ('c', <itertools._grouper object at 0x1079a12b0>),
 ('d', <itertools._grouper object at 0x1079a12e8>),
 ('e', <itertools._grouper object at 0x1079a1320>),
 ('a', <itertools._grouper object at 0x1079a1358>)]
"""
for char, group in groupby('aabccdea'):
     print(char,'->',list(group))

"""
a -> ['a', 'a']
b -> ['b']
c -> ['c', 'c']
d -> ['d']
e -> ['e']
a -> ['a']
"""
# another example with key
a = ['aac', 'add', 'adcaa', 'abcca', 'aaaaa', 'dec']
a.sort(key = lambda x: len(x))
# ['aac', 'add', 'dec', 'adcaa', 'abcca', 'aaaaa']
for le, group in groupby(a,lambda x: len(x)):
...     print(le,'->',list(group))
...
# 3 -> ['aac', 'add', 'dec']
# 5 -> ['adcaa', 'abcca', 'aaaaa']

# yield item in reverse order, seq must be a seq or
# implement the __reverse__ method
reverse(seq)

# -----------------------------------------------------------------------
# yield from
def chain(*iter):
    for it in iter:
        yield from it # we can delegate the yield to the generator it
        """
        for i in it:
            yield i
        """
s = 'abc'
t = tuple(range(3))
l = list(chain(s,t))
print(l)
# -----------------------------------------------------------------------
# iterable reducing function

# return true if all item in it are truthy lese false
# all([]) returns true
all(it)

# any item in it is truthy return true, else flase
# any([]) returns false
any(it)

# returns the maxium value in it,
# key is ordering function, as in sorted
# default is returned if the list is empty
max(it, [key=,],[default=])
max(*args,key) # max arg will gets returned

# like max but find the minmum
min(it, [key=,],[default=])
min(*args,key) # min arg will gets returned

# sum all iterm from it with start point
# use math.fsum for better precision when adding floats
sum(it, start = 0)

import functools
# return the result of applying func to the first pair of items
# then to that result and third item and so on,
# if inital value was given then it will form the first pair with
# the first item in it as func arg
functools.reduce(fuc, it,[inital])
r = functools.reduce(lambda a,b: a+b,(1,2,3),100) #106

# -----------------------------------------------------------------------
# another use of iter function
# iter() could take a callable object that can be invoked repeatedly without arguments
# second arg is the sentinel which is a marker value that when returned by the callable
# will cause the iterator to raise SotpIteration instead of yielding the sentinel
callable_iterator_object = iter(func,sentinel)

# e.g. roll dice and stop when get 1
def d6():
    return randint(1,6)

d6_iter = iter(d6,1) # <callable_iterator object at 0x1079a16d8>
list(d6_iter) # [6, 3, 2, 3, 5, 5, 4]

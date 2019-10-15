#===================================================================
#topic list
-sequence
-dict & set
-iterables & iterator & generator

-object reference & mutability
-function Director and closure

-function
-object
-class
#===================================================================
#format
#https://www.python-course.eu/python3_formatted_output.php
#===================================================================
#arg parse
'''
-Multiple options in any order.
-Short and long options.
-Default values.
-Generation of a usage help message.
-requried args
'''
#https://www.pyimagesearch.com/2018/03/12/python-argparse-command-line-arguments/

from argparse

parser = argparse.ArgumentParser()
parser.add_argument("-f", "--file", dest="filename",required = True
                    help="write report to FILE", metavar="FILE")
parser.add_argument("-q", "--quiet",
                    action="store_false", dest="verbose", default=True,
                    help="don't print status messages to stdout")

#will turn argments name and arg values into dictionary
#args[file]
args = vars(parser.parse_args())

#command line arg
import sys
#command line argument can be access through sys.argv as list
print(sys.argv) #[arg1,arg2,arg3]
filename = sys.argv[1]

#===================================================================
#lambda
bigger = lambda  x , y : x if x > y else y
bigger(4,3)
fruits = ['apple', 'banana','pear']
sorted(fruits,key = lambda word: word[::-1])


#===================================================================
#list comphrehension
arr = [3,4,2,1]
val_pos={v:p for (p,v) in enumerate(arr)}

#* for unpacking
#https://www.python.org/dev/peps/pep-3132/
#===================================================================
#list comphrehension 
a = { good:1, #line break are ignored in [],{},(), no need \
     bad:2}

symbols = "absded"
ascii = [ord(s) for s in symbols if ord(s) > 127]
ascii = list(filter(lambda c: c> 127, map(ord,symbols))) #same as above

#cartesian product using list comphrehension
colors = ['black', 'white']
sizes = ['S','M','L']
#make two nested for loop in a listcomp
tshirts = [(color,size) for color in colors for size in sizes]

#-----------------------------------------------------------------
#using tuple unpacking to swap two variable without using a temp var
a, b = b, a
divmod(20,8)
t = (20,8)
divmod(*t) #*t unpack tuple as separate arg 

#using * for grab excess/rest items
a,b,*rest =range(5) 
'''
(0,1,[2,3,4])
'''
a,*body,b =range(5) 
'''
(0,1[1,2],3)
'''

*a, = range(5)

for a, *b in [(1, 2, 3), (4, 5, 6, 7)]:
    print(b)
'''
[2, 3]
[5, 6, 7]
'''

#unpacking nested tuple as long as expression match the nested struct
metro_area = [
    ('Tokyo','JP',36.933,(35.44,139.33)),
    #...
]
for name ,cc ,pop ,(lat, lon) in metro_area:
    #do something

#-----------------------------------------------------------------
#named tuple as record
from collections import nametuple
#class take two args:1.class name 2.field names delimited by space
City = nametuple('City','name country population coordinates')
Tokyo = City('Tokyo','JP',36.44,(35.32,193.11)) #construct an instance of this tuple class with filed init
Tokyo.name #can access filed by name or position
Tokyo[1] #JP

#inherited special method 
City._files #print out all the fileds
LatLong = nametuple('lat','lon')
shanghai_data = ('Shanghai','CN',21.2,Latlong(28.34,139.23)) #constructor could be inside another
Shanghai = City._make(shanghai_data) #init from a iterable , 
Shanghai = City(*shanghai_data) #will do the same
Shanghai._asdict() #return ordered dict with each file name as key

#-----------------------------------------------------------------
#slicing
s[begin:end:step] #step can be negative in opposite order
s.__getitem__(slice(start,stop,step))
#we cand name the slice object like name a group of cells in excel
#and then pass the slice object to the list the seq to retrive the relevant filed
UNIT_PRICE = slice(3,10)
items[UNIT_PRICE] #same as: items[3:10]

#multiple dim array with ellipsis
#for numpy.ndarray get access multiple dim array
a[i,j]
a[m:n,k:l]
x[i,...] #same as x[i,:,:,:,]

#assignment to slices
l[2:5] = [20,30]
del l[5:7]
l[3::2] = [11,22]
l[2:5] = [100] #when the target of assignment is a slice ,RHS must be an iterable

#-----------------------------------------------------------------
# using + and * with seq
# both + and * will create a new object but never chang the operands
l = [1,2,3]
l * 2#[1,2,3,1,2,3]
2 * 'abc' #'abcabc'
#when a * n a is a seq containing mutable items
#will return 3 reference to the inner mutable item
my_list =[[1]] * 3 #[[1],[1],[1]]
my_list[1][0] = 99 #[[99],[99],[99]]

#use listcomp to int list of list
board = [['_']*3] for i in range(3)] #seq of "_" not mutable

#-----------------------------------------------------------------
#build in sort
#will sort the original seq in place
sort(reverse = False,key = lambda r: r.upper())

#taks in a seq mutable or not mutable will return a new sorted seq
sorted_list = sorted(my_list,reverse = True, key = len)

#reversed
reversed(a) #return a reversed iterator will no change a
a.reverse() #will reverse a in place

#bisec searc
import bisect
bisec(haystack, needle) #seq must be sorted , will do binary search and return the index
#bisec is alias for bisec_right: when needle compares equal to an item in the list, it returns an
#insertion point after the existing item
#bisec_left returns the position of the existing item, so insertion could occur before it
def grade(score, breakpoints=[60,70,80,90],grades = 'FDCBA'):
    i = bisect.bisect(breakpoints,score)
    return grades[i]

#print [F,A,C,C,B,A,A]
[grade(score) for score in [33,99,77,70,89,90,100]]

#insort(seq, item) 
#insert itme into seq while keep seq in ascending order

#===================================================================
#Deque
from collections  import deque

#maxlen bound the que and will pop out from the opposite side you append when full
dq = deque(range(10), maxlen = 10) #deque([0, 1, 2, 3, 4, 5, 6, 7, 8, 9], maxlen=10)
#rotate(n) n > 0 , take element from the right end and prepend to the left
#when n < 0, items taken from the left end and append to the right
dq.rotate(3) #deque([7, 8, 9, 0, 1, 2, 3, 4, 5, 6], maxlen=10)
dp.appendleft(-1)
dp.extend([11,22,33]) #adding elements to the right
dp.extendleft([10,20,30,40])
dp.pop()
dp.popleft()

#-----------------------------------------------------------------
#dict
#different way to init a dict
a = dict(one=1,two=2,three=3)
b={'one':1,'two':2,'three':3}
c = dict(zip(['one','two','three'],[1,2,3]))

#can build dict from dictcomp
DIAL_CODE = [
    (86,'China'),
    (91,'India'),
]
country_code = {country:code for code,country in DIAL_CODE}

#creae a dict init keys with seq and default value
seq = range(0,10)
#{0: 10, 1: 10, 2: 10, 3: 10, 4: 10, 5: 10, 6: 10, 7: 10, 8: 10, 9: 10}
dict = dict.fromkeys(seq, 10) #int a dict with the iterable as key and init value as set

a = dict.pop(3) #will return the value associate with 3 and remove the entry with key of 3

#if key exits, will return the value associated with the key
#if not, will return the value inserted , will insert the key value pair
#setdefault is used to update items holding mutable values
a = dict.setdefault(10,99)
a= dict.fromkeys(range(10),[]) #will result all inner list reference to the same list
a = {k:[] for k in range(10)}

a= dict.fromkeys(range(10),10) #will result all inner list reference to the same list
a[2] += 1 #OK
a.setdefault(2,99) += 1 #not okay , can not do 10 += 1
#will check if 100 exists as key, if not will create a key with default value and return the
# reference to the value a[100] 
a.setdefault(100,[]).append(99)
#same as 
if 100 not a:
    a[100] = []
a.[100].appned(99)


# -----------------------------------
# some dict method
# update
dict = {'Name': 'Zara', 'Age': 7}
dict2 = {'Sex': 'female' }
dict.update(dict2) # now dict will have the content of dict2 as well its original
# {'Name': 'Zara', 'Age': 7, 'Sex': 'female'}


# -----------------------------------
#default dict
from collections import defaultdict
dd = defaultdict(int)
dd = defaultdict(lambda : 1)

#if the key does not exists
# will call int to construct the value with the key as entry
#return a reference to the value 
dd[key] += 1

#will update the dict according to the iterable that contains key value pairs
#if key does not exits, will create this entry
#if exists , will update the existing value
#equiv to the loop of assignment with dict[key] = value
dict.update([(1,100),(2,100),(3,100),(88,100)])
dict.values()
dict.keys()

#Counter:take an iterables and will return freq of each iterable
#Counter({'e': 3, 'a': 2, 'b': 1, 'c': 1, 'd': 1, 'f': 1})
ct = collections.Counter('aabcdeeef')
#Counter({'apple': 2, 'beef': 1, 'orange': 1})
ct = Counter(['apple','beef','apple','orange'])
#update will udpate the counter freq with the new arg
#Counter({'apple': 3, 'd': 2, 'beef': 1, 'orange': 1, 'a': 1, 'b': 1})
ct.update(['apple','a','d','d','b'])
#[('apple', 3), ('d', 2)]
ct.most_common(2)
#-----------------------------------------------------------------
#default containers
from collections import defaultdic
num_freq = defaultdict(int)   #init dict with default value of int of 0
num_freq['a'] += 1 #ventry a:1
#-----------------------------------------------------------------
#set 
s = set() #to init an empty set, {} init a dict not set
s = {1,2,3} #int set faster than s = set([1,2,3])
from unicodedata import name
{chr(i) for i in range(32,256) if 'SIGN' in name(chr(i),'')} #setcomp

#operator &,|,-,^ can only operate between sets,but words expression can
#operate on set between iterable of any kind

u = a | b # b must be a set
b = [1,2,3]; c = [3,3,4,5]
U = a.union(b,c) #a must be set , b and c could be iterable of any type
a |= b# a = a | b
a.union_update(b)

i = a & b
I = a.intersection(b,c)
a &= a & b #a = a & b
a.intersection_update(b)

d = a -b # a has but b does not
d = a.difference(b)
b -= a #b = b-a
b.difference_update(a)

x = s ^ z # s xor z
x = s.__xor__(z)
s ^= z
s.__ixor__(z)

b = e in s
b = s <= z #s is a subset of z
s < z #s is a proper set of z

#set method
s.add(e)
s.discard(e) #remove e if e exists
s.pop() #remove a elemen and return , if s empty raise error
s.remove(e) #remove e from s ,it not exists raise error

#Key ordering depends on insertion order
DIAL_CODE = [
    (86,'China'),
    (91,'India'),
]
d1 = dict(sorted(DIAL_CODE, key = lambda x:x[1])) #sorted by country code
d2 = dict(sorted(DIAL_CODE, key = lambda x:x[0])) #sorted by country name

'''
when adding item to the dict may change the existing order of the key:
when adding new item, python may decide that the hash table might need
to grow and add all current item to the new table,resulting hash collision
key might order differently.
if you iterate over the dictionary keys and changing them at the same time
your loop may not scan all the items as expceted
if you want to modify the content of the dict while iterating throught it
-make a copy of the dict to iterate
-update the original dict
'''

#-----------------------------------------------------------------
# heap
import heapq
Q = [1,2,3]
heapq.heapnify(Q)
popped = heapq.heappop(Q)
heapq.heappush(popped)


# priority queue
from queue import PriorityQueue

q = PriorityQueue()

q.put((2, 'code'))
q.put((1, 'eat'))
q.put((3, 'sleep'))

while not q.empty():
    next_item = q.get()
    print(next_item)

# Result:
#   (1, 'eat')
#   (2, 'code')
#   (3, 'sleep')
#===================================================================
#expressions

#tinary expression
#value_when_true if condition else value_when_false
fruit = 'Apple'
isApple = True if fruit == 'Apple' else False

if someBoolValue: num1=20
#===================================================================

#object mutability
#python assigment is reference assignment
a = [1,2,3]
b = a
a.append(4)
b #[1,2,3,4]

#tuple immutability:what the tuple holds is constant , which is the reference to the object
#if the object is mutable , then object can be changed through the reference inside tutple
t1 = (1,2,[30,40])
t1[-1].append(99) #will change

#copies are shallow by default
l2 = list(l1) #create a copy of l1

#the shallow copy will contains the reference to the same items held by the original
#container would be no problem if all items are immutabible
#due to the fact that containers will contain the reference to the object
l1 = [3,[66,55,44],(7,8,9)]
l2 = list(l1) #l2 is a shallow copy of l1
l1.append(100) #add a new reference in containter l2 no effects on l2
l1[1].remove(55) #change in l2 since l1[1] reference to the same object as in l2
print('l1: ', l1)
print('l2: ', l2)
l2[1] += [33,22] #will change in l1 since reference to the saem list
# same as l2[2] = l[2] + (10,11)
l2[2] += (10,11) #will creaet a new tuple and return so no more alias with l1

#shallow vs deep copy
#shallow copy will copy each object's reference as in the container
#deep copy will allocate new space and copy the value of each objects into the
#new space and contains each reference of it
#cotainers contains mutabile objects and if want independance , use deepcopy
import copy

bus1 = Bus(['a','b','c'])
bus2 = copy.copy(bus1)
bus3 = copy.deepcopy(bus1)
#bus 1, 2 ,3 are different containters

#bus 3 will not be affected since it create as new list when copy
#which is independant of that in bus1
bus1.drop('a') #bus2 will remove a as well since reference to the same list

#function params as reference
def f(a,b):
    a+=b
    return a

x=1;y=2;
#x,y will not change since x, y immutabible
#+= will create a new object and gets returned orignal object will not get affected
f(x,y)
t = (10,20); u = (30,40);
f(t,u)
a = [1,2]
b = [3,4]
f(a,b) #a pass in as ref and will be changed inside

#using mutable object as function params is a bad idea
#since default value is evaluated when the function is defined
#if it is aliated to a memebr of the function, every time the default value 
#changed it will affects future function calls
#e.g. instead of using [] as default params for class memeber
#we could use none for potential mutable object as default params
#we could then initialise [] if the arg is none

#if we do not expect the function will change the mutable object when we pass it in
#as params, we could make a deep or shallow copy(depends on the objects that this object 
#contains whether mutable or immutabible) then we can just operate on the copy of this mutable
#object without having side effects on the orignal objects

#===================================================================
#how to write doc 
https://realpython.com/documenting-python-code/
#first class functions
def func():
    '''function help doc use with
       func.__doc__ or help(func)
    '''
    return 1

#user defined callable type
#only need to implememnt a __call__ instance method
#good things is that a function like object that could have some internal state keeping
class Bus:
    def __init__(self,items):
        self._items = list(items)

    def pick(self):
        return self._items.pop()

    def __call__(self):
        return self.pick()

#positional and keyward params
#content will capture any args that comes after first positional arg that is not keyword arg as tuples
#attrs will capture all keyword args that is not explicitly name in the function signiture as dict
#positional argument will take argument as in the specfied position as in the function signiture
def tag(name, *content, cls=None, **attrs):
    pass

#general order: position args->rest of the positional args->named keyword args->rest keyward args
tag('br') #store in the positional arg in name
tag('p','hello') #hello will store in content as (hellow) 
tag('p','hello','world') #contents:('hello','world')
tag('p','hello',id=33) #atrrs: {id:33}
tag('p','hello','world',cls='sidebar') #cls = sidebar
tag(content='testing',name = "img") #even the first position arg can be called 
my_tag_dict = {'name':'img','title':'sunset','src':'sunset.jpeg','cls':'framed'}
tag(**my_tag_dict) #will pass in args as individual keyward args ,named none will be captured ,rest in attrs

#to specify keyword-only args when define a function , name then after the argument prefixed with *
#if do not want support variable lenght arg , simply just put * between positional and keyward args
def f(a,*,b): #a is positional, b is keyward without default value
    return a,b
#===================================================================
# class
#class representation
class Coordinate(object): #object is the parent class 
    #definition here
    def __init__(self,x,y): #constructor for this object
        self.x_ = x #self is a place holder for the instance when the object is constructed
        slef.y_ = y

    def __str__(self): #special method will be called when call print
        print(self.x_,self.y_)

    #operator defined
    def __add__(self,other): #add two objects a + b

    def __sub__(self,other): #add two objects a + b

    def __equal__(self,other): #add two objects a + b




#===================================================================

#===================================================================
#doc test
http://pythontesting.net/framework/doctest/doctest-introduction/
https://pymotw.com/3/doctest/

python3 -m doctest -v my_prog.py

def point_include(num):
    """compare point_include(num) with num2words(num).
    number with points:
    >>> point_include(920494030.103567) == num2words(920494030.103567)
    True

    More tests:

    >>> point_include(9294030.103567) == num2words(9294030.103567)
    True
    >>> point_include(92930.103567) == num2words(92930.103567)
    True
    >>> point_include(930.103567) == num2words(930.103567)
    True
    >>> point_include(30.103567) == num2words(30.103567)
    True
    >>> point_include(19.103567) == num2words(19.103567)
    True
    """
    pass

#test can be done in a separate text file
"""compare point_include(num) with num2words(num).
number with points:
>>> from num_text import *
>>> point_include(920494030.103567) == num2words(920494030.103567)
True
"""
#===================================================================
# decorator
# single dispatch function
http://hackwrite.com/posts/learn-about-python-decorators-by-writing-a-function-dispatcher/

from functools import singledisptach
# cache the most recently used func call result
# use dict to store the result ,key uses positional and keyward argument
# so arguments must be hashable
functionfools.lru_cache(maxsize=128, typed=False)



# function as object 
# set attributes
def foo():
    l = [1,2,3] 
    print(l)
    def change(i):
        l.append(i)
    def wrapper():
        pass
    wrapper.change = change
    wrapper.l = l
    return wrapper

foo.sex = "good"
foo()
foo().change(99)
foo()

#===================================================================
# memory view
https://julien.danjou.info/high-performance-in-python-with-zero-copy-and-the-buffer-protocol/


#===================================================================
#code documentation
https://realpython.com/documenting-python-code/

# TODO: somehing
# FIXME:

# ----------------------
# compile python to c
https://github.com/Nuitka/Nuitka#requirements

#===================================================================

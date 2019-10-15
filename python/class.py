

# ===================================================================================
# array 
# support all mutable sequence operation(pop, insert, extend) and additional methods for
# fast loading and saveing like: .frombytes and .tofile
from array import array
from random import random

# since it is like a c array need to specify the type code 
# follow a iterable object to initialise the array
floats = array('d',(random() for i in range(10**7)))
floats[-1] # substribtable

bb = floats.tobytes() # convert back to bytes
floats0  = array('d')
floats0.frombytes(bb) # reconstruct from bytes

fp = open('floats.bin','wb')
floats.tofile(fp) # writes the binary to file
fp.close()

floats2 = array('d') # init an empty array of type d
fp = open('floats.bin', 'rb')
floats.fromfile(fp,10**7) # read from file to init array
fp.close()
floats2[-1]

# ===================================================================================
# bytes
# two built in type for binary seq: immutable bytes type, mutable bytearray
# both bytes and bytearray support every str method except those that do formating
# endswith(), replace(), strip, translate, upper 
# regex supports binary sequence as well
b = bytes(array.array('h',(x for x in range(5)))) # create byte stream from an iterable object
bytes.fromhex('31 4B CE') # build by parsing pairs of hex digits

cafe = bytes('cafe',encoding='utf_8') # encoding only used for string argument
cafe[0] # 99
cafe[:1] # b'c'

cafe_arr = bytearray(cafe)
cafe_arry[:-1] # a slice of a byte array is still a byte array

# ===================================================================================
# memoryview
# like a pointer , to share the underling memory without copy the object
numbers = array.array('h',[-2,-1,0,1,2])
memv = memoryview(numbers)
len(lemv)
memv[0] # could substribe elementskj
# cast to another memv view type , with still same
# with the same memory pointers but different type interperation
memv_oct = memv.cast('B')
memv_oct.tolist()
memv_oct[5] = 4
print(numbers) # the related bytes will change according to preivous modification
# ===================================================================================
# struct
# provides functions to parse packed bytes into a typle of fields of different types or
# to perform the opposite conversion, from a tuple into packed bytes
import struct
# < little endian;3s3s two sequence of 3 bytes;HH two 16 bit integers
fmt = '<3s3sHH'
with open('fileter.gif', 'rb') as fp:
    img = memoeryview(fp.read()) # create a shared memoryview without copy
header = img[:10] # get the first 10 bytes of the memoryview
bytes(header) # will return a copy of the bytes
struct.unpack(fmt,header) # will unpack bytes sequence as format
#(b'GIF',b'89a', 555, 230) type, version,width, height
del header # remove the memoryview reference
del img


# ===================================================================================
# class
# -------------------------------------------------------------------------
"""
A 2-dimensional vector class
# BEGIN VECTOR2D_V0_DEMO

    >>> v1 = Vector2d(3, 4)
    >>> print(v1.x, v1.y)  # <1>
    3.0 4.0
    >>> x, y = v1  # <2>
    >>> x, y
    (3.0, 4.0)
    >>> v1  # <3>
    Vector2d(3.0, 4.0)
    >>> v1_clone = eval(repr(v1))  # <4>
    >>> v1 == v1_clone  # <5>
    True
    >>> print(v1)  # <6>
    (3.0, 4.0)
    >>> octets = bytes(v1)  # <7>
    >>> octets
    b'd\\x00\\x00\\x00\\x00\\x00\\x00\\x08@\\x00\\x00\\x00\\x00\\x00\\x00\\x10@'
    >>> abs(v1)  # <8>
    5.0
    >>> bool(v1), bool(Vector2d(0, 0))  # <9>
    (True, False)

# END VECTOR2D_V0_DEMO
"""


from array import array
import math

# BEGIN VECTOR2D_V3_SLOTS
class Vector2d:
    __slots__ = ('__x', '__y')

    typecode = 'd'

    # methods follow (omitted in book listing)
# END VECTOR2D_V3_SLOTS

    def __init__(self, x, y):
        self.__x = float(x) # attribute start with __ is private
        self.__y = float(y)

    @property # property decorator marks the getter method of the property
    def x(self):
        return self.__x

    @property
    def y(self):
        return self.__y

    def __iter__(self): # return iterator object for looping 
        return (i for i in (self.x, self.y))

    def __repr__(self):
        class_name = type(self).__name__
        return '{}({!r}, {!r})'.format(class_name, *self)

    def __str__(self): # str representation when print the object
        return str(tuple(self))

    def __bytes__(self): # called when built in bytes is called
        return (bytes([ord(self.typecode)]) +
                bytes(array(self.typecode, self)))

    def __eq__(self, other): # self == other 
        return tuple(self) == tuple(other)

    def __hash__(self): # for hash(self) for hashable in map or set
        return hash(self.x) ^ hash(self.y)

    def __abs__(self): # called when built in function abs(self)
        return math.hypot(self.x, self.y)

    def __bool__(self):
        return bool(abs(self))

    def angle(self):
        return math.atan2(self.y, self.x)

    def __format__(self, fmt_spec=''): # when format(slef, format_spec) is called 
        if fmt_spec.endswith('p'):
            fmt_spec = fmt_spec[:-1]
            coords = (abs(self), self.angle())
            outer_fmt = '<{}, {}>'
        else:
            coords = self
            outer_fmt = '({}, {})'
        components = (format(c, fmt_spec) for c in coords)
        return outer_fmt.format(*components)

    @classmethod
    def frombytes(cls, octets): # to build the object from bytes
        typecode = chr(octets[0])
        memv = memoryview(octets[1:]).cast(typecode)
        return cls(*memv)


# -------------------------------------------------------------------------
# format
# the format bult in function and the str.format() method delegate the actual 
# formatting to each type bye calling their .__format__(format_spec) 
# format(my_obj, format_spec)
# the format specifier is called the format specification Mini-Language
brl = 1/2.43# 0.4115226337448559
format(brl,'0.4f') # '0.4115' '0.4f' is the format_spec
# {} is the replacement field rate is called the field name , which determines which argment
# would later goes into the replacement filed, 0.2f is the format_spec
'1 BRL  ={rate:0.2f} USD'.format(rate=brl) # '1 BRL  =0.41 USD'

# -------------------------------------------------------------------------
# private and protected
# attributes that marks __ will "private" to the class, but still user can get access
# to the the atrributs by _ClassName__atrr = 99 , this is called name mangling, to preven user 
# accidently chagne the value of the supposed to be private atttributes of the class
# name mangling is also to prevent the name shaowing , e.g. if there is mood attributes in 
# dog and subclass dog as Beagle and it also has a mood attributes.
# name mangling can prevent this since if we do __mood in both calls then 
# the one in dog will be _Dog__mood, and one in Beagle will be _Beagle__mood

# -------------------------------------------------------------------------
# class vs object attributes
https://dzone.com/articles/python-class-attributes-vs-instance-attributes
https://www.toptal.com/python/python-class-attributes-an-overly-thorough-guide
# when obj.class_attr = 99 , then obj will create a dynamic attribute called the class_atrr
# so the class attributes would not change if class_attr is immutable
# if class_attr is mutable, it will actually change the class_attr

# when obj,x = 99 , when x is not in the current objt attribute , then it will create a new one
# for this object if x happens to be the class attributes , objc.x will shadow the class 
# atrributes, since next obj.x will retrieve the objt attributes instead of the class one

# if want to change need to set through the class directly
# usually we subclass the base class just to change some class data atrributes
class ShortVector2d(Vector2d):
    typecode = 'f' # just to override the class attributes

# -------------------------------------------------------------------------
# saving space with __slots__ atrributes
# python stores instance atrributes in a per instance dict named __dict__
# since dict using hashing and the overhead for meory is high ,e.g. we have 
# milions of object with few attributes

# cavet when using __slots__
# 1.once the object has defined the __slots__ the instance can only have the attributes in slots
# 2.instance when call __slots__ will only show the attributes but not the value
# 3.sublcass need to redeclare __slots__ since inheritance would ignore it


# -------------------------------------------------------------------------





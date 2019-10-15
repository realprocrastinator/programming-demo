
#generate the list of date range and append it to list L
# Fit a line, ``y = mx + c``, through some noisy data-points:
list = ['larry', 'curly', 'moe']
list.append('shemp')         ## append elem at end
list.insert(0, 'xxx')        ## insert elem at index 0
list.extend(['yyy', 'zzz'])  ## add list of elems at end
print(list)  ## ['xxx', 'larry', 'curly', 'moe', 'shemp', 'yyy', 'zzz']
print(list.index('curly'))    ## 2
list[::-1]  #will print the list backward -1 means increase the index -1
list.remove('curly')         ## search and remove that element
list.pop(1)                  ## removes and returns at the index
print(list)  ## ['xxx', 'moe', 'shemp', 'yyy', 'zzz']
L = [1] + [2, 3]
L += [4, 5, 6]  #add to the end of the list
L = [1, 2] * 3  #repeat the list 3 times and concat into one list

#create a list of list
l1= []
for i in range(10):
    l1.append(list(range(10)))
    
#alias for each element of the list and if mutable will change the alias as well
l=[1,2,3,4,5]
l = [[item] for item in l]  #[[1], [2], [3], [4], [5]]
a = l[:2]  #[[1], [2]]
l[0][0] = 10    #[[10], [2], [3], [4], [5]]
a  #[[10], [2]]

#sorting
#key specifies a function of one argument that is used to extract a comparison
#key from each list element:
strs = ['xc', 'zb', 'yd' ,'wa']

#sorted will sort based out the outcome of the transformation given in the
student_tuples = [
...     ('john', 'A', 15),
...     ('jane', 'B', 12),
...     ('dave', 'B', 10),
... ]
sorted(student_tuples, key=lambda student: student[2])
print(sorted(strs, key=MyFn, reverse = True))  ## ['wa', 'zb', 'xc', 'yd']


#list comphrehension
[expr for item in iterabe [filter condition]]

nums = [1, 2, 3, 4]
squares = [ n * n for n in nums ]   ## [1, 4, 9, 16]
strs = ['hello', 'and', 'goodbye']
shouting = [ s.upper() + '!!!' for s in strs ]
small = [ n for n in nums if n <= 2 ]  ## [2, 1]

colors = ['Royal Blue', 'Grey']
sizes = ['S','M','L','XL']
tshirts = [(color, size) for color in colors for size in sizes]
[x if x % 2 else -x for x in range(15) if x % 3]


#Caveate to create list of list



#Generator
(expr for var in interable [filter condition])
colors = ['Royal Blue', 'Grey']
sizes = ['S','M','L','XL']
tshirts = ((color, size) for color in colors for size in sizes)



#############################Queque###########################################
import queue 
q = queue.Queue()
q.put(1)    #enqueque
q.get()     #dequeque



##priority que
import heapq
heapq.heapify(h)  #returns  [0, 2, 1, 4, 5, 6, 2, 8]
heapq.heappush(h,7)
heapq.heappop(h)
heapq.heappushpop(h,3)  #push item to the heap and return the first on heap

heappush(h, (5, 'write code'))
heappush(h, (7, 'release product'))
heappush(h, (1, 'write spec'))
heappush(h, (3, 'create tests'))
heappop(h)


#########################Set#################################################
#set() – set is mutable collection of unique elements
a= set(range(10))
b= {11,12,4,5,3,13}
a.intersection(b); a & b
a.union(b) ;a | b ; a |= b
a.add(18)
a-b    #return a set that a has but not b
a.intersection_update(b); a &= b  #only leave in a the intersection with b
a-=b     #


#########################Dictionary and Default Dic#########################
#python dict key must be uniq and immutable object like tuple
mydict={'a':1,'b':2,'c':3}
otherdict=dict((['a',1],['b',2],['c',3]))
mydict['a'] = 'alpha'

#initialise dic from keys can define and intial value as well
seq = ('name', 'age', 'sex')
dict = dict.fromkeys(seq)
print("New Dictionary : %s" %  str(dict))
dict = dict.fromkeys(seq, [10,8,9])
print("New Dictionary : %s" %  str(dict))



for key in dict: print(key)
print(dict.keys())
print(dict.values())  ## ['alpha', 'omega', 'gamma']

## .items() is the dict expressed as (key, value) tuples
print(dict.items()) ##  [('a', 'alpha'), ('o', 'omega'), ('g', 'gamma')]
for k, v in dict.items(): print(k, '>', v)

##dic formating
hash = {}
hash['word'] = 'garfield'
hash['count'] = 42
s = 'I want %(count)d copies of %(word)s' % hash  # %d for int, %s for string
  # 'I want 42 copies of garfield'

##del
del list #delet a var definition
l = ['a', 'b', 'c', 'd']
del list[-2:]   ## Delete last two elements

dict = {'a':1, 'b':2, 'c':3}
del dict['b']   ## Delete 'b' entry

dict.pop('b')   #will remove the entry and return the value assoicated with the key




#########################Enumerator######################################
icecream_flavors = ['chocolate','butterscotch','dark current','vanilla']
en = enumerate(icecream_flavors,initial_index)    #will return a enumerate object can access by next()
next(en)
for i,flav in enumerate(icecream_flavors,2): print('%d : %s ' % (i,flav))


#########################Default Dic#########################
#default dict initialized with a function (“default factory”) 
#that takes no arguments and provides the default value for a nonexistent key.
#pass in the function object but not the function defaultdict(func)
from collections import defaultdict
a=defaultdict(lambda :None) #will initialise the default value of dict
b=defaultdict(list)
mydict=defaultdict(int)




###########################File###############################################
#The special mode 'rU' is the "Universal" option for text files 
#where it's smart about converting different line-endings 
#so they always come through as a simple '\n'.
f = open('foo.txt', 'rU')   #open a file handler s'r', use 'w' for writing, and 'a' for append.

f.read() #method reads the whole file into a single string
f.readlines() #reads the whole file into memory and returns its contents as a list of its lines. 
f.write(string) #is the easiest way to write data to an open output file.

###########################Untility Module#####################################
 #-- list of filenames in that directory path 
#(not including . and ..). The filenames are just the names in the directory, 
#not their absolute paths.
filenames = os.listdir(dir)

#-- given a path, return an absolute form, e.g. /home/nick/foo/bar.html
os.path.abspath(path) 

#-- given dir/foo/bar.html, return the dirname "dir/foo" and basename "bar.html"
os.path.dirname(path), os.path.basename(path) 

os.path.exists(path) #-- true if it exists

shutil.copy(source-path, dest-path) #-- copy a file (dest path directories should exist)

import os
cwd = os.getcwd()

os.chdir("/tmp/")

##########################Filtering###############################################
##lambda
lambda arguments : expression
x = lambda a:a+1
x(2)
bigger = lambda  x , y : x if x > y else y
bigger(4,3)


##map
#function will take each element as parametr and do transformation and return
#the transformed interalbles
a = [1,2,3,4,5,6,7,8,9,10]
def square(x):
    return x * x
squares = map(square, a)

a = [1,2,3,4,5,6,7,8,9,10]
even = lambda x: True if x %2 == 0 else False
evens = list(map(even, a))

a = [1,2,3]
b = [4,5,6]
add_list = list(map(lambda x,y: x+y, a,b))

#filter will put each element in the function and evaluate and only keep the
#element that has been evaluated to true in the return generator object
filter(function or None, iterable)

#select even number in the list return a generator object and then from the generator object
#transform each element to the sqaure and then instantiated the returned object as list
a = [1,2,3,4,5,6,7,8,9,10]
even_squares = list(map(lambda i : i**2, filter(lambda i :i %2 ==0,a)))



#reduce 
#Apply a function of two arguments cumulatively to the items of a sequence,
#from left to right, so as to reduce the sequence to a single value.
from functools import reduce

a =[1,2,3,4]
reduce(lambda x,y: x+y,a)   #to get sum

a =[11,2,13,41,34,30]
max_value = lambda x,y: x if (x > y) else y  #get max

###########################Some Methods########################################
  
foo.lstrip() # to remove leading white space
foo.rstrip() # to remove trailing whitespace
foo.strip()  # to remove both lead and trailing whitespace

[x for x in dir(list) if not x.startswith('__')] #check method available

#join
seq = ("a", "b", "c");
delimiter = "-"
print(delimiter.join(seq))

#split
#The method split() returns a list of all the words in the string, 
#using str as the separator
str.split(delimiter, num)
s= "this|word| is | so | good"
s.split("|") #['this', 'word', ' is ', ' so ', ' good']

print('{0:2d} {1:3d} {2:4d}'.format(x, x*x, x*x*x))
print("Art %5d, Price per Unit :%8.2f" % (453,59.089))
print("hello",end = "$");
print('PRINT 0:  a =', a,
      ' m =', m, ' n =', n,
      '        x =', x)


#scope
#the inner function could get access to the value of the same variable in the outer
#function and if there is same name it will find the value that from inner to outer
#the nearest one

global n    #specify the scope of this variable is referring global var
#The nonlocal statement is useful in nested functions. 
#It causes the variable to refer to the previously bound s
#variable in the closest enclosing scope
nonlocal n  
###########################OOP###############################################
class Myclass(inhterited_class):
    x=1
    __num_elements = 10 #private atrributes can not be access outside
    def hello():
        print("hello")
        s
print(Myclass.x)
Myclass.y =10   #can change the the attributes from the outside

obj_1 = MyClass()       #create an instance of the calss as if it is a function

#initilisation of the object
class Employee(object): #ts a reference of the object on which method is applied.
    def __init__(self, first_name, last_name):
        self.first_name = first_name
        self.last_name = last_name
        
emp_1 = Employee("James","Tylor")

#class attributes shared amonng all instance and change in the classs will affect
#the objects instantilised from that class, aka each objesct has a pointer to the shared
#class attributes like global var

#a instance method is defined with the first parametre as self 
class ClassName(object):
     def a_instance_method(self):
          statements
          
class MyClass(object):
    x = 10
    def get():
        return self.x    
    def set(value):
        self.x = value
s
#Class method
class Employee(object):             
    @classmethod
    def i_am_class_method(cls): 
        pass        

#class methond could be called without substatiation of the instance
Employee.i_am_class_method()


#static method could be access by both class and instances just as a module level function
class Employee(object):       
    @staticmethod
    def i_am_static_method():
        pass

#Inhteritance
class Person(object): 
    def __init__(self,f_name, l_name): 
        self.first_name = f_name 
        self.last_name  = l_name
 
    def get_name(self): 
        return self.first_name +" " + self.last_name


class Employee(Person):
    def __init__(self,f_name, l_name,emp_id,emp_title ):
        #initialise super class then the uniq part of itsefl as sub  class
        Person.__init__(self,f_name,l_name)
        #super() will call parent class
        #super().__init__(f_name, l_name)
        self.employee_id = emp_id
        self.title  = emp_title

    def isEmployee(self):
        return True
    
e1 = Employee("Alex","Branden",23456,'Director')

###########################OOP###############################################
def main():

if __name__ == "__main__":
    main()
    #do something
    #the begining of the programme

#command line arg
import sys
#command line argument can be access through sys.argv as list
if sys.argv < 2:
    print('To few arguments, please specify a filename')
filename = sys.argv[1]













https://realpython.com/inheritance-composition-python/

# =====================================================================
# super()
https://realpython.com/python-super/
https://appdividend.com/2019/01/22/python-super-function-example-super-method-tutorial/
"""
The super() builtin function returns a proxy object, a substitute object a substitute
object that can call the method of the base class via delegation.
This is called indirection (ability to reference base object with super())
"""

"""
- derived class would inherited all method atrributes of the base class
- derived class could init the base class via calling the base class constructor
super().__init__(arg1,arg2)
- derived class could reimplement the base class method
- not like c++ python class method can be accessed both through object as well from class
- class attributes better to be assigned through either class name directly or
object method or class method
- class name could access object method,like Base.objectmethod(base_obj)
"""

# -----------E.g. Start----------------------------
class Base:

    """
    class attributes can be accessed both through the class name or the object name, but
    if assignemnt of through the object then it will create a object attributes instead of
    change the class attributes, since it will the attributes does not exists in the object
    so it will dynamically create the attribtues for this object
    so it is better to change the class attributes using class name or a object or class method
    """
    attr = 99

    """
    if object method needs to change class attributes need to specify the class attributes
    through the class name
    """
    def change(self):
        Base.attr = 100

    @classmethod
    def class_name(cls):
        print("This is base")

    def __init__(self,x,y):
        self._x = x
        self._y = y

    def getx(self):
        print("good job")

class Derived(Base):
    def name(self):
        # Base.class_name()
        super().class_name()

    # if there is no overriden the constructor then
    # the base class constructor will be used
    def __init__(self,x,y):
        super().__init__(x,y) # call the base class constructor
        self._z = 99 # any additional attribtues than base init

    # same function definition will override the base class implementation
    def getx(self):
        print("get x in derived")
        #super().getx()

    # additional method is the additional method to this subclass
    def getz(self):
        print(self._z)

    def __str__(self):
        return "({},{},{})".format(self._x,self._y,self._z)


d = Derived(33,44)
d.getx()
d.getz()
print(d)
d.name()

b = Base(22,33)
b.class_name()
Base.class_name()

b.change()
print(Base.attr)

# -----------E.g. End----------------------------
# =============================================================================
# abc
# In hr.py
from abc import ABC, abstractmethod

# since Employee inherited the ABC, its object can not be instantiated 
class Employee(ABC):
    def __init__(self, id, name):
        self.id = id
        self.name = name

    # abc can have default method that subclass can either
    # inherite or overried it implementation is not mandatory
    def default_method(self):
        pass

    # the abstract method must be overried
    # if the subclass did not overried all the abstract method
    # then the subclass is still abc
    @abstractmethod
    def calculate_payroll(self):
        pass

# when to inherit: when there is an is a relationship , subclass is a base class
# and we want to resue most of the base class implementation of the subclass

# inheritance can lead you to a huge hierarchical structure of classes 
# that is hard to understand and maintain. This is known as the class explosion problem.


# Method resolution order MRO
MyClass.__mro__()


# =============================================================================
# composition
# a composite class is a class that has components object of other classes to 
# reuse the implementation, or delegate as a service to this class
# can be used when there is not bouding is a relationship which provides more flexibility

# =============================================================================
# Mixin
# provide methods for other class but is not considered as a base class
# A mixin allows other classes to reuse its interface and implementation 
# without becoming a super class.

# e.g.
class AsDictionaryMixin:
    def to_dict(self):
        return {
            prop: self._represent(value)
            for prop, value in self.__dict__.items()
            if not self._is_internal(prop)
        }

    def _represent(self, value):
        if isinstance(value, object):
            if hasattr(value, 'to_dict'):
                return value.to_dict()
            else:
                return str(value)
        else:
            return value

    def _is_internal(self, prop):
        return prop.startswith('_')




class Employee(AsDictionaryMixin):
    pass

print_dict(employee.to_dict())
# =============================================================================
# inherit from built in class
https://github.com/fluentpython/example-code
"""
inheritance directly from the built in type like list or dict should be avoided
since the built in method would ignore the user defined override
e.g. like mydict.update() will ignore the __getitem__() method overried by user but still use
the built in one that mydict inherited from
"""

# -----------E.g. Start----------------------------
class DroppelDict2(collections.UserDict):
    def __setitem__(self,key,value):
        super().__setitem__(key,[value]*2)

dd = DroppelDict2(one=1)
dd # {'one':1}
dd['two'] = 2
dd # {'one':1,'two':2}
dd.update(three=3)
# -----------E.g. End----------------------------

# =============================================================================
# mutiple inheritance
# if there is ambigiaty when call method with the same method name from different super class
# we can explicitly call the classname then explicity pass the object as the self argument to
# the method
# super() can be used instead , which would follow the MRO(method resolution order)
C.pong(d)







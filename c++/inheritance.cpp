#include <iostream>

using namespace std;

// --------------------------------------------------------------------------------------
// Inheritance and constructors
// Every subclass constructor must call a base class constructor
// If none is manually called, the default constructor is used
// A subclass cannot initialise fields defined in the base class
class SClass: public BaseClass {
    public:
        // call base class constructor
        SClass(int member, int* ptr): BaseClass{member}, ptr_member_{ptr} {}
        // Won't compile.
        SClass(int member, int* ptr): int_member_{member}, ptr_member_{ptr} {}
       
    private:
        std::vector<int> vector_member_;
        int* ptr_member_;
}

// --------------------------------------------------------------------------------------
// object slicing problem
// when a base class is expected then a subclass get passed in
// then the compiler only knows that the passed in object is a
// baseclass , therefore it only knows the base class part of the 
// object
// could solved by passing a base class reference or pointer since
// pointer size is fixed and can be determined at compile time


// virtual function
// virtual keyward before the function to explicitly tell the compiler that
// this function can be override by the subclass
// subclass that intents to override the virtual function can specify override before
// the function body to explicitly saying to override the function in the base class
// advantange of using override is that if there is miss spelling or signiture miss match
// complier will complaint
// if virtual function is not overriden then virtual function will be the subclass's default
// implementation

// vtable
https://pabloariasal.github.io/2017/06/10/understanding-virtual-tables/
// each class will rememeber what function it has overriden so to call for itself
// and store all overriden virtual function that it should call in a vtable
// Each class has a VTable stored in the data segment
// vtable is an array of function pointers that points to the virtual functions
// that this class should use
// if the class's vtable is not empty then every instance/object of that class
// will store a pointer to the vtable in that class
//
// when the virtual function is called on a pointer or a reference type then
// -follow the vtable pointer to get to the vtable
// -goes to a constant offset which is the pointer for that function
// -follow the function pointer in the vtable and call that function

class BaseClass {
    public:
        int GetMember() { return member_;}
        // intend for subclass to imlement with defualt implementation as 
        // inherited baseclass implementation
        virtual string GetClassName() const{ return "BaseClass";}
    private:
        int member_;
};

class SubClass: public BaseClass {
    public:
         // the imeplemented virtual function is also a virtual function
         // final means that it is not virtual for any subclass
         // so any subclass inherit from here does not need to look
         // up this funtion in the vtable
        string GetClassName() const override final{return "SubClass";}
    private:
        int subclass_data_;
};

void PrintClassName(const BaseClass& base_class) {
    cout << base_class.GetClassName()<< '\n';
}

int main(){
    BaseClass base_class;
    SubClass sub_class;

    PrintClassName(base_class);
    PrintClassName(sub_class);
}

// --------------------------------------------------------------------------------------
// Abstract Base Class
// itself is not a class can not be constructed, does not it to be able to 
// instantiated into objects just needs to default data or behavior as frame to start with 
// if a class has one pure virtual function then the class is abc and can not be constructed

// virtual vs pure virtual
// Virtual functions are good for when you have a default implementation that
// subclasses may want to overwrite
// pure virtual functions specifies a function that subclass all must override in order 
// for the class not to be abc , if there is pure virtual function left not implemented
// then the class is also a abc for future subclasses to implement 
class Shape {
    // Your derived class "Circle" may forget to write this.
    virtual void draw(Canvas&) {}
    // Fails at link time because there's no definition.
    virtual void draw(Canvas&);
    // Pure virtual function.
    virtual void draw(Canvas&) = 0;
};

// --------------------------------------------------------------------------------------
// Destructing polymorphic object
// When you have a virtual destructor, the move constructor and assignment
// are not synthesized

/*  By now it should also be clear why it is always a good idea to make destructors 
 *  of base classes virtual. Since derived classes are often handled via base class references,
 *  declaring a non-virtual destructor will be dispatched statically, 
 *  obfuscating the destructor of the derived class
 */

// --------------------------------------------------------------------------------------
// Static and dynamic types
// Due to object slicing, an object that is neither reference or pointer
// always has the same static and dynamic type
// Static binding: Decide which function to call at compile time (based on static type)
// Dynamic binding: Decide which function to call at runtime (based on dynamic type)

class Base2 {
public:
  // copy ,move , move assignment will be deleted when destructor defined
  Base2() =default;
  Base2(int num): num2_{num}{};

  Base2(const Base2&) = default; // copy constructor
  Base2(Base2&&) = default; // move constructor
  Base2& operator=(Base2&&) = default; // move assignment

  // -----------------------
  virtual void GetClassName() const{cout << "Base Class" << endl;}
  void SomeFunc(){cout << "func in base" << endl;}
  // -----------------------

  virtual ~Base2(){
    //std::cout << "Destroying base" << std::endl;
  }

  int num2_ = 0;
};


class Derived2 : public Base2 {
public:
  // need to manually call base constructor
  // otherwise the base default constructor is called
  Derived2(int num,int number):Base2(num) { // constructor 
    some_resource_ = new int(number);}
  Derived2(const Derived2& d):Base2(d){ // copy constructor
    some_resource_ = new int(*(d.some_resource_));}
  Derived2(Derived2&& d): // move constructor
    Base2(std::move(d)), some_resource_{std::move(d.some_resource_)}{};// move constructor

  // -----------------------
  void GetBase() const {cout << num2_ << endl;} 
  void GetD() const {cout << *some_resource_ << endl;}
  void GetClassName() const override{cout << "Derived Class" << endl;}
  
  // nonvirtuals can be hidden by the function with the same name in the subclass
  // since it is not a virtual function not in the vtale and function in this class 
  // will get called
  void SomeFunc(){cout << "func in derived" << endl;}
  // -----------------------

  // not overriding the base destructor since base destructor is not virtual
  ~Derived2() override{
    //std::cout << "Destroying derived" << std::endl;
    delete some_resource_;
  }

private:
  int* some_resource_;
};

// since parameter accept a reference, so when a virtual function
// gets called, the type will call its dynamic type virtual function
void PrintClassName(const Base2& base_class) {
    base_class.GetClassName();
}

// -----------------------
int main() {
    Base2* p = new Derived2(10,5);
    // only the base class destructor will be called
    delete p;

    Derived2 d(11,99);
    Derived2 d2(22,100);

    Derived2 d3(d2);
    d3.GetBase();
    
    // compiler only knows that a base object is expeted
    // so it only knows the base part of the object
    Base2 b(d); // still base
    const Base2& b2(d); //same as const Base2& b2 = d dynamic type is derived class  

    // since b2 dynamic type is derived , we can down cast its 
    // static type to the derived type to let the compiler know that
    // it is a derived class
    const Derived2& dd{static_cast<const Derived2&>(b2)};
    dd.GetBase();
    dd.GetD();
 
    const Derived2& d4(d3); // okay
    
    // since expects a reference to the base
    // when a virtual function called , its dynamic type is used
    PrintClassName(b2); // wil call derived class
    PrintClassName(b);
}

// --------------------------------------------------------------------------------------
// up and down casting
// up casting from a derived class to a base class is called up-casting
// upcasting is always safe since derived class contains all information of a base class
// it is just the subclass will get sliced into the base class

Dog dog;
Cat cat;
Animal& animal_dog{dog};
Animal& animal_cat{cat};
// Attempt to down-cast with references.
// Neither of these compile.
// Why not?
Dog& dog_ref{animal_dog}; // since animal reference is not a dog reference
Dog& dog_ref{animal_cat}; // compiler does not allow that unless explicity downcasting


// Down cast a baseclass into a subclass
// is not always safe , unless you definetly know that 
// If you know it is, you can use static_cast, static_cast will not throw exception if
// it is not correct, which would be undefined behavior
// Otherwise, you can use dynamic_cast which will get exception if type does not match
// since the dynamic type can be known at run time, and it can then be checked
Dog dog;
Cat cat;
Animal& animal_dog{dog};
Animal& animal_cat{cat};
// Attempt to down-cast with references.
Dog& dog_ref{static_cast<Dog&>(animal_dog)};
Dog& dog_ref{dynamic_cast<Dog&>(animal_dog)};
// Undefined behaviour (incorrect static cast).
Dog& dog_ref{static_cast<Dog&>(animal_cat)};
// Throws exception
Dog& dog_ref{dynamic_cast<Dog&>(animal_cat)};

// Attempt to down-cast with pointers.
Dog* dog_ref{static_cast<Dog*>(animal_dog)};
Dog* dog_ref{dynamic_cast<Dog*>(animal_dog)};
// Undefined behaviour (incorrect static cast).
Dog* dog_ref{static_cast<Dog*>(animal_cat)};
// returns null pointer
Dog* dog_ref{dynamic_cast<Dog*>(animal_cat)};

// --------------------------------------------------------------------------------------
https://quuxplusone.github.io/blog/2019/01/20/covariance-and-contravariance/
// Covariants
// Every possible return type for the derived must be a valid return type for the base
// base return type should contains subclass return type
class Base {
  // subclass implementation must return the same class or
  // subclass of what the virtual function in the base function returns
  virtual LandAnimal& GetFavoriteAnimal();
};
class Derived: public Base {
  // Fails to compile: Not all animals are land animals.
  Animal& GetFavoriteAnimal() override;
  // Compiles: All land animals are land animals.
  LandAnimal& GetFavoriteAnimal() override;
  // Compiles: All dogs are land animals.
  Dog& GetFavoriteAnimal() override;
};

// Contravariants
// Every possible parameter to the base must be a possible parameter for the derived
// derived class parameter should be able to take the base class paramater
class Base {
  virtual void UseAnimal(LandAnimal&);
};
class Derived: public Base {
  // Compiles: All land animals are valid input (animals).
  void UseAnimal(Animal&) override;
  // Compiles: All land animals are valid input (land animals).
  void UseAnimal(LandAnimal&) override;
  // Fails to compile: Not All land animals are valid input (dogs).
  void UseAnimal(Dog&) override;
};


// -------------------------------
// example why it is neccessary
class Base {
    virtual Dog& f();
    virtual void g(Animal&);
};
class Derived {
    Animal& f() override { return cat; }
    void g(Dog&) override
};

Base b;
Derived d;
Base& bref{b};
Base& dref{d};
// Based on the definition for Base, this should work, 
// but the derived class can return a cat instead. Thus, this isn't allowed.
Dog dog = dref.f();
// Based off the definition for Base, this should be allowed, 
// but clearly the derived class can only take in dogs.
dref.g(Cat{});


// -------------------------------
// Probably worth noting that C++ does not support contravariant parameter types 
// through virtual functions, since it's possible you just meant an overload, 
// though it does support covariant return types. If you try this:
struct Base {
  virtual void foo(Dog&);
};

struct Derived : Base {
  virtual void foo(Animal&) override;
};
//You'll get an error complaining that "foo is marked `override' 
//but doesn't override anything". However the following works fine:

struct Base {
  virtual Animal& foo();
};

struct Derived : Base {
  virtual Dog& foo() override;
};
// After all, C++ doesn't support overloading functions purely on return type,
// so this is unambiguous.(However, note that `std::function' does support 
// contravariant parameter types IIRC.)

// --------------------------------------------------------------------------------------
// Default arguments are determined at compile time for efficiency's sake
// Hence, default arguments will use the static type of the function
// Avoid default arguments when overriding virtual functions
class Base {
    virtual void PrintNum(int i = 1) {
        std::cout << "Base " << i << '\n';
    }
};

class Derived: public Base {
    void PrintNum(int i = 2) override {
        std::cout << "Derived " << i << '\n';
    }
};

int main() {
    Derived derived;
    // at compile time static type is base default value 
    // will get init to the one in the base class
    Base& base{derived}; 
    derived.PrintNum(); // Prints "Derived 2"
    // since dynamic type is derived , drived virtual function will get called
    // but the default parameter has been init at compile time using the 
    // one in the base class
    base->PrintNum(); // Prints "Derived 1"
}

// --------------------------------------------------------------------------------------
// Construction of the derived class
// Base classes are always constructed before the derived class is constructed
// The base class is never dependent on the derived class
// The derived may be dependent on the base

class Animal {...}
class LandAnimal: public Animal {...}
class Dog: public LandAnimals {...}
Dog d;
// Dog() calls LandAnimal()
// LandAnimal() calls Animal()
// Animal members constructed using initialiser list
// Animal constructor body runs
// LandAnimal members constructed using initialiser list
// LandAnimal constructor body runs
// Dog members constructed using initialiser list
// Dog constructor body runs


// virtual in constructors
// If a class is not fully constructed, cannot perform dynamic binding
class Animal {...};
class LandAnimal: public Animal {
    LandAnimal() {
        // at this time dog object is not fully constructed
        // so dynamic bonding is not hapening at this point
        // since Run() in dog might need to depend on members in dogs
        // the compiler choose not to bind
        Run(); // virtual function in constructor will not get bind
    }
    virtual void Run() {
        std::cout << "Land animal running\n";
    }
};

class Dog: public LandAnimals {
    void Run() override {
        std::cout << "Dog running\n";
    }
};
// When the LandAnimal constructor is being called,
// the Dog part of the object has not been created yet.
// C++ chooses to not allow dynamic binding in constructors
// because Dog::Run() might depend upon Dog's members.
Dog d;


// Destruction of derived classes
// Easy to remember order: Always opposite to construction order
class Animal {...}
class LandAnimal: public Animal {...}
class Dog: public LandAnimals {...}
Dog d;
// ~Dog() destructor body runs
// Dog members destructed in reverse order of declaration
// ~LandAnimal() destructor body runs
// LandAnimal members destructed in reverse order of declaration
// ~Animal() destructor body runs
// Animal members destructed in reverse order of declaration.

// Virtuals in destructors
// If a class is partially destructed, cannot perform dynamic binding
// Unrelated to the destructor itself being virtual
class Animal {...};
class LandAnimal: public Animal {
    virtual ~LandAnimal() {
        Run(); // dog destroyed vritual function override by dog not bind
    }
    virtual void Run() {
        std::cout << "Land animal running\n";
    }
};
class Dog: public LandAnimals {
     void Run() override {
         std::cout << "Dog running\n";
     }
};
// When the LandAnimal constructor is being called,
// the Dog part of the object has already been destroyed.
// C++ chooses to not allow dynamic binding in destructors
// because Dog::Run() might depend upon Dog's members.
Dog d;




//=================================================================
// initialisation
https://www.learncpp.com/cpp-tutorial/8-5a-constructor-member-initializer-lists/
https://www.youtube.com/watch?v=bNFaZBdGink

for each data member in declaration order
 if it has an in-class initialiser
 Initialise it using the in-class initialiser
 else if it is of a built-in type (numeric, pointer, bool, char, etc.)
 do nothing (leave it as whatever was in memory before)
 else
 Initialise it using its default constructor

// -------------------------------------------------------------------
// List Init
/* member wise init , according to the order that member is declared.
 */
 // if arg the same number but constructor would take the initializer list
 // the initializer list constructor would be preferred
vector<int> v{10,0}; // init with 10 and 0 insteand of 10 zeros, since init list is preferred

// if without init list constructor, if the parameters in the init list match
// one of the constructor then that constructor will be called



// -------------------------------------------------------------------
// memeber initialization list
// The member initializer list is inserted after the constructor parameters.
// It begins with a colon (:), and then lists each variable to initialize along
// with the value for that variable separated by a comma.

// -------------------------------------------------------------------
// Default init
/*defined variable witout initialization
 * Built in type that are defined outside any function body will init to zero
 * Built in type that are defined inside the function are uninitialised
 * the value of the uninitialised variable is undefined 
 * class member of built in type will not be initialised unless explicitly
 * value of the uninitialised built in type is undefined
 */
// default init of a{} will init each member of a with empty iniitialisation list
// same as a {{} , {}, {} ,...} , even there is built in type, this init will int
// the built in type to its default value since int i{}  will init to 0
MyClass a{}; // default init each member of the class
MyClass a; // call default constructor  

int b; // undefined value
int b{}; // a is 0


class A {
public:
 int a_; // memeory untouched
};

class B {
public:
 B(int b): b_{b} {}
 int b_;
};

class C {
public:
 int i{0}; // in-class initialiser
 int j; // Untouched memory
 A a; // since primitive type member in A , so no constructor is called 
 // This stops default constructor
 // from being synthesized.
 B b;
};




// -------------------------------------------------------------------
// Carr example
class Car {
    public:
        // constructor
        Car(string name, int seats = 4):name_{name},seats_{seats}{++n_object_;};
        Car():Car{"unknown",4}{}
        Car(const Car& rhs): name_{rhs.name_}, seats_{rhs.seats_}
        { // copy constructor
            ++n_object_;
        }

        Car(Car&& rhs) noexcept
            : name_{std::move(rhs.name_)}, seats_{std::move(rhs.seats_)}
        { // move constructor
            ++n_object_;
        }

        // operator
        Car& operator=(const Car& rhs){ // copy assignment
            Car temp(rhs);
            std::swap(*this, temp); // need move assignment to swap
            return *this;
        }

        Car& operator=(Car&& rhs) noexcept { // move assignment
            name_ = std::move(rhs.name_);
            seats_ = std::move(rhs.seats_);
            return *this;
        }

        // method
        int GetSeats() const {return seats_;}
        static int ObjectCount() {return n_object_;}

        // destructor
        ~Car() noexcept {--n_object_;}


    private:
        string name_;
        int seats_ = 0;

        static int n_object_;
};

int Car::n_object_ = 0;

int main() {
    Car c("Nisan",9);
    cout << c.GetSeats() << endl;

    Car c2;
    cout << Car::ObjectCount() << endl;

    Car c2{"ford",8};
    Car c1;
    c1 = std::move(c2);
    cout << c1.GetSeats() << endl;
    cout << c2.GetSeats() << endl;


}





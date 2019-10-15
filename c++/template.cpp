

#include <iostream>
using namespace std;
//=================================================================
//Template
// Function Template
// Type and non type paramater
// T is type paramater , size is a non type paramater which 
// we know the type but not the value
template <typename T, size_t size>
T findmin(const std::array<T, size> a) {
    T min = a[0];
    for (size_t i = 1; i < size; ++i) {
        if (a[i] < min) min = a[i];
    }
    return min;
}

// template function argument deduction
// parameter of T x[D] is equivalent to T x[]
template <typename T, size_t size>
T findmin(const T (&a)[size]){
    T min = a [0];
    for(size_t i = 1;i< size;++i){
        if(a[i] < min) min = a[i];
    }
    return min;
}


// --------------------------------------------------------------------
// class template
#include <iostream>
#include <vector>

template <typename T>
class Stack {
    public:
        friend std::ostream& operator<<(std::ostream& os, const Stack& s) {
            for (const auto& i : s.stack_) os << i << " ";
            return os;
        }
        void push(const T&);
        void pop();
        T& top();
        const T& top() const;

    private:
        vector<T> stack_;
};
// --------------------------
// need to specify for template paramater list if
// memeber function defined outside the class template
template <typename T>
void Stack<T>::push(const T &item) { // need to qualify with MyClass<T>::
    stack_.push_back(item);
}
template <typename T>
void Stack<T>::pop() {
    stack_.pop_back();
}
template <typename T>
T& Stack<T>::top() {
    return stack_.back();
}
template <typename T>
const T& Stack<T>::top() const {
    return stack_.back();
}
// --------------------------------------------------------------------
// tute excercise 5
#include <stdexcept>

template <typename T, int size_max_>
class Queue {
    public:
        Queue() :
            size_curr_{0}, queue_{std::make_unique<T[]>(size_max_)} {}
        Queue(const Queue&); // copy constructor
        void enque(const T&);
        T deque();
        int size() const;

        friend ostream& operator<<(ostream& os, const Queue& rhs){
            for(int i =0  ; i < rhs.size_curr_; ++i) {
                os << rhs.queue_[i]<< " ";
            }
            return os;
        }

    private:
        int size_curr_;
        std::unique_ptr<T[]> queue_;
};

template <typename T, int size_max_>
Queue<T,size_max_>::Queue(const Queue& temp){
     size_curr_ = temp.size_curr_;
     size_max_ = temp.size_max_;

     // rhs is a rvalue so move construct the unique_ptr
     queue_ = make_unique<T[]>(size_max_);
     for(int i = 0;i < size_max_ ; ++i){
         queue_[i] = temp.queue_[i];
     }
 }

template <typename T, int size_max_>
void Queue<T,size_max_>::enque(const T& s){
    if(size_curr_ == size_max_){
        throw std::overflow_error{"Queue is full"};
    }
    queue_[size_curr_++] = s;
}

template <typename T, int size_max_>
T Queue<T,size_max_>::deque(){
    if(size_curr_ == 0) {
      	throw std::logic_error{"No items in queue"};
    }
    return queue_[--size_curr_];
}

template <typename T, int size_max_>
int Queue<T,size_max_>::size() const {
    return size_curr_;
}
// ----------------------------
int main() {
    Queue<string,3> q5;
    q5.enque("good");
    q5.enque("right");
    q5.enque("for");
    cout << q5 << endl;

    Queue<int,2> q2;
    q2.enque(1);
    q2.enque(2);
    cout << q2 << endl;

}

// --------------------------------------------------------------------
// inclusing compilation model
// we need to put declaration and e definition of template together in the same file
/* since template defnition by itself can not compile at compile time , since it is not an
 * actual function nor a class, and it can not be instatiated at linking time, so
 * the definition of the template needs to be known at compile time so that during compilation
 * it knoww how to instantiated itself.
 * there could be multiple instantiation since every file using the header file would instantiate
 * the template ,where there could be duplicate instatiation
 * up to the linker to ensure there is only one instatiation
 */

// Lazy instantiation: Only members functions that are called are instantiated
// Each stack instantiation has one unique instantiation of the friend
// Each template instantiation has it's own set of static members
// --------------------------------------------------------------------
// default arguments to template types ,default argment itself is a type
template <typename T, typename Cont = std::vector<T>>
class Stack_temp {...};


// --------------------------------------------------------------------
// Specialisation
// partial specialisation: define template in another generic form like T*
// explicit specialisation: define template for a specific type like string
// Function can not be partially specialised and no need to full specialise function
// since it is better just to do function overload


// The following a fairly standard example, for illustration purposes only. 
// Specialisation is designed to refine a generic implementation for a specific type,
// not to change the semantic.
template <typename T>
class Stack<T*> {
    public:
        void push(T* t) { stack_.push_back(t); }
        T* top() { return stack_.back(); }
        void pop() { stack_.pop_back(); }
        int size() const { return stack_.size(); };
        int sum() {
            return accumulate(stack_.begin(),
            stack_.end(), 0, [] (int a, T *b) { return a + *b; });
        }
    private:
        std::vector<T*> stack_;
};

// Explicit specialisation should only be done on classes.
template <typename T>
struct VoidType {
    static const bool val = false;
};

template<>
struct VoidType<void> {
    static const bool val = true;
};

int main() {
    std::cout << VoidType<int>::val << "\n";
    std::cout << VoidType<void>::val << "\n";
}

// --------------------------------------------------------------------
// Type Traits: Class (or clas template) that characterises a type

#include <array>
#include <limits>

// Traits allow generic template functions to be parameterised
template <typename T, auto size>
T findMax(const std::array<T, size>& arr) {
    T largest = std::numeric_limits<T>::min();
    for (const auto& i : arr) {
        if (i > largest) largest = i;
    }
    return largest;
}

int main() {
    std::array<int, 3> i{ -1, -2, -3 };
    std::cout << findMax(i) << "\n";
    std::array<double, 3> j{ 1.0, 1.1, 1.2 };
    std::cout << findMax(j) << "\n";
}

// STL type trait examples
#include <type_traits>

template <typename T>
void testIfNumberType(T i) {
    if (std::is_integral<T>::value || std::is_floating_point<T>::value) {
        std::cout << i << " is a number" << "\n";
    } else {
        std::cout << i << " is not a number" << "\n";
    }
}

int main() {
    int i = 6;
    long l = 7;
    double d = 3.14;
    testIfNumberType(i);
    testIfNumberType(l);
    testIfNumberType(d);
    testIfNumberType(123);
    testIfNumberType("Hello");
    std::string s = "World";
    testIfNumberType(s);
}

// --------------------------------------------------------------------
// variadic template
#include <typeinfo>

// base case template to print a particular type
template <typename T>
void print(const T& msg) {
    std::cout << msg << " ";
}

// recursive definition print head and the rest
template <typename A, typename... B>
void print(A head, B... tail) {
    print(head);
    print(tail...);
}

int main() {
    print(1, 2.0f);
    std::cout << std::endl;
    print(1, 2.0f, "Hello");
    std::cout << std::endl;
}

// -----------------
// instatination
void print(const char* const& c) {
    std::cout << c << " ";
}
void print(const float& b) {
    std::cout << b << " ";
}
void print(float b, const char* c) {
    print(b);
    print(c);
}
void print(const int& a) {
    std::cout << a << " ";
}
void print(int a, float b, const char* c) {
    print(a);
    print(b, c);
}
// ----------------------------------------------------------------------
// member template

template <typename T>
class Stack {
    public:
        explicit Stack() {}
        template <typename T2>
        Stack(Stack<T2>&);
        void push(T t) { stack_.push_back(t); }
        T pop();
        bool empty() const { return stack_.empty(); }
    private:
        std::vector<T> stack_;
};

template <typename T>
T Stack<T>::pop() {
    T t = stack_.back();
    stack_.pop_back();
    return t;
}

// the order will the be same as the template parameter that appers
// in the class
template <typename T>
template <typename T2>
Stack<T>::Stack(Stack<T2>& s) {
    while (!s.empty()) {
        stack_.push_back(static_cast<T>(s.pop()));
    }
}
//-----------------
int main() {
    Stack<int> is1;
    is1.push(2);
    is1.push(3);
    // Stack<int> is2{is1}; // this works
    Stack<double> ds1{is1}; // both works at a time 
}
// ----------------------------------------------------------------------
// template template paramater
// template <typename T, template <typename> Cont>
// class stack {}
#include <vector>

// the template paramater itself is a template 
// just need to mention the template class with its
// template paramater list
// the second template parametre itself is a template which
//  is a vector template that itself is a class and its template 
//  paramater takes two classes
template <typename T, template <class,class> class Cont>
class Stack {
    public:
        void push(T&);
        void pop();
        T& top();
    private:
        Cont<T,std::allocator<T>> stack_;
};

// -------------------
int main(void) {
    Stack<int, std::vector> s1; // instead of Stack<int, std::vector<int>>
    s1.push(1);
    s1.push(2);
    std::cout << "s1: " << s1 << "\n";
} 
// ----------------------------------------------------------------------
// Template Argument Deduction is the process of determining the types 
// (of type parameters) and the values of nontype parameters from the types of
// function argument

,std::allocator<T>// implicit deduction
// three types of convertion

// array to pointer
template <typename T>
f(T* array) {}

int a[] = { 1, 2 };
f(a);

// const qualification
template <typename T>
f(const T item) {}
int a = 5;
f(5); // int => const int;

// conversion to base class
// from derived class
template <typename T>
class Base {
    public:
        Base():num1_{}{}
        Base(T num):num1_{num}{}

        T num1_;
};

template <typename T, typename S>
class Derived: public Base<T> {
    public:
        Derived(S num):Base<T>::Base(), num2_{num}{}

        S num2_;
};

template <typename T>
void foo(Base<T>& b){ // convert derived class to the base class
    cout << b.num1_ << endl;
}
// -------------------------
int main {
    Base<int> b(99);
    Derived<int, double> d(2.0);
    foo(d); // will deduce as base class reference
}



// ------------------------
// explicit deduction
// If we need more control over the normal deduction process, 
// we can explicitly specify the types being passed in
template <typename T>
T min(T a, T b) {
    return a < b ? a : b;
}

int main() {
    int i; double d;
    min(i, static_cast<int>(d)); // int min(int, int)
    min<int>(i, d); // int min(int, int)
    min(static_cast<double>(i), d); // double min(double, double)
    min<double>(i, d); // double min(double, double)
}


//=================================================================
// advanced type
// decltype: like typeof in c
/* 
Rule 1:
If expression e is any of:
    variable in local scope
    variable in namespace scope
    static member variable
    function parameters
then result is variable/parameters type T
Rule 2: if e is an lvalue, result is T&
Rule 3: if e is an xvalue, result is T&&
Rule 4: if e is a prvalue, result is T
 */

// Trailing Return Types
// we know that the return type should be of decltype(*beg), but beg is
// not declared until in the function paramater
// so we use auto as place holder, then using -> ReturnType to
// incidate the return type
template <typename It>
auto find(It beg, It end, int index) -> decltype(*beg) {
    for (auto it = beg, int i = 0; beg != end; ++it; ++i) {
        if (i == index) {
            return *it;
        }
    }
    return end;
}
// -----------------------------------------------------------------------------
// type transformation
#include <type_traits>

template<typename T1, typename T2>
void print_is_same() {
    std::cout << std::is_same<T1, T2>() << std::endl;
}

int main() {
    std::cout << std::boolalpha;
    print_is_same<int, int>();
    // true
    print_is_same<int, int &>(); // false
    print_is_same<int, int &&>(); // false
    print_is_same<int, std::remove_reference<int>::type>();
    // true
    print_is_same<int, std::remove_reference<int &>::type>(); // true
    print_is_same<int, std::remove_reference<int &&>::type>(); // true
}

// -----------------------------
int main() {
    typedef std::add_rvalue_reference<int>::type A;
    typedef std::add_rvalue_reference<int&>::type B;
    typedef std::add_rvalue_reference<int&&>::type C;
    typedef std::add_rvalue_reference<int*>::type D;

    std::cout << std::boolalpha
    std::cout << "typedefs of int&&:" << "\n";
    std::cout << "A: " <<  std::is_same<int&&, A>() << "\n"; // true
    std::cout << "B: " << std::is_same<int&&, B>() << "\n"; // false
    std::cout << "C: " << std::is_same<int&&, C>() << "\n"; // true
    std::cout << "D: " << std::is_same<int&&, D>() << "\n"; // false

}

// -----------------------------
// Tute exmaple 
namespace traits{
template <typename T>
struct is_a_pointer{
    static constexpr const bool value  = 
        !std::is_same<typename std::remove_pointer<T>::type,T>::value;
};

/* Alternative template partial specialisation solution
template <typename T>
struct is_a_pointer{
    static constexpr const bool value = false;
};

template <typename T>
struct is_a_pointer<T*>{
    static constexpr const bool value = true;
};
*/
template <typename T>
struct is_real_number{
    static constexpr const bool value =
        std::is_floating_point<T>::value || std::is_integral<T>::value;
};
} // end of namespace traits

template <typename T>
void printPointer(T t) {
    if constexpr (traits::is_a_pointer<T>::value) {
    	std::cout << *t << "\n";
    } else {
    	std::cout << t << "\n";
    }
}

template <typename T>
void IsReal(T t){
    if constexpr (traits::is_real_number<T>::value) {
        std::cout << "Is real number" << "\n";
    }
}

// -----------------
int main() {
    int* p = new int(66);
    int i = 77;
    printPointer(p);
    printPointer(i);
}

// -----------------------------------------------------------------------------
// static
https://www.studytonight.com/cpp/static-keyword.php
// static var inside function
void counter(){
    static int count=0;
    cout << count++;
}

int main(){
    // value maintained between function calls
    counter(); // 0
    counter(); // 1
}

// -----------------------------------------------------------------------------
// Binding 
// template T&& binds to all
// const T& binds to all
// T& binds only to lvalue
// T&& only binds to rvlaue
// const T&& binds rvalue and const value

// -----------------------------------------------------------------------------
// how std::move is defined
// template T&& binds to all types and T capture the type that passed in
// due to the reference collapsing the we remove the reference add rvalue reference
// to the type
#include <utility>

template <typename T>
typename remove_reference<T>::type&& move(T&& t){
    // return add_rvalue_reference<<typename remove_reference<T>::type>>::type;
    return static_cast<typename remove_reference<T>::type&&>(t);
}


// std::forward
// preserve the tpes of the original argument that passed in through the function
// std::forward<T> returns T&& not lime std::move which would cast it to a T&& ,
// forward will add && to the type that passed in as to preserve the original type
template <typename Type>
intermediary(Type&& arg){
    // Type will capture the paramater type that passed in
    // forward will return Type with rvalue reference added 
    // Type&& , due to reference collapsing, will return the 
    // original Type that passed in
    finalFnc(std::forward<Type>(arg));
}

// ---------------------------
void f(int&& j, int& i){
    cout << j << " " << i << endl;
}
template <typename F, typename T1, typename T2>
void flip(F f, T1&& t1, T2&& t2){
   /*when pass in flip2(f,i,42)  
    * T1 will be of int& , so int& && t1, t1 collapse into int& t1
    * T2 will be of int&&, so int&& && t2, t2 collapse into int&& t2 
    * forward t1 and t2 will preserve the type it passed in through flip
    */
    f(std::forward<T2>(t2),std::forward<T1>(t1)); 
}

int i = 99;
flip(f,i,42);

// ---------------------------
// possible implementation
template<typename T>
T&& forward(typename remove_reference<T>::type& a) noexcept {
  return static_cast<T&&>(a);
}

// easier explaination
// This is approximately std::forward.
// Returns reference to value for lvalues
// Returns std::move(value) for rvalues
template <typename T>
T& forward(T& value) {
    return static_cast<T&>(value);
}

template <typename T>
T&& forward(T&& value) {
    return static_cast<T&&>(value);
}

// Often you need to call a function you know nothing about
// It may have any amount of parameters
// Each parameter may be a different unknown type
// Each parameter may be an lvalue or rvalue
template <typename... Args>
auto wrapper(Args&&... args) {
    // Note that the ... is outside the forward call, and not right next to args.
    // This is because we want to call
    // fn(forward(arg1), forward(arg2), ...)
    // and not
    // fn(forward(arg1, arg2, ...)
    return fn(std::forward<Args>(args)...);
}





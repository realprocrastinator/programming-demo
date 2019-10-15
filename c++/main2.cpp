#include <iostream>
#include <memory>
#include <algorithm>
#include <numeric>
#include <vector>
#include <set>
#include <utility>
#include <map>
#include <list>


using namespace std;


void inner(int&& value) {
 ++value;
 std::cout << value << '\n';
}
void outer(int&& value) {
 //inner(value); // This fails? Why?
 std::cout << value << '\n';
}

void f(int i) {
    cout << " functon called " << i <<  endl;
}

// ---------------------------------------------------------------
class Erik {
    public:
        Erik()= default;
        Erik(int i):num_(i){};
        int get() const {return num_;};
    private:
        int num_;
        //friend bool operator<(const erik& rhs, const erik& lhs){ return rhs.num_ < lhs.num_; };
};

class Comp {
    public:
        bool operator()(const Erik& rhs,const Erik& lhs) {
            return rhs.get() < lhs.get();
        }
};

bool CompFunc(const Erik& rhs,const Erik& lhs){
    return rhs.get() < lhs.get();
}

std::ostream& operator<<(std::ostream& ostr,  const set<Erik,decltype(&CompFunc)> set2){
    for (auto &i : set2)
        ostr << " " << i.get();
    return ostr;
}

/*
std::ostream& operator<<(std::ostream& ostr,  set<Erik,Comp>& set2){
    for (auto &i : set2)
        ostr << " " << i.get();
    return ostr;
}
*/
// --------------------------------------------------------------
#include <fstream>
#include <iterator>
#include <sstream>

// given a string and a string delimitor
// parse accodint to the delim and save into a vector
vector<string> Split(string s, string& delim){
    vector<string> result;
    size_t pos = 0;

    while((pos = s.find(delim)) != string::npos) {
        auto token = s.substr(0,pos);
        result.push_back(token);
        s = s.substr(pos + delim.size());
    }
    result.push_back(s);

    return result;
}

// --------------------------------------------------------------
class Point {
    public:
        // constructor
        Point(int x, int y):x_{x}, y_{y}{};
        
        // method
        int GetX(){return x_;}

        // operator
        Point& operator+=(const Point&);
        Point& operator++(); // pre increment
        Point operator++(int);// ppost increment
        operator vector<int>(){ // for type converstion
            vector<int> temp;
            temp.push_back(x_);
            temp.push_back(y_);
            return temp;
        }

        friend ostream& operator<<(ostream& os, const Point& p){
            os << p.x_ << "," << p.y_;
            return os;
        }
        
    private:
        int x_ = 0;
        int y_ = 0;
};

Point& Point::operator+=(const Point& lhs){
    this->x_ += lhs.x_;
    this->y_ += lhs.y_;
    return *this;
}

Point& Point::operator++(){
    ++(this->x_);
    ++(this->y_);
    return *this;
}

Point Point::operator++(int){
    auto temp = *this;
    ++(this->x_);
    ++(this->y_);
    return temp;
}

#include <iostream>
class StringPtr {
    public:
        StringPtr(std::string *p) : ptr{p} { }
        ~StringPtr() { delete ptr; }

        std::string* operator->() { return ptr; }
        std::string& operator*() { return *ptr; }

    private:
        std::string *ptr;
};

// --------------------------------------------------------------
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



// --------------------------------------------------------------

class Book {
    public:
        // constructor
        Book(string name, string author, int isbn, double price):
            name_{name},author_{author},isbn_{isbn}, price_{price}{}
        
        // operator
        friend bool operator==(const Book& rhs, const Book& lhs){ 
            return rhs.name_ == lhs.name_ && rhs.author_ == lhs.author_
                && rhs.isbn_ == lhs.isbn_ && rhs.price_ == rhs.price_;
        }

        friend bool operator!=(const Book& rhs, const Book& lhs){
            return !(rhs == lhs);
        }

        friend ostream& operator<<(ostream& os ,const Book& rhs){
            os << rhs.name_ << " " << rhs.author_ << " "
                << rhs.isbn_ << " " << rhs.price_;
            return os;
        }

        friend bool operator<(const Book& rhs, const Book& lhs){
            return rhs.isbn_ < lhs.isbn_;
        }

        operator std::string () const {
            ostringstream oss;
            oss << name_ << ",";
            oss << author_ << ",";
            return oss.str();
        }

        // method
        int GetIsbn() const { return isbn_; }
        double GetPrice() const  { return price_; }
        
    private:
        std::string name_;
        std::string author_;
        int isbn_;
        double price_;
};

// Helper function to print vectors of books.
void print(const std::string& title, const std::vector<Book>& books) {
  std::cout << title << '\n';
  for (const auto& b: books) {
    std::cout << "\t";
    std::cout << b << '\n';
  }
  std::cout << '\n';
}

// --------------------------------------------------------------
class Giraffe {
    public:
        Giraffe() { std::cout << "Giraffe constructed" << '\n'; }
        Giraffe(const Giraffe &g) { std::cout << "Giraffe copy-constructed" << '\n'; }
        ~Giraffe() { std::cout << "Giraffe destructed" << '\n'; }
};

void zebra() {
    throw Giraffe{};
}

void llama() {
    try {
        zebra();
    } catch (Giraffe g) {
        std::cout << "caught in llama; rethrow" << '\n';
        throw;
    }
}

// --------------------------------------------------------------
/*
class Stack {
    public:
        // Why won't this work if we uncomment the line below?
        Stack(int i) { stack_.push_back(i); }
        void push(int&);
        void pop();
        int& top();
        const int& top() const;
    private:
        std::vector<int> stack_;
};
*/

// --------------------------------------------------------------
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
    T temp = queue_[0]; // get the top item
    for(int i = 0;i < size_curr_;++i){
        queue_[i] = queue_[i+1];
    }
    --size_curr_;
    return temp;
}

template <typename T, int size_max_>
int Queue<T,size_max_>::size() const {
    return size_curr_;
}

// --------------------------------------------------------------
/*
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
*/

// --------------------------------------------------------------
template <typename T>
struct Ask {
    static const bool val = false; 
};

template<>
struct Ask<void> {
    static const bool val = true;
};



// --------------------------------------------------------------
template <typename T>
class Stack {
    public:
        explicit Stack() {}
        template <typename T2>
        Stack(Stack<T2>&);

        void push(T t) { stack_.push_back(t); }
        T pop();
        bool empty() const { return stack_.empty(); }
        vector<T>& Get(){return stack_;}

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
// --------------------------------------------------------------
#include <array>
#include <limits>


template <typename T, auto size>
T findMax(const std::array<T, size>& arr) {
    T largest = std::numeric_limits<T>::min();
    for (const auto& i : arr) {
        if (i > largest) largest = i;
    }
    return largest;
}

void fu(const int a){
   cout << a << endl; 
}
// --------------------------------------------------------------
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
        Derived(S num, T num2):Base<T>::Base(num2), num2_{num}{}

        S num2_;
};

template <typename T>
void foo(Base<T>& b){
    cout << b.num1_ << endl;
}


// --------------------------------------------------------------
class BaseClass {
    public:
        int GetMember() { return member_;}
        virtual string GetClassName() const{ return "BaseClass";}
    private:
        int member_;
};

class SubClass: public BaseClass {
    public:
         string GetClassName() const override{return "SubClass";}
    private:
        int subclass_data_;
};


void PrintClassName(const BaseClass& base_class) {
    cout << base_class.GetClassName()<< '\n';
}


// --------------------------------------------------------------
class Base2 {
public:
  // copy ,move , move assignment will be deleted when destructor defined
  Base2() =default;
  Base2(int num): num2_{num}{};

  Base2(const Base2&) = default; // copy constructor
  Base2(Base2&&) = default; // move constructor
  Base2& operator=(Base2&&) = default; // move assignment

  virtual void GetClassName() const{cout << "Base Class" << endl;}
  void SomeFunc(){cout << "func in base" << endl;}

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

  // --------------------------------------------------------------
  void GetBase() const {cout << num2_ << endl;} 
  int& GetBase() {return num2_;} 
  void GetD() const {cout << *some_resource_ << endl;}
  void GetClassName() const override{cout << "Derived Class" << endl;}
  void SomeFunc(){cout << "func in derived" << endl;}
  // --------------------------------------------------------------

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
// --------------------------------------------------------------

struct Base3 {
  virtual Base2& foo();
};

struct Derived3 : Base3 {
  virtual Derived2& foo() override;
};

#include <type_traits>
// --------------------------------------------------------------
void Type(const int&& a){
    cout << a << endl;
}

auto G(){
    return 888;
}

auto F(int d = 77){
    return d;
}
// --------------------------------------------------------------
namespace traits{
    template <typename T>
    struct is_a_pointer{
        static constexpr const bool value  = 
            !std::is_same<typename std::remove_pointer<T>::type,T>::value;
    };

    template <typename T>
    struct is_real_number{
        static constexpr const bool value =
            std::is_floating_point<T>::value || std::is_integral<T>::value;
    };
}

template <typename T>
void printPointer(T t) {
    if constexpr (traits::is_a_pointer<T>::value) {
    	std::cout << *t << "\n";
    } else {
    	std::cout << t << "\n";
    }
}

// --------------------------------------------------------------
void counter(){
    static int count=0;
    cout << count++;
}
// --------------------------------------------------------------

template <typename T>
void IsReal(T t){
    if constexpr (traits::is_real_number<T>::value) {
        std::cout << "Is real number" << "\n";
    }
}

// --------------------------------------------------------------
/*
template <typename T>
struct Forward{
    auto operator()(T param){
        return static_cast<typename std::add_rvalue_reference<T>::type>(param);
    } 
};
*/
template <typename T>
T&& Forward(T& param){
    return static_cast<typename std::add_rvalue_reference<T>::type>(param);
}

void fo(int&& j, int& i){
    cout << j << " " << i << endl;
}
template <typename F, typename T1, typename T2>
void flip(F fo, T1&& t1, T2&& t2){
   /*when pass in flip2(f,i,42)  
    * T1 will be of int& , so int& && t1, t1 collapse into int& t1
    * T2 will be of int&&, so int&& && t2, t2 collapse into int&& t2 
    * forward t1 and t2 will preserve the type it passed in through flip
    */
    fo(Forward<T1>(t1), Forward<T2>(t2));

    /*
    fo(static_cast<typename std::add_rvalue_reference<T1>::type>(t1), 
       static_cast<typename std::add_rvalue_reference<T2>::type>(t2));
    */

    //fo(forward<T1>(t1),std::forward<T2>(t2)); 
}


// --------------------------------------------------------------
class Base4{
    public:
        virtual void Get(){
            cout << "in base" << endl;
        }

        int base_ = 99;
};

class Derived4:public Base4{
    public:
        virtual void Get(){
            cout << " in Derived" << endl;
        }

        int dev_ =88;
};

void print(Derived4& o){
    o.Get();
}
// --------------------------------------------------------------
class Lemon {
 public:
  explicit Lemon(const int r, std::string s) :  radius_{r}, sourness_{s}{}
  friend std::ostream& operator<<(std::ostream& os, const Lemon& l) { os << l.radius_; return os; }
 private:
  int radius_;
  std::string sourness_;
};

// --------------------------------------------------------------
int findmin(int a[3]){
    auto min = a [0];
    for(int i = 1;i< 3;++i){
        if(a[i] < min) min = a[i];
    }
    a[0] = 100;
    return min;
}


template <typename T, size_t size>
T findmin2(const std::array<T, size> a) {
    T min = a[0];
    for (size_t i = 1; i < size; ++i) {
        if (a[i] < min) min = a[i];
    }
    return min;
}
// --------------------------------------------------------------
class B5 {
    public:
        int pub_ = 88;
    protected:
        int p_num_ = 7;
    private:
        int num_ =99;
};

class D5: public B5 {
    void GetP(){cout << pub_<< endl;}
    void GetT(){cout << p_num_ << endl;}
    // void GetI(){cout << num_ << endl;}
};



// --------------------------------------------------------------
class Base5 {
public:
    ~Base5(){}
    virtual void PrintNum(int i = 1) {
        std::cout << "Base " << i << '\n';
    }

    void Access(const Base5 b){
        cout << "accces private of arg:" << b.num_ << endl;
    }
private:
    int num_= 999;
};

class Derived5: public Base5 {
public:
    void PrintNum(int i = 2) override {
        std::cout << "Derived " << i << '\n';
    }
};

// --------------------------------------------------------------
template <typename T, size_t size>
auto createDefaultArray() {
  return std::make_unique<T[]>(size);
}

// --------------------------------------------------------------
class Magnitude {
 public:
  Magnitude() : Magnitude(1) {}
  Magnitude(int l) : litres_{l} {}

 int getLitres() const {
    return litres_;
  }

  friend int operator*(const Magnitude& lhs, const Magnitude& rhs){
      return lhs.getLitres() * rhs.getLitres();
  }
 private:
  int litres_;
};

// --------------------------------------------------------------
template <typename T>
class EuclideanVector {
 public:
  EuclideanVector() : EuclideanVector(10) {}
  EuclideanVector(int size) : vec_{new T[size]}, size_{size} {}

  // copy constructor
  EuclideanVector(const EuclideanVector& rhs){
      vec_ = new T[rhs.size_];
      for(int i = 0; i < rhs.size_;++i){
          vec_[i] = rhs.vec_[i];
      }
  }

  // move constructor
  EuclideanVector(EuclideanVector&& rhs){
      vec_ = std::move(rhs.GetV());
      size = std::move(rhs.GetS());
  }

  // move assignment
  EuclideanVector& operator=(EuclideanVector&& rhs){
      std::swap(rhs,*this);
      return *this;
  }

  // copy assignment
  EuclideanVector& operator=(const EuclideanVector& rhs){
      EuclideanVector temp{rhs};
      std::swap(*this, temp);
      return *this;
  }

  // destructor
  ~EuclideanVector(){delete [] vec_;}

 private:
  T *vec_;
  int size_;
};



// --------------------------------------------------------------

// --------------------------------------------------------------
#include <fstream>
#include <iterator>
#include <cmath>
// --------------------------------------------------------------
int main() {
   

  // --------------------------------------------------------------
  std::set<char> s{'a','e','i','o','u'};
  std::vector<std::string> vec;
  vec.push_back("Hayden");
  vec.push_back("is");
  vec.push_back("made");
  vec.push_back("of");
  vec.push_back("pineapple");
  int sum = 0;

  
  sum = std::accumulate(vec.begin(), vec.end(),0,
          [&s](auto a, auto b) -> int{
              auto it =std::remove_if(b.begin(),b.end(),
                      [&s](auto x){return s.count(x);});
              return a += std::distance(it,b.end());
          });
/*
  sum = std::accumulate(vec.begin(), vec.end(),0,
          [&s](auto a, auto b) -> int{
              return a += std::accumulate(b.begin(),b.end(),0,
                      [&s](auto i, auto j)->int{return i += s.count(j) ? 1 :0;});
         });
*/
  std::cout << "Sum: " << sum << "\n";



/*
   // copy(istream_iterator<int>{cin}, istream_iterator<int>{},
    //        ostream_iterator<int>{cout,"---"});

    // --------------------------------------------------------------
  Lemon l(3, "Very sour!");
  std::cout << l << "\n";

    // --------------------------------------------------------------
    Base4 b;
    Derived4 d;
    print(b);
    print(d);

    // --------------------------------------------------------------
    int i = 99;
    flip(fo,42,i);
    // --------------------------------------------------------------
    int* p = new int(66);
    int i = 77;
    printPointer(p);
    printPointer(i);
    IsReal(p);

    // --------------------------------------------------------------
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
    Base2& b2(d); // only access base elements 
    // since b2 dynamic type is derived , we can down cast its 
    // static type to the derived type to let the compiler know that
    // it is a derived class
    Derived2& dd{static_cast<Derived2&>(b2)};
    dd.GetBase() = 999;
    cout << d.GetBase() << endl;
    const Derived2& d4(d3); // okay
    
    // since expects a reference to the base
    // when a virtual function called , its dynamic type is used
    PrintClassName(b2); // call derived class
    PrintClassName(d4);

    int temp = 99;
    int& tempr = temp;
    decltype(tempr) rr = temp;
    tempr =999;
    rr = 10000;
    cout << tempr << " " << temp<< endl;

    cout << std::is_same<int, int>()<< endl;
    const int temp3 = 88;
    Type(G());
    cout << F() << endl;

    // --------------------------------------------------------------
    BaseClass base_class;
    SubClass sub_class;

    PrintClassName(base_class);
    PrintClassName(sub_class);

    // --------------------------------------------------------------
    Base<int> b(99);
    Derived<int, double> d(2.0,99);
    foo(d);


    // --------------------------------------------------------------
    std::array<int, 3> i{ -1, -2, -3 };
    std::cout << findMax(i) << "\n";
    std::array<double, 3> j{ 1.0, 1.1, 1.2 };
    std::cout << findMax(j) << "\n";

    // --------------------------------------------------------------
    Stack<int> is1;
    is1.push(2);
    is1.push(3);
    is1.push(5);
//    Stack<int> is2{is1}; // this works
    Stack<double> ds1{is1}; // this does not

    auto result = ds1.Get();
    cout << result[0] << endl;


   std::cout << Ask<int>::val << "\n";
   std::cout << Ask<void>::val << "\n";

    // -----------------------------------------
    Queue<string,3> q5;
    q5.enque("good");
    q5.enque("right");
    q5.enque("for");
    cout << q5 << endl;

    Queue<int,2> q2;
    q2.enque(1);
    q2.enque(2);
    cout << q2 << endl;

    // ----------------------------------------------------------------------
    Queue<string> q(3);
    q.enque("good");
    q.enque("job");
    q.enque("man");
    cout << q << endl;
    cout << q.deque() << endl;
    cout << q.deque() << endl;
    cout << q << endl;
    Queue<string> qq(q);
    cout<< qq << endl;

    Queue<int> q2(3);
    q2.enque(1);
    q2.enque(2);
    q2.enque(3);
    cout << q2 << endl;
    cout << q2.deque() << endl;
    cout << q2 << endl;

    auto u = make_unique<string>("this is good");
    auto u2 = make_unique<string>("this is bad");
    u.reset(u2.release());
    cout << *u << endl;
    */




/*
 * ------------------------------------------
    set<int> s{4,1,2,8,3};
    for(auto it = s.begin(); it != s.end(); ++it){
        if(*it == 4){
            s.erase(it);
            cout << *it << endl;
        }
        cout << "all iterators: "<<  *it << endl;
    }

 * ------------------------------------------
    try {
       llama();
    } catch (Giraffe g) {
       std::cout << "caught in main" << '\n';
    }

 * ------------------------------------------
    auto p = make_unique<double>(99.0);
    unique_ptr<double> p2 = make_unique<double>(100.0);
    auto p3 = make_unique<int[]>(10);

    p = std::move(p2);
    cout << *p << endl;

    auto sp = make_shared<double>(1000.0);
    sp.reset(p.release());
   
    cout << *sp << endl;
    // cout << *p << endl; // error

    weak_ptr<double> wp(sp);
    if(auto sp2 = wp.lock()){
        cout << *sp2 << endl;
    }


 * ------------------------------------------
    std::vector<Book> books1{
        Book{"Book1", "Author1", 2222, 12.2},
        Book{"Book2", "Author2", 1111, 11.50},
        Book{"Book3", "Author3", 3333, 10.50}};
    
    std::vector<Book> books2{
        Book{"Book1", "Author1", 2222, 12.2},
        Book{"Book2", "Author2", 1111, 11.50},
        Book{"Book3", "Author3", 3333, 10.50}};
    
    print("Books:", books1);
    
    // Call the std::vector<Book> operator==() overload which in
    // turn calls Book operator==() overload.
    std::cout << "Vector of books are equal: "
              << "books1 " << (books1 == books2 ? "==" : "!=")
              << " books2\n\n";
    
    std::sort(books1.begin(), books1.end());
    print("Default (ISBN) sorted books:", books1);
    
    std::cout << "Vector of books are no longer equal: "
              << "books1 " << (books1 == books2 ? "==" : "!=")
              << " books2\n\n";
    
    std::sort(books1.begin(), books1.end(),
              [](const Book& a, const Book& b) {
                return a.GetPrice() < b.GetPrice();
              }
    );
    
    print("Price sorted books:", books1);

 * ------------------------------------------
    Car c2{"ford",8};
    Car c1;
    c1 = std::move(c2);
    cout << c1.GetSeats() << endl;
    cout << c2.GetSeats() << endl;

 * ------------------------------------------
    Point p1{1,2};
    Point p2{99,99};

    cout << p1 << endl;
    cout << (p1 += p2).GetX()<< endl; // += return a reference to the object
    cout << p1 << endl; // print out the updated p1
   
    cout << p1++ << endl;; 
    cout << p1 << endl;; 

    cout << ++p1 << endl; // 
    cout << p1 << endl; // 

    vector<int> v = static_cast<vector<int>>(p1);

    string s = "good job";

    StringPtr p{new string{"good job"}};
    // p.operator->()->size() operator -> reapply itself
    cout << p->size() << endl;


    // --------------------------------------------
    string buff = "really$^good$^one";
    string delim = "$^";

    auto v = Split(buff,delim);
    std::ostream_iterator<string> oss(cout," ");
    
    copy(v.begin(),v.end(),oss);

    // --------------------------------------------

    Car c("Nisan",9);
    cout << c.GetSeats() << endl;

    Car c2;
    cout << Car::ObjectCount() << endl;
    */
}








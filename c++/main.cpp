#include <iostream>
#include <memory>
#include <algorithm>
#include <numeric>
#include <vector>
#include <set>
#include <utility>
#include <map>


using namespace std;
// ===================================================================
// Complete the commonChild function below.
template<typename T>
ostream& operator<<(ostream& os,vector<vector<T>>& v){
    for(const auto& v1:v){
        for(const auto& v2:v1)
            cout<< v2<<" ";
        cout<<endl;
    }
    return os;
}

template<typename T>
ostream& operator<<(ostream& os,vector<T>& v){
    for(const auto& v1:v){
        cout<< v1<<" ";
    }
    cout<<endl;
    return os;
}


// ------------------------------------------------------------------------------------
class N{
    public:
        N(){};
        N(std::string s): s_(s){}

        string& GetS(){return s_;}
    private:
        std::string s_;
};

class I{
    public:
        int num_;
};

class I2{
    public:
        int num2_;
        I mem_;
};

class I3{
    public:
        int num3_;
};


class A {
public:
 int a_; // memeory untouched
};

class B {
public:
 B() = default;
 B(int b): b_{b} {}
 int b_;

};

class C {
public:
 int i{99}; // in-class initialiser
 int j; // Untouched memory
 A a; // since primitive type member in A , so no constructor is called 
 // This stops default constructor
 // from being synthesized.
 B b;
};

class AA {
    public:
        string s_;
        string s2_;
        int num_{100};
};

class AAA{
    public:
        int num1_, num2_;
};



// ------------------------------------------------------------------------------------

void f(int&& i, int& j){
    cout<<i << " "<< j <<endl;
}

// ------------------------------------------------------------------------------------
/* forward<T> is &&T: forward returns an rvalue reference to 
 * that explicit argument type
 */
template <typename F, typename T1, typename T2>
void flip(F f, T1&& t1, T2&& t2){
   /*when pass in flip2(f,i,42)  
    * T1 will be of int& , so int& && t1, t1 collapse into int& t1
    * T2 will be of int&&, so int&& && t2, t2 collapse into int&& t2 
    * forward t1 and t2 will preserve the type it passed in through flip
    */
    f(std::forward<T2>(t2),std::forward<T1>(t1)); 
}

/*when pass in flip2(f,i,42) 
 * T1 will be of int& , so int& && t1, t1 collapse into int& t1
 * T2 will be of int&&, so int&& && t2, t2 collapse into int&& t2 
 */
template <typename F, typename T1, typename T2>
void flip2(F f, T1&& t1, T2&& t2){
    f(t2,t1); // now t2 is a lvalue reference can not bind to rvalue reference in f paramater
}

// ------------------------------------------------------------------------------------
class BaseClass {
public:
 virtual std::string GetClassName() {
 return "BaseClass\n";
 };
  ~BaseClass() {
 std::cout << "Destructing base class\n";
 }

 int num = 10;
};

class SubClass: public BaseClass {
public:
 std::string GetClassName() override {
 return "SubClass\n";
 }
 ~SubClass() {
 std::cout << "Destructing subclass\n";
 }

 double sub_num = 99.0;
};

void PrintClassName(BaseClass& base_class) {
    std::cout << base_class.GetClassName()<< '\n';
}

class BB {
    protected:
        int b = 99;
};

class D :public BB {
    public:
        void CallB() {
            cout<<"here is b in B:" <<b<<endl;
        }

        int d = 100;
};

int gob = 100;
class T {
    int& b_ = gob;

    T(const T& t){
        b_ = t.b_; 

    }
};

// ------------------------------------------------------------------
class Mul {
public:
    static int total_;
    
    void operator()(int a ) {
        total_ += a;
        cout << a << endl;
    }
};

int Mul::total_ = 0;

int mul(int a, int b){
    return a*b;
}

char to_upper(char& value) {
 return std::toupper(static_cast<unsigned char>(value));
}

auto print = [](int a){cout << a << " ";};

#include <Eigen/Dense>
using namespace Eigen;
// ===================================================================
C g; // global object
int main()
{
    
    vector<int> v{1,2,3};
    int product = std::accumulate(v.begin(), v.end(), 1, mul);
    cout << product << endl;


    std::string s = "hello world";
    // std::for_each modifies each element
    // Mul()(100);
    Mul m;
    m(100);
    std::for_each(v.begin(), v.end(), Mul());
    cout << " we have total : " << Mul::total_ << endl;

    std::string upper;
    // Algorithms like transform, which have output iterators,
    // use the other iterator as an output.
    std::transform(s.begin(), s.end(), std::back_inserter(upper), to_upper);
    cout << upper << endl;

    std::reverse(s.begin(), s.end());
    cout << s << endl;



    /*
    C cc{};
    AA a{"cool","bad"};
    //cout << a.s_ << " " <<a.s2_ << " " <<  a.num_ <<endl;

    AAA aaa{99};
    //cout << aaa.num1_  << " "<< aaa.num2_ << endl;

    MatrixXd m(3,3);
    m << 1, 2, 3,
         4, 5, 6,
         7, 8, 9;
    std::cout << m<<endl;

    MatrixXd v(3,1);
    v << 1,2,3;

    cout << v[2] <<endl;
    
    cout << cc.a.a_<<endl;
    cout << cc.b.b_<<endl;
    cout << cc.j<<endl;
    cout << cc.i<<endl;
    cout << " -----------------"<<endl;
    cout << g.a.a_<<endl;
    cout << g.b.b_<<endl;
    cout << g.j<<endl;
    cout << g.i<<endl;
    */


 return 0;
}


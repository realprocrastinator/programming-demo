
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

// ============================================================
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
        operator vector<int>() const { // for type converstion
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
int main() {

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

}


// ============================================================
// Book example
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

//----------------------------------------------------------------
int main() {
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
}

// --------------------------------------------------------------


/*
 * Why are some operator overloads done as member functions, and others as friends?
 * Non-members: For when the operator doesn't take an instance of the class as the LHS argument
        If we need this non-member function to access private fields of the class type, we define this 
 *  non-member overload as a friend Members: For when the operator does take an instance of the class
 *  as the LHS argument
*/



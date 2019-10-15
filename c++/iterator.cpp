#include <iostream>
#include <iteartor>

using namespace std;
// --------------------------------------------------------------------------
// iterator invalidation

// push back:
// If the new  is greater than  then all iterators and references 
// (including the past-the-end iterator) are invalidated. 
// Otherwise only the pastthe-end iterator is invalidated.
std::vector v{1, 2, 3, 4, 5};
// Copy all 2s
for (auto it = v.begin(); it != v.end(); ++it) {
    if (*it == 2) {
        v.push_back(2); // push_back cause all iterator invalid
    }
}

// erase
// Invalidates iterators and references at or after the point of the erase,
// including the end iterator
// Erase all 2s
for (auto it = v.begin(); it != v.end(); ++it) {
    if (*it == 2) {
        v.erase(it); // erease also cuase iterator invalid
    }
}

/*Containers generally don't invalidate when you modify values
But they may invalidate when removing or adding elements
std::vector invalidates everything when adding elements
std::unordered_(map/set) invalidates everything when adding elements
std::map/set does not invalidate iterators upon insertion, since the the order is still
maintained , when erease , will only invlidate the iterator at the erase point
so if wish to continue the iteator need to get the iterator from the erease and continue iterating from there

 */
int main() {
    set<int> s{4,1,2,8,3};
    for(auto it = s.begin(); it != s.end(); ++it){
        if(*it == 4){
            s.erase(it); // it becomes invalid
            cout << *it << endl; // undefined value
        }
        cout << "all iterators: "<<  *it << endl;
        // increase an invalid iterator undefined behavior
    }
}


// --------------------------------------------------------------------------
// min requirement for forward iterator
class MyClass{
    private:
        struct Iterator {
            using iterator_category = std::forward_iterator_tag;
            using value_type = T;
            using reference = T&;
            using pointer = T*; // Not strictly required, but nice to have.
            using difference_type = int; // to know the distance to increase
            
            // depends on the catergories of the iterator , operator needs to be defined accordingly
            reference operator*() const;
            Iterator& operator++();
            Iterator operator++(int) {
                auto copy{*this};
                ++(*this);
                return copy;
            }
            // This one isn't strictly required, but it's nice to have.
            pointer operator->() const { return &(operator*()); }
            friend bool operator==(const Iterator& lhs, const Iterator& rhs) { ... };
            friend bool operator!=(const Iterator& lhs, const Iterator& rhs) { return !(lhs == rhs); }
        
            // make the container encapsulate the iterator as friend
            friend class MyContainer;
        
            // some iterator memebers 
            // e.g. could use iterator of the internel container
        };

    public:
         // Make the iterator using one of these by convention.
        using iterator = Iterator;
        
        // the iterator public interface through the container
        // Need to define these.
        iterator begin(){}; // init the internel state of the iterator to the container data memeber
        iterator end(){}; // init the end of iterator indicating the end

        // If you want const iterators (hint: you do), define these.
        const_iterator begin() const { return cbegin(); }
        const_iterator cbegin();
        const_iterator end() const { return cend(); }
        const_iterator cend() const;

        // reverse iterator
        // as long as it is a bidirectional iterator that suppor -- and 
        // can go back from end of iterator to the begin() then reverse iterator
        // can be created automatically
        using reverse_iterator = std::reverse_iterator<iterator>;
        reverse_iterator rbegin() { return reverse_iterator{end()}; }
        reverse_iterator rend() { return reverse_iterator{begin()}; }

        

        // the rest MyClass content

}

// --------------------------------------------------------------------------
// intstack example

#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <utility>

using std::begin;
using std::rbegin;
using std::cbegin;
using std::end;
using std::rend;

class IntStack {
 private:
  struct Node {
    Node(int value, std::unique_ptr<Node>&& next, Node* prev):
       value{value}, next{std::move(next)},prev{prev}{}
    int value;
    std::unique_ptr<Node> next;
    Node* prev;
  };

  // Exercise to the reader once we've covered templates:
  // Try making the const iterator and the non-const iterator with one class template.
  template <typename T>
  class Iterator {
   public:
    // define all the iterator traits here
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;// what type of value iterator points to
    using reference = T&;// what type reference
    using pointer = T*; // what type pointer
    using difference_type = T; // to calculate distance between iterators

    reference operator*() const { return node_->value; }// get the value of reference
    pointer operator->() const { return &(operator*()); }// return the pointer of the value
    Iterator operator++() {// follow the next pointer this nodes points to
      node_ = node_->next.get();
      return *this;
    }
    Iterator operator++(int) {
      auto copy{*this};
      ++(*this);
      return copy;
    }

    Iterator operator--() {// follow the next pointer this nodes points to
      node_ = node_->prev;
      return *this;
    }
    Iterator operator--(int) {
      auto copy{*this};
      --(*this);
      return copy;
    }

    friend bool operator==(const Iterator& lhs, const Iterator& rhs) {
      return lhs.node_ == rhs.node_;
    }

    friend bool operator!=(const Iterator& lhs, const Iterator& rhs) { return !(lhs == rhs); }

   private:
    explicit Iterator(Node* node): node_{node} {}
    Node* node_;

    friend class IntStack; 
  };

 public:
  // TODO(lecture): show how make const and non-const iterators during lecture.
  IntStack(): head_(std::make_unique<Node>(0,nullptr,nullptr)),
            tail_{head_.get()}{};

  using iterator = Iterator<int>;
  using const_iterator = Iterator<const int>;

  // construct from the head's pointer
  // iterator does no own the item it iterate over so we use raw pointer instead of shared_ptr
  iterator begin() { return iterator{head_.get()}; }
  const_iterator begin() const { return cbegin(); }
  // just construct an iterator from nullptr
  const_iterator cbegin() const { return const_iterator{head_.get()};}
  iterator end() { return iterator{tail_}; }
  const_iterator end() const { return cend(); }
  const_iterator cend() const { return const_iterator{tail_}; }

  // Make the iterator using these.
   using reverse_iterator = std::reverse_iterator<iterator>;
   using const_reverse_iterator = std::reverse_iterator<const_iterator>;
   // Need to define these.
   reverse_iterator rbegin() { return reverse_iterator{end()}; }
   reverse_iterator rend() { return reverse_iterator{begin()}; }
   // If you want const reverse iterators (hint: you do), define these.
   const_reverse_iterator rbegin() const { return crbegin(); }
   const_reverse_iterator rend() const { return crend(); }
   const_reverse_iterator crbegin() const { return const_reverse_iterator{cend()}; }
   const_reverse_iterator crend() const { return const_reverse_iterator{cbegin()}; }


  void push(int value) { 
      head_ = std::make_unique<Node>(value, std::move(head_),nullptr);
      head_->next->prev = head_.get();
  }

  // TODO(students): Why doesn't std::stack::pop return the value you pop?
  void pop() { head_ = std::move(head_->next); }

  const int& top() const { return *cbegin(); }
  int& top() { return *begin(); }

 private:
  std::unique_ptr<Node> head_;
  Node* tail_; // for the dummy of of iterator for bidir iterator
  //std::set<Node>::iterator it_; // if using pre existing type , can store existing type iteartor
};

//===========================================================================================
int main() {
  IntStack l;
  l.push(5);
  l.push(4);
  l.push(3);
  l.push(2);
  l.push(1);

  std::cout << std::boolalpha;
  std::cout << "Head is " << l.top() << '\n';
  // pop can only return value if needed ,but requries copy
  // pop can not return reference since it has been deallocated
  l.pop();
  std::cout << "After popping, head is " << l.top() << '\n';

  std::cout << "Algorithms\n";
  std::copy(begin(l), end(l), std::ostream_iterator<int>{std::cout, "\n"});

  auto check_present = [&] (int value) {
    std::cout << "Is " << value << " present: "
              << (std::find(begin(l), end(l), value) != end(l)) << '\n';
  };
  check_present(5);
  check_present(99);
  (*begin(l)) = 99;
  check_present(99);

  // TODO(lecture): This should fail to compile
  (*cbegin(l)) = 100;

  std::cout << "Range-for\n";
  for (const auto& item : l) {
    std::cout << item << '\n';
  }
}

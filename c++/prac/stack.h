#ifndef LECTURES_WEEK7_STACK_H_
#define LECTURES_WEEK7_STACK_H_

#include <vector>

template <typename T>
class Stack {
 public:
  void push(T);
  T pop();
 private:
  std::vector<T> stack_;
};

#include "stack.tpp"
#endif  // LECTURES_WEEK7_STACK_H_

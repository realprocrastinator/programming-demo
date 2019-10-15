template <typename T>
void Stack<T>::push(T t) {
  stack_.push_back(t);
}

template <typename T>
T Stack<T>::pop() {
  auto temp = stack_.back();
  stack_.pop_back();
  return temp;
}

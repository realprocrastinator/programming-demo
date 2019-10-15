#ifndef TUTORIALS_WEEK8_ROPE_H_
#define TUTORIALS_WEEK8_ROPE_H_

#include <optional>
#include <string>
#include <utility>
#include <vector>

class Rope {
 public:
  explicit Rope(std::vector<std::string> rope): rope_{std::move(rope)} {}
  
  template<typename T>
  class Iterator {
   public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using reference = T&;
    using pointer = T*;
    using difference_type = int;

    reference operator*() const;
    Iterator& operator++();
    Iterator operator++(int) {
      auto copy{*this};
      ++(*this);
      return copy;
    }

    // This one isn't strictly required, but it's nice to have.
    pointer operator->() const { return &(operator*()); }

    friend bool operator==(const Iterator& lhs, const Iterator& rhs) {
      // We need to check the sentinel because comparison of default constructed Iterators is undefined.
      return lhs.outer_ == rhs.outer_ && (lhs.outer_ == lhs.sentinel_ || lhs.inner_ == rhs.inner_);
    }

    friend bool operator!=(const Iterator& lhs, const Iterator& rhs) { return !(lhs == rhs); }


   private:
    std::vector<std::string>::iterator outer_;
    const std::vector<std::string>::iterator sentinel_;
    std::string::iterator inner_;

    friend class Rope;
    Iterator(const decltype(outer_)& outer, const decltype(sentinel_)& sentinel, const decltype(inner_)& inner): outer_{outer}, sentinel_{sentinel}, inner_{inner} {}
  };

  using iterator = Iterator<char>;
  using const_iterator = Iterator<const char>; 

  iterator begin();
  iterator end();
  const_iterator cbegin();
  const_iterator cend();

 private:
  std::vector<std::string> rope_;
};



// =================================================================================
#include <algorithm>
template <typename T>
typename Rope::Iterator<T>::reference Rope::Iterator<T>::operator*() const {
  return *inner_;
}

template <typename T>
typename Rope::Iterator<T>& Rope::Iterator<T>::operator++() {
  ++inner_;
  if (inner_ == outer_->end()) {
    do {
      ++outer_;
    } while (outer_ != sentinel_ && outer_->begin() == outer_->end());
    if (outer_ != sentinel_) {
      inner_ = outer_->begin();
    }
  }
  return *this;
}

Rope::iterator Rope::begin() {
  // What if the first element is empty?
  if (auto first = std::find_if(rope_.begin(), rope_.end(), [] (const std::string& s) { return !s.empty(); }); first != rope_.end()) {
    return {first, rope_.end(), first->begin()};
  }
  return end();
}

Rope::iterator Rope::end() {
  return {rope_.end(), rope_.end(), {}};
}


Rope::const_iterator Rope::cbegin() {
  // What if the first element is empty?
  if (auto first = std::find_if(rope_.begin(), rope_.end(), [] (const std::string& s) { return !s.empty(); }); first != rope_.end()) {
    return {first, rope_.end(), first->begin()};
  }
  return cend();
}

Rope::const_iterator Rope::cend() {
  return {rope_.end(), rope_.end(), {}};
}

#endif  // TUTORIALS_WEEK8_ROPE_H_

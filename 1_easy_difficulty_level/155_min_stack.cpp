/*
155. Leetcode coding challenge: Min stack

Design a stack that supports push, pop, top, and retrieving the minimum element
in constant time.

   push(x) -- Push element x onto stack.
   pop() -- Removes the element on top of the stack.
   top() -- Get the top element.
   getMin() -- Retrieve the minimum element in the stack.

Example:

MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin();   --> Returns -3.
minStack.pop();
minStack.top();      --> Returns 0.
minStack.getMin();   --> Returns -2.
*/

#include <functional>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>

using namespace std;

template <typename T, typename MinOperation = less<T>>
class MinStack {
  size_t min_element_index;
  vector<pair<T, size_t>> s;
  MinOperation min_op_;

 public:
  MinStack() : min_element_index{} { s.reserve(1024); }

  template <typename MinOperationFunc>
  MinStack(MinOperationFunc&& min_op)
      : min_element_index{}, min_op_{forward<MinOperationFunc>(min_op)} {
    s.reserve(1024);
  }

  T getMin() {
    if (s.empty())
      throw runtime_error{"Stack is empty!"};

    return s[min_element_index].first;
  }

  T top() {
    if (s.empty())
      throw runtime_error{"Stack is empty!"};

    return s.back().first;
  }

  void pop() {
    if (s.empty())
      throw runtime_error{"Stack is empty!"};

    s.pop_back();
    if (!s.empty())
      min_element_index = s.back().second;
  }

  void push(const int x) {
    if (s.empty()) {
      s.emplace_back(make_pair(x, 0u));
      min_element_index = 0u;
      return;
    }

    s.emplace_back(make_pair(x, min_element_index));

    if (min_op_(x, s[min_element_index].first))
      min_element_index = s.back().second = s.size() - 1;
  }
};

int main() {
  MinStack<int> ms{};

  try {
    ms.push(-2);
    printf("1. ms.push(-2);\n");
    ms.push(0);
    printf("2. ms.push(0);\n");
    ms.push(-3);
    printf("3. ms.push(-3);\n");
    cout << "4. ms.getMin() -> " << ms.getMin() << '\n';  // expected output: -3
    ms.pop();
    printf("5. ms.pop();\n");
    cout << "6. ms.top() -> " << ms.top() << '\n';        // expected output: 0
    cout << "7. ms.getMin() -> " << ms.getMin() << '\n';  // expected output: -2

  } catch (exception& e) {
    cerr << e.what() << '\n';
    return 1;
  }

  return 0;
}

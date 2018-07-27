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

#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>

using namespace std;

class MinStack {
  size_t min_element_index;
  vector<pair<int, size_t>> s;

 public:
  MinStack() : min_element_index{} { s.reserve(1024); }

  int getMin() {
    if (s.empty())
      throw runtime_error{"Stack is empty!"};

    return s[min_element_index].first;
  }

  int top() {
    if (s.empty())
      throw runtime_error{"Stack is empty!"};

    return s.back().first;
  }

  void pop() {
    if (s.empty())
      throw runtime_error{"Stack is empty!"};

    const int t{s.back().first};
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

    if (x < s[min_element_index].first)
      min_element_index = s.back().second = s.size() - 1;
    else
      s.back().second = min_element_index;
  }
};

int main() {
  MinStack ms{};

  ms.push(-2);
  ms.push(0);
  ms.push(-3);
  ms.getMin();
  ms.pop();
  ms.top();
  ms.getMin();

  return 0;
}

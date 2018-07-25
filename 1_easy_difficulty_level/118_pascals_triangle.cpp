/*
118. Leetcode coding challenge: Pascal's triangle

Given a non-negative integer numRows, generate the first numRows of Pascal's
triangle.

In Pascal's triangle, each number is the sum of the two numbers directly above
it.

Example:

Input: 5
Output:
[
     [1],
    [1,1],
   [1,2,1],
  [1,3,3,1],
 [1,4,6,4,1]
]
*/

#include <iostream>
#include <vector>

using namespace std;

template <typename T>
ostream& operator<<(ostream& os, const vector<T>& data) {
  if (data.empty()) {
    os << "data is empty\n";
    return os;
  }
  os << "\n  [";
  for (size_t i{}; i < data.size() - 1; i++)
    os << data[i] << ',';
  os << data.back() << "]";
  return os;
}

template <typename T>
ostream& operator<<(ostream& os, const vector<vector<T>>& data) {
  if (data.empty()) {
    os << "data is empty\n";
    return os;
  }

  os << "\n[\n";
  for (const auto& row : data)
    os << row;
  os << "\n]\n";

  return os;
}

class Solution {
 public:
  vector<vector<int>> generate(const size_t pascal_row_number) {
    if (!pascal_row_number)
      return {};
    if (1 == pascal_row_number)
      return {{1}};
    if (2 == pascal_row_number)
      return {{1}, {1, 1}};
    if (3 == pascal_row_number)
      return {{1}, {1, 1}, {1, 2, 1}};

    vector<vector<int>> current_pascal_triangle{{1}, {1, 1}, {1, 2, 1}};

    vector<int> prev_pascal_triangle_numbers{1, 2, 1};
    vector<int> next_pascal_triangle_numbers{};

    for (size_t i{4}; i <= pascal_row_number; i++) {
      next_pascal_triangle_numbers.emplace_back(1);

      for (size_t j{}; j < prev_pascal_triangle_numbers.size() - 1; j++)
        next_pascal_triangle_numbers.emplace_back(
            prev_pascal_triangle_numbers[j] +
            prev_pascal_triangle_numbers[j + 1]);

      next_pascal_triangle_numbers.emplace_back(1);

      current_pascal_triangle.emplace_back(next_pascal_triangle_numbers);

      prev_pascal_triangle_numbers.clear();

      swap(prev_pascal_triangle_numbers, next_pascal_triangle_numbers);
    }

    return current_pascal_triangle;
  }
};

int main() {
  Solution s{};

  const auto output{s.generate(5)};

  cout << "s.generate(5) -> " << output << '\n';

  return 0;
}

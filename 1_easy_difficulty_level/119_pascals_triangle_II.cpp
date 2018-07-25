/*
119. Leetcode coding challenge: Pascal's triangle II

Given a non-negative index k where k ≤ 33, return the kth index row of the
Pascal's triangle.

Note that the row index starts from 0.

In Pascal's triangle, each number is the sum of the two numbers directly above
it.

Example:

Input: 3
Output: [1,3,3,1]
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
  os << '[';
  for (size_t i{}; i < data.size() - 1; i++)
    os << data[i] << ',';
  os << data.back() << ']';
  return os;
}

class Solution {
 public:
  vector<int> getRow(const size_t rowIndex) {
    if (!rowIndex)
      return {1};
    if (1 == rowIndex)
      return {1, 1};
    if (2 == rowIndex)
      return {1, 2, 1};

    vector<int> prev_pascal_triangle_numbers{1, 2, 1};
    vector<int> next_pascal_triangle_numbers{};

    size_t iter{3};

    while (true) {
      next_pascal_triangle_numbers.emplace_back(1);

      for (size_t j{}; j < prev_pascal_triangle_numbers.size() - 1; j++)
        next_pascal_triangle_numbers.emplace_back(
            prev_pascal_triangle_numbers[j] +
            prev_pascal_triangle_numbers[j + 1]);

      next_pascal_triangle_numbers.emplace_back(1);

      if (rowIndex == iter)
        break;

      iter++;

      prev_pascal_triangle_numbers.clear();

      swap(prev_pascal_triangle_numbers, next_pascal_triangle_numbers);
    }

    return next_pascal_triangle_numbers;
  }
};

int main() {
  Solution s{};

  const auto output{s.getRow(3)};

  cout << "s.getRow(3) -> " << output << '\n';  // expected output: [1, 3, 3, 1]

  return 0;
}

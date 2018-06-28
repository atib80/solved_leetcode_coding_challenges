/*
Given a non-empty array of digits representing a non-negative integer, plus one
to the integer.

The digits are stored such that the most significant digit is at the head of the
list, and each element in the array contain a single digit.

You may assume the integer does not contain any leading zero, except the number
0 itself.

Example 1:

Input:  [1,2,3]
Output: [1,2,4]
Explanation: The array represents the integer 123.

Example 2:

Input:  [4,3,2,1]
Output: [4,3,2,2]
Explanation: The array represents the integer 4321.
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

template <typename T>
void print_range(T&& first, T&& last, ostream& os) {
  if (first == last)
    return;
  --last;
  os << '[';
  for_each(first, last, [&os](const auto& data) { os << data << ','; });
  os << *last << "]\n";
}

class Solution {
 public:
  Solution() = default;
  vector<int> plusOne(vector<int>& digits) {
    int index = digits.size() - 1;
    while (true) {
      if (index < 0) {
        digits.insert(begin(digits), 1);
        break;
      }

      digits[index]++;
      if (10 == digits[index]) {
        digits[index] = 0;
        index--;
      } else
        break;
    }

    return move(digits);
  }
};

int main() {
  Solution s{};
  vector<int> input{1, 2, 3};
  auto output = s.plusOne(input);
  cout << "s.plusOne(input) -> ";
  print_range(begin(output), end(output), cout);
  input.assign({4, 3, 2, 1});
  output = s.plusOne(input);
  cout << "s.plusOne(input) -> ";
  print_range(begin(output), end(output), cout);
  return 0;
}

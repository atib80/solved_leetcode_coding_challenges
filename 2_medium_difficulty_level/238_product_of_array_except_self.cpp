/*
238. Product of array except self (difficulty level: medium)

Given an array nums of n integers where n > 1,  return an array output such that
output[i] is equal to the product of all the elements of nums except nums[i].

Example:

Input:  [1,2,3,4]
Output: [24,12,8,6]

Note: Please solve it without division and in O(n).

Follow up:
Could you solve it with constant space complexity? (The output array does not
count as extra space for the purpose of space complexity analysis.)
*/

#include <algorithm>
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
  vector<int> productExceptSelf(vector<int>& nums) {
    int product{1};
    bool found_zero{}, multiple_zeroes{};
    for_each(begin(nums), end(nums),
             [&product, &found_zero, &multiple_zeroes](const int n) {
               if (!n) {
                 if (found_zero)
                   multiple_zeroes = true;
                 found_zero = true;
               } else
                 product *= n;
             });

    for (int& n : nums) {
      if (multiple_zeroes)
        n = 0;
      else if (n) {
        if (found_zero)
          n = 0;
        else
          n = product / n;
      } else
        n = product;
    }

    return move(nums);
  }
};

int main() {
  Solution s{};
  vector<int> input{1, 2, 3, 4};
  auto output{s.productExceptSelf(input)};
  cout << "s.productExceptSelf([1,2,3,4]) -> " << output
       << '\n';  // expected output: [24,12,8,6]

  input.assign({0, 0});
  output = s.productExceptSelf(input);
  cout << "s.productExceptSelf([0, 0]) -> " << output
       << '\n';  // expected output: [0, 0]

  input.assign({1, 0});
  output = s.productExceptSelf(input);
  cout << "s.productExceptSelf([1, 0]) -> " << output
       << '\n';  // expected output: [0, 1]

  input.assign({1, 0, 2, 3, 4, 5, 6, 7, 8, 9, 0});
  output = s.productExceptSelf(input);
  cout << "s.productExceptSelf([1, 0, 2, 3, 4, 5, 6, 7, 8, 9, 0]) -> " << output
       << '\n';  // expected output: [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]

  return 0;
}

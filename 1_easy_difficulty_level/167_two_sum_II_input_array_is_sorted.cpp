/*
Given an array of integers that is already sorted in ascending order, find two
numbers such that they add up to a specific target number.

The function twoSum should return indices of the two numbers such that they add
up to the target, where index1 must be less than index2.

Note:

    Your returned answers (both index1 and index2) are not zero-based.
    You may assume that each input would have exactly one solution and you may
not use the same element twice.

Example:

Input: numbers = [2,7,11,15], target = 9
Output: [1,2]
Explanation: The sum of 2 and 7 is 9. Therefore index1 = 1, index2 = 2.
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

class Solution {
 public:
  vector<int> twoSum(const vector<int>& numbers, const int target) {
  	
    int first{}, second{static_cast<int>(numbers.size()) - 1};
    while (first < second) {
      if (numbers[first] + numbers[second] == target)
        return {first + 1, second + 1};
      else if (numbers[first] + numbers[second] > target)
        second--;
      else
        first++;
    }

    return {0, 0};
  }
};

int main() {
  Solution s{};
  const auto output{s.twoSum({2, 7, 11, 15}, 9)};
  cout << "s.twoSum({2,7,11,15}) -> " << output
       << '\n';  // expected output: [1, 2]
  return 0;
}

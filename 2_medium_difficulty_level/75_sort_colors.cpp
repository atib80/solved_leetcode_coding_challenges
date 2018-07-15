/*
75. Leetcode coding challenge: Sort colors

Given an array with n objects colored red, white or blue, sort them in-place so
that objects of the same color are adjacent, with the colors in the order red,
white and blue.

Here, we will use the integers 0, 1, and 2 to represent the color red, white,
and blue respectively.

Note: You are not suppose to use the library's sort function for this problem.

Example:

Input: [2,0,2,1,1,0]
Output: [0,0,1,1,2,2]

Follow up:

    A rather straight forward solution is a two-pass algorithm using counting
sort. First, iterate the array counting number of 0's, 1's, and 2's, then
overwrite array with total number of 0's, then 1's and followed by 2's. Could
you come up with a one-pass algorithm using only constant space?

*/

#include <iostream>
#include <vector>

using namespace std;

static int sr = []() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  return 0;
}();

template <typename T>
ostream& operator<<(ostream& os, const vector<T>& data) {
  if (data.empty()) {
    os << "data is empty\n";
    return os;
  }
  os << "\n[";
  for (size_t i{}; i < data.size() - 1; i++)
    os << data[i] << ',';
  os << data.back() << "]\n";
  return os;
}

class Solution {
 public:
  void sortColors(vector<int>& nums) {
    const size_t nums_size{nums.size()};

    size_t start_1{}, start_2{nums.size()};

    size_t i{};

    while (i < nums_size) {
      switch (nums[i]) {
        case 0:
          if (i > start_1) {
            nums.erase(begin(nums) + i);
            nums.insert(begin(nums) + start_1, 1, 0);
            if (i > start_2)
              start_2++;
          }
          i++;

          break;

        case 1:
          if (i > start_2) {
            nums.erase(begin(nums) + i);
            nums.insert(begin(nums) + start_2, 1, 1);
            start_2++;
          }
          i++;

          break;

        case 2:

          if (i < start_2) {
            nums.erase(begin(nums) + i);
            nums.emplace_back(2);
            start_2--;
          } else
            i++;
          break;
      }
    }
  }
};

int main() {
  Solution s{};

  vector<int> input{2, 0, 2, 1, 1, 0, 2, 1, 0, 1, 2,
                    0, 1, 2, 1, 0, 2, 0, 1, 1, 2, 0};
  s.sortColors(input);
  cout << "s.sortColors({2, 0, 2, 1, 1, 0, 2, 1, 0, 1, 2, 0, 1, 2, 1, 0, 2, 0, "
          "1, 1, 2, 0}) -> "
       << input << '\n';

  return 0;
}

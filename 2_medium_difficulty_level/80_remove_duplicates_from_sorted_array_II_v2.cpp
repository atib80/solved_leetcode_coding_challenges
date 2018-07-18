/*
80. Leetcode coding challenge: Remove duplicates from sorted array II
(2nd version does not explicitly erase duplicate elements of given input vector.
Instead it keeps tracks of a handy source and a destination index in order to
move vector's elements to their correct places)

Given a sorted array nums, remove the duplicates in-place such that duplicates
appeared at most twice and return the new length.

Do not allocate extra space for another array, you must do this by modifying the
input array in-place with O(1) extra memory.

Example 1:

Given nums = [1,1,1,2,2,3],

Your function should return length = 5, with the first five elements of nums
being 1, 1, 2, 2 and 3 respectively.

It doesn't matter what you leave beyond the returned length.

Example 2:

Given nums = [0,0,1,1,1,1,2,3,3],

Your function should return length = 7, with the first seven elements of nums
being modified to 0, 0, 1, 1, 2, 3 and 3 respectively.

It doesn't matter what values are set beyond the returned length.

Clarification:

Confused why the returned value is an integer but your answer is an array?

Note that the input array is passed in by reference, which means modification to
the input array will be known to the caller as well.

Internally you can think of this:

// nums is passed in by reference. (i.e., without making a copy)
int len = removeDuplicates(nums);

// any modification to nums in your function would be known by the caller.
// using the length returned by your function, it prints the first len elements.
for (int i = 0; i < len; i++) {
    print(nums[i]);
}
*/

#include <iostream>
#include <vector>

using namespace std;

static int sres = []() {
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
  os << '[';
  for (size_t i{}; i < data.size() - 1; i++)
    os << data[i] << ',';
  os << data.back() << ']';
  return os;
}

class Solution {
 public:
  size_t removeDuplicates(vector<int>& nums) {
    if (nums.empty())
      return 0;

    size_t i{1}, j{1}, count{1};
    int value{nums[0]};

    while (i < nums.size()) {
      if (value == nums[i]) {
        count++;
        if (count > 2) {
          i++;
          continue;
        }
      } else {
        value = nums[i];
        count = 1;
      }

      nums[j] = nums[i];
      i++;
      j++;
    }

    return j;
  }
};

int main() {
  Solution s{};

  vector<int> numbers{1, 1, 1, 2, 2, 3};
  cout << "numbers.size() before removing duplicates: " << numbers.size()
       << '\n';
  size_t nums_size = s.removeDuplicates(numbers);
  cout << "numbers.size() after removing duplicates: " << nums_size << '\n';
  numbers.erase(begin(numbers) + nums_size, end(numbers));
  cout << "s.removeDuplicates({1,1,1,2,2,3}) -> " << numbers << "\n\n";
  numbers.assign({1, 1, 1});
  cout << "numbers.size() before removing duplicates: " << numbers.size()
       << '\n';
  nums_size = s.removeDuplicates(numbers);
  cout << "numbers.size() after removing duplicates: " << nums_size << '\n';
  numbers.erase(begin(numbers) + nums_size, end(numbers));
  cout << "s.removeDuplicates({1,1,1}) -> " << numbers << '\n';
  numbers.assign({1, 1, 1, 2, 2, 2, 3, 3});
  cout << "numbers.size() before removing duplicates: " << numbers.size()
       << '\n';
  nums_size = s.removeDuplicates(numbers);
  cout << "numbers.size() after removing duplicates: " << nums_size << '\n';
  numbers.erase(begin(numbers) + nums_size, end(numbers));
  cout << "s.removeDuplicates({1,1,1,2,2,2,3,3}) -> " << numbers << '\n';

  return 0;
}

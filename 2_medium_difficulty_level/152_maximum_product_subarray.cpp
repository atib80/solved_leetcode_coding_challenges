/*
152. Maximum product subarray

Given an integer array nums, find the contiguous subarray within an array
(containing at least one number) which has the largest product.

Example 1:

Input: [2,3,-2,4]
Output: 6
Explanation: [2,3] has the largest product 6.

Example 2:

Input: [-2,0,-1]
Output: 0
Explanation: The result cannot be 2, because [-2,-1] is not a subarray.
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {

 public:
  int maxProduct(const vector<int>& nums) {
    int max_product{nums[0]}, previous_max_product{nums[0]},
        previous_min_product{nums[0]};

    for (size_t i{1}; i < nums.size(); i++) {
      const int prev_max_curr_product{previous_max_product * nums[i]};
      const int prev_min_curr_product{previous_min_product * nums[i]};
      const int current_max_product{
          max(prev_max_curr_product, max(prev_min_curr_product, nums[i]))};
      const int current_min_product{
          min(prev_max_curr_product, min(prev_min_curr_product, nums[i]))};
      if (current_max_product > max_product)
        max_product = current_max_product;
      previous_max_product = current_max_product;
      previous_min_product = current_min_product;
    }

    return max_product;
  }
};

int main() {
  Solution s{};

  cout << "s.maxProduct() -> " << s.maxProduct({2, 3, -2, 4})
       << '\n';  // expected output: 6
  cout << "s.maxProduct() -> " << s.maxProduct({-2, 0, -1})
       << '\n';  // expected output: 0

  return 0;
}
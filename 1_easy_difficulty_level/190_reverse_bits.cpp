/*
Reverse bits of a given 32 bits unsigned integer.

Example:

Input: 43261596
Output: 964176192
Explanation: 43261596 represented in binary as 000000101001010000011110
10011100, return 964176192 represented in binary as
00111001011110000010100101000000.

Follow up:
If this function is called many times, how would you optimize it?
*/

#include <cstdint>
#include <iostream>
#include <string>

using namespace std;

class Solution {
 public:
  uint32_t reverseBits(uint32_t n) {
    uint32_t result{}, left_mask{1u << 31}, right_mask{1u};

    while (left_mask > right_mask) {
      if (n & left_mask)
        result |= right_mask;
      if (n & right_mask)
        result |= left_mask;

      left_mask >>= 1;
      right_mask <<= 1;
    }

    return result;
  }

  uint32_t reverseBits_v2(uint32_t n) {
    uint32_t result{};
    size_t counter{};

    while (counter < 32) {
      result <<= 1;
      result |= n & 1;
      n >>= 1;
      ++counter;
    }

    return result;
  }
};

int main() {
  Solution s{};
  cout << "s.reverseBits(43261596u) -> " << s.reverseBits(43261596u)
       << '\n';  // expected output: 964176192
  cout << "s.reverseBits_v2(43261596u) -> " << s.reverseBits_v2(43261596u)
       << '\n';  // expected output: 964176192

  return 0;
}

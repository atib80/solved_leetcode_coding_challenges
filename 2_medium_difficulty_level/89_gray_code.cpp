/*
The gray code is a binary numeral system where two successive values differ in
only one bit.

Given a non-negative integer n representing the total number of bits in the
code, print the sequence of gray code. A gray code sequence must begin with 0.

Example 1:

Input: 2
Output: [0,1,3,2]
Explanation:
00 - 0
01 - 1
11 - 3
10 - 2

For a given n, a gray code sequence may not be uniquely defined.
For example, [0,2,3,1] is also a valid gray code sequence.

00 - 0
10 - 2
11 - 3
01 - 1

Example 2:

Input: 0
Output: [0]
Explanation: We define the gray code sequence to begin with 0.
             A gray code sequence of n has size = 2n, which for n = 0 the size
is 20 = 1. Therefore, for n = 0 the gray code sequence is [0].

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
  os << "\n  [";
  for (size_t i{}; i < data.size() - 1; i++)
    os << data[i] << ',';
  os << data.back() << "]";
  return os;
}

class Solution {
 public:
  vector<int> grayCode(const size_t n) {
    if (!n)
      return vector<int>{0};
    if (1 == n)
      return vector<int>{0, 1};

    const size_t count{1u << n};
    vector<int> gray_codes{}, valid_masks{};
    gray_codes.reserve(count);
    valid_masks.reserve(n);

    for (size_t i{}, mask{1}; i < n; i++) {
      valid_masks.emplace_back(mask);
      mask <<= 1;
    }

    do {
      gray_codes.clear();
      gray_codes.emplace_back(0);
      vector<int> unique_grey_codes(count, 0);
      unique_grey_codes[0] = 1;
      int value{};
      int prev_used_mask{};

      while (true) {
        bool found{};
        for (const int m : valid_masks) {
          if (m == prev_used_mask)
            continue;
          const int gc{value ^ m};
          if (unique_grey_codes[gc])
            continue;
          value = gc;
          prev_used_mask = m;
          unique_grey_codes[gc] = 1;
          gray_codes.emplace_back(gc);
          found = true;
          break;
        }

        if (!found)
          break;

        if (gray_codes.size() == count)
          return gray_codes;
      }

    } while (next_permutation(begin(valid_masks), end(valid_masks)));

    return gray_codes;
  }
};

int main() {
  Solution s{};

  vector<int> grey_codes1{s.grayCode(2)};
  cout << "s.grayCode(2) -> " << grey_codes1 << '\n';
  vector<int> grey_codes2{s.grayCode(3)};
  cout << "s.grayCode(3) -> " << grey_codes2 << '\n';
  vector<int> grey_codes3{s.grayCode(4)};
  cout << "s.grayCode(4) -> " << grey_codes3 << '\n';

  return 0;
}

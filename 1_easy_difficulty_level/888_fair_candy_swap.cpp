/*
Alice and Bob have candy bars of different sizes: A[i] is the size of the i-th
bar of candy that Alice has, and B[j] is the size of the j-th bar of candy that
Bob has.

Since they are friends, they would like to exchange one candy bar each so that
after the exchange, they both have the same total amount of candy.  (The total
amount of candy a person has is the sum of the sizes of candy bars they have.)

Return an integer array ans where ans[0] is the size of the candy bar that Alice
must exchange, and ans[1] is the size of the candy bar that Bob must exchange.

If there are multiple answers, you may return any one of them.  It is guaranteed
an answer exists.



Example 1:

Input: A = [1,1], B = [2,2]
Output: [1,2]

Example 2:

Input: A = [1,2], B = [2,3]
Output: [1,2]

Example 3:

Input: A = [2], B = [1,3]
Output: [2,3]

Example 4:

Input: A = [1,2,5], B = [2,4]
Output: [5,4]

Note:

    1 <= A.length <= 10000
    1 <= B.length <= 10000
    1 <= A[i] <= 100000
    1 <= B[i] <= 100000
    It is guaranteed that Alice and Bob have different total amounts of candy.
    It is guaranteed there exists an answer.
*/

#include <algorithm>
#include <iostream>
#include <numeric>
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
  vector<int> fairCandySwap(vector<int>& A, vector<int>& B) {
    const size_t A_len{A.size()};
    const size_t B_len{B.size()};
    const int A_sum{accumulate(begin(A), end(A), 0)};
    const int B_sum{accumulate(begin(B), end(B), 0)};
    const int average{(A_sum + B_sum) / 2};

    vector<int>& greater_sum_elements{A_sum > average ? A : B};
    vector<int>& lower_sum_elements{A_sum < average ? A : B};
    const size_t greater_sum_elements_size{A_sum > average ? A_len : B_len};
    const int greater_sum{A_sum > average ? A_sum : B_sum};
    const int lower_sum{A_sum < average ? A_sum : B_sum};
    sort(begin(lower_sum_elements), end(lower_sum_elements));

    for (int i = greater_sum_elements_size - 1; i >= 0; i--) {
      const int missing_candy_size{average -
                                   (greater_sum - greater_sum_elements[i])};
      if (binary_search(begin(lower_sum_elements), end(lower_sum_elements),
                        missing_candy_size) &&
          (lower_sum - missing_candy_size + greater_sum_elements[i] ==
           average)) {
        if (greater_sum == A_sum)
          return {greater_sum_elements[i], missing_candy_size};
        return {missing_candy_size, greater_sum_elements[i]};
      }
    }

    return {0, 0};
  }
};

int main() {
  Solution s{};
  vector<int> a{1, 1};
  vector<int> b{2, 2};
  vector<int> swapped_candy_bars{s.fairCandySwap(a, b)};
  cout << "s.fairCandySwap([1,1], [2,2]) -> " << swapped_candy_bars
       << '\n';  // expected output: [1,2]

  a.assign({1, 2});
  b.assign({2, 3});
  swapped_candy_bars = s.fairCandySwap(a, b);
  cout << "s.fairCandySwap([1,2], [2,3]) -> " << swapped_candy_bars
       << '\n';  // expected output: [1,2]

  a.assign({2});
  b.assign({1, 3});
  swapped_candy_bars = s.fairCandySwap(a, b);
  cout << "s.fairCandySwap([2], [1,3]) -> " << swapped_candy_bars
       << '\n';  // expected output: [2,3]

  a.assign({1, 2, 5});
  b.assign({2, 4});
  swapped_candy_bars = s.fairCandySwap(a, b);
  cout << "s.fairCandySwap([1,2,5], [2,4]) -> " << swapped_candy_bars
       << '\n';  // expected output: [5,4]

  return 0;
}
/*
122. Leetcode coding challenge: Best time to buy and sell stock II

Say you have an array for which the ith element is the price of a given stock on
day i.

Design an algorithm to find the maximum profit. You may complete as many
transactions as you like (i.e., buy one and sell one share of the stock multiple
times).

Note: You may not engage in multiple transactions at the same time (i.e., you
must sell the stock before you buy again).

Example 1:

Input: [7,1,5,3,6,4]
Output: 7
Explanation: Buy on day 2 (price = 1) and sell on day 3 (price = 5), profit =
5-1 = 4. Then buy on day 4 (price = 3) and sell on day 5 (price = 6), profit =
6-3 = 3.

Example 2:

Input: [1,2,3,4,5]
Output: 4
Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit =
5-1 = 4. Note that you cannot buy on day 1, buy on day 2 and sell them later, as
you are engaging multiple transactions at the same time. You must sell before
buying again.

Example 3:

Input: [7,6,4,3,1]
Output: 0
Explanation: In this case, no transaction is done, i.e. max profit = 0.
*/

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
  static void calculate_max_profit(const vector<int>& prices,
                                   const size_t prices_len,
                                   int& max_profit,
                                   const size_t start = 0,
                                   const int profit = 0) {
    for (size_t i{start + 1}; i < prices_len; i++) {
      const int diff{prices[i] - prices[start]};
      if (diff > 0) {
        if (profit + diff > max_profit)
          max_profit = profit + diff;
        calculate_max_profit(prices, prices_len, max_profit, i + 1,
                             profit + diff);
      }

      calculate_max_profit(prices, prices_len, max_profit, i, profit);
    }
  }

 public:
  int maxProfit(const vector<int>& prices) {
    const size_t prices_len{prices.size()};
    if (prices_len < 2)
      return 0;

    int max_profit{};

    calculate_max_profit(prices, prices_len, max_profit);

    return max_profit;
  }
};

int main() {
  Solution s{};

  cout << "s.maxProfit({7,1,5,3,6,4}) -> " << s.maxProfit({7, 1, 5, 3, 6, 4})
       << '\n';  // expected output: 7
  cout << "s.maxProfit({1,2,3,4,5}) -> " << s.maxProfit({1, 2, 3, 4, 5})
       << '\n';  // expected output: 4
  cout << "s.maxProfit({7,6,4,3,1}) -> " << s.maxProfit({7, 6, 4, 3, 1})
       << '\n';  // expected output: 0
  cout << "s.maxProfit({3,2,6,5,0,3}) -> " << s.maxProfit({3, 2, 6, 5, 0, 3})
       << '\n';  // expected output: 7

  return 0;
}
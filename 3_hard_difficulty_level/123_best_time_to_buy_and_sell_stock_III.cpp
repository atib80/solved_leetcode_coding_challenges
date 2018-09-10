/*
Say you have an array for which the ith element is the price of a given stock on
day i.

Design an algorithm to find the maximum profit. You may complete at most two
transactions.

Note: You may not engage in multiple transactions at the same time (i.e., you
must sell the stock before you buy again).

Example 1:

Input: [3,3,5,0,0,3,1,4]
Output: 6
Explanation: Buy on day 4 (price = 0) and sell on day 6 (price = 3), profit =
3-0 = 3. Then buy on day 7 (price = 1) and sell on day 8 (price = 4), profit =
4-1 = 3.

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
#include <type_traits>
#include <vector>

using namespace std;

class Solution {
  template <typename IterType>
  static typename iterator_traits<IterType>::value_type
  calculate_max_profit_for_specified_interval_of_days(IterType&& start,
                                                      IterType&& last) {
    using stock_price_type = typename iterator_traits<IterType>::value_type;

    stock_price_type current_max_profit{}, current_minimum{*start};

    for (auto current{++start}; current != last; ++current) {
      const stock_price_type current_day_stock_price{*current},
          diff{current_day_stock_price - current_minimum};
      if (diff > current_max_profit)
        current_max_profit = diff;

      else if (current_day_stock_price < current_minimum)
        current_minimum = current_day_stock_price;
    }

    return current_max_profit;
  }

 public:
  int maxProfit(const vector<int>& prices) const {
    const size_t prices_len{prices.size()};
    if (prices_len < 2)
      return 0;

    int max_profit{calculate_max_profit_for_specified_interval_of_days(
        begin(prices), end(prices))};
    for (size_t i{}; i < prices_len - 1; i++) {
      for (size_t j{i + 1}; j < prices_len; j++) {
        int transaction_profit{prices[j] - prices[i]};
        if (transaction_profit <= 0)
          continue;
        transaction_profit +=
            calculate_max_profit_for_specified_interval_of_days(
                begin(prices) + j, end(prices));

        if (transaction_profit > max_profit) {
          max_profit = transaction_profit;
          break;
        }
      }
    }

    return max_profit;
  }
};

int main() {
  Solution s{};

  cout << "s.maxProfit([3,3,5,0,0,3,1,4]) -> "
       << s.maxProfit({3, 3, 5, 0, 0, 3, 1, 4}) << '\n';  // expected output: 6
  cout << "s.maxProfit([1,2,3,4,5]) -> " << s.maxProfit({1, 2, 3, 4, 5})
       << '\n';  // expected output: 4
  cout << "s.maxProfit([7,6,4,3,1]) -> " << s.maxProfit({7, 6, 4, 3, 1})
       << '\n';  // expected output: 0

  return 0;
}
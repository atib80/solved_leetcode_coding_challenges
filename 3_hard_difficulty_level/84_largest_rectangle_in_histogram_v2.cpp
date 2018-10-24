/*
Given n non-negative integers representing the histogram's bar height where the
width of each bar is 1, find the area of largest rectangle in the histogram.

Above is a histogram where width of each bar is 1, given height = [2,1,5,6,2,3].

The largest rectangle is shown in the shaded area, which has area = 10 unit.

Example:

Input: [2,1,5,6,2,3]
Output: 10
*/

#include <iostream>
#include <chrono>
#include <stack>
#include <vector>

using namespace std;

class Solution {
 public:
  Solution() { Solution::start_stop_timer(true); }

  ~Solution() {
    cout << "\nElapsed time: " << Solution::start_stop_timer() << " seconds\n";
  }

  size_t largestRectangleArea(const vector<size_t>& heights) {
    stack<size_t> s{};
    const size_t heights_size{heights.size()};
    size_t max_area{}, i{};

    while (i < heights_size) {
      if (s.empty() || heights[i] >= heights[s.top()])
        s.emplace(i++);
      else {
        const size_t top{s.top()};
        s.pop();

        size_t current_area;
        if (s.empty())
          current_area = heights[top] * i;
        else
          current_area = heights[top] * (i - s.top() - 1);

        if (current_area > max_area)
          max_area = current_area;
      }
    }

    while (!s.empty()) {
      const size_t top{s.top()};
      s.pop();

      size_t current_area;

      if (s.empty())
        current_area = heights[top] * i;
      else
        current_area = heights[top] * (i - s.top() - 1);

      if (current_area > max_area)
        max_area = current_area;
    }

    return max_area;
  }

  static double start_stop_timer(const bool is_start_timer = false) {
    static chrono::high_resolution_clock::time_point start_time;
    if (is_start_timer)
      start_time = chrono::high_resolution_clock::now();

    return chrono::duration_cast<chrono::duration<double>>(
               chrono::high_resolution_clock::now() - start_time)
        .count();
  }
};

int main() {
  Solution s{};

  vector<size_t> heights{2, 1, 5, 6, 2, 3};
  cout << "s.largestRectangleArea({2,1,5,6,2,3}) -> "
       << s.largestRectangleArea(heights) << '\n';  // expected output: 10

  return 0;
}

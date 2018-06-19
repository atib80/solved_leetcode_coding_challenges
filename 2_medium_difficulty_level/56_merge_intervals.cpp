/*
Given a collection of intervals, merge all overlapping intervals.

Example 1:

Input:  [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]
Explanation: Since intervals [1,3] and [2,6] overlaps, merge them into [1,6].

Example 2:

Input:  [[1,4],[4,5]]
Output: [[1,5]]
Explanation: Intervals [1,4] and [4,5] are considerred overlapping.
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

static int sr = []() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  return 0;
}();

struct Interval {
  int start;
  int end;
  Interval() : start{}, end{} {}
  Interval(const int s, const int e) : start{s}, end{e} {}
};

template <typename T>
ostream& operator<<(ostream& os, const vector<T>& data) {
  if (data.empty()) {
    os << "data is empty\n";
    return os;
  }
  os << '\n';
  for (size_t i{}; i < data.size(); i++)
    os << data[i] << '\n';

  return os;
}

ostream& operator<<(ostream& os, const Interval& interval) {
  os << '[' << interval.start << ',' << interval.end << ']';
  return os;
}

class Solution {
 public:
  vector<Interval> merge(vector<Interval>& intervals) {
    vector<Interval> merged_intervals{};
    const size_t intervals_size{intervals.size()};

    if (!intervals_size)
      return merged_intervals;

    if (1 == intervals_size)
      vector<Interval>{move(intervals.front())};

    sort(begin(intervals), end(intervals),
         [](const Interval& i1, const Interval& i2) {
           return i1.start < i2.start;
         });

    vector<int> visited_indices(intervals_size, 0);

    for (size_t i{}; i < intervals_size - 1; i++) {
      if (visited_indices[i])
        continue;
      for (size_t j{i + 1}; j < intervals_size; j++) {
        // if (visited_indices[j]) continue;

        if (intervals[i].end >= intervals[j].start) {
          intervals[i].end = max(intervals[i].end, intervals[j].end);
          visited_indices[j] = 1;
        } else
          break;
      }

      merged_intervals.emplace_back(move(intervals[i]));
    }

    if (!visited_indices[intervals_size - 1])
      merged_intervals.emplace_back(move(intervals[intervals_size - 1]));

    return merged_intervals;
  }
};

int main() {
  Solution s{};

  vector<Interval> input{Interval{1, 3}, Interval{2, 6}, Interval{8, 10},
                         Interval{15, 18}};
  vector<Interval> output{s.merge(input)};
  cout << output << '\n';

  input.assign({Interval{1, 4}, Interval{4, 5}});
  output = s.merge(input);
  cout << output << '\n';

  return 0;
}
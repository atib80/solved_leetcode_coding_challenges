/*
57. leetcode coding challenge: Insert Interval

Given a set of non-overlapping intervals, insert a new interval into the
intervals (merge if necessary).

You may assume that the intervals were initially sorted according to their start
times.

Example 1:

Input:  intervals = [[1,3],[6,9]], newInterval = [2,5]
Output: [[1,5],[6,9]]

Example 2:

Input:  intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
Output: [[1,2],[3,10],[12,16]]
Explanation: Because the new interval [4,8] overlaps with [3,5],[6,7],[8,10].
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
  vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
    vector<Interval> merged_intervals{};
    size_t intervals_size{intervals.size()};

    if (!intervals_size)
      return vector<Interval>{move(newInterval)};

    bool is_interval_inserted{};

    for (size_t i{}; i < intervals_size; i++) {
      if (newInterval.start < intervals[i].start) {
        intervals.insert(begin(intervals) + i, move(newInterval));
        is_interval_inserted = true;
        break;
      }
    }

    if (!is_interval_inserted)
      intervals.emplace_back(move(newInterval));

    intervals_size++;

    /*
    sort(begin(intervals), end(intervals),
         [](const Interval& i1, const Interval& i2) {
           return i1.start < i2.start;
         });
    */

    vector<int> visited_indices(intervals_size, 0);

    for (size_t i{}; i < intervals_size - 1; i++) {
      if (visited_indices[i])
        continue;
      for (size_t j{i + 1}; j < intervals_size; j++) {
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
  vector<Interval> input{Interval{1, 3}, Interval{6, 9}};
  vector<Interval> output{s.insert(input, Interval{2, 5})};
  cout << output << '\n';

  input.assign({Interval{1, 2}, Interval{3, 5}, Interval{6, 7}, Interval{8, 10},
                Interval{12, 16}});
  output = s.insert(input, Interval{4, 8});
  cout << output << '\n';

  return 0;
}

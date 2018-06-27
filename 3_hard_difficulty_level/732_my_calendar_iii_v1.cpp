/*
Implement a MyCalendarThree class to store your events. A new event can always
be added.

Your class will have one method, book2(int start, int end). Formally, this
represents a booking on the half open interval [start, end), the range of real
numbers x such that start <= x < end.

A K-booking happens when K events have some non-empty intersection (ie., there
is some time that is common to all K events.)

For each call to the method MyCalendar.book2, return an integer K representing
the largest integer such that there exists a K-booking in the calendar. Your
class will be called like this: MyCalendarThree cal = new MyCalendarThree();
MyCalendarThree.book2(start, end)

Example 1:

MyCalendarThree();
MyCalendarThree.book2(10, 20); // returns 1
MyCalendarThree.book2(50, 60); // returns 1
MyCalendarThree.book2(10, 40); // returns 2
MyCalendarThree.book2(5, 15); // returns 3
MyCalendarThree.book2(5, 10); // returns 3
MyCalendarThree.book2(25, 55); // returns 3
Explanation:
The first two events can be booked and are disjoint, so the maximum K-booking is
a 1-booking. The third event [10, 40) intersects the first event, and the
maximum K-booking is a 2-booking. The remaining events cause the maximum
K-booking to be only a 3-booking. Note that the last event locally causes a
2-booking, but the answer is still 3 because eg. [10, 20), [10, 40), and [5, 15)
are still triple booked.

Note:
The number of calls to MyCalendarThree.book2 per test case will be at most 400.
In calls to MyCalendarThree.book2(start, end), start and end are integers in the
range [0, 10^9].
*/

// #include <conio.h>
#include <stl_helper_functions.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

static int sres = []() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  return 0;
}();

template <typename ForwardIter, typename T, typename Func>
void split(ForwardIter first, ForwardIter last, const T& value, Func f) {
  if (first == last)
    return;
  while (true) {
    const ForwardIter found{find(first, last, value)};
    f(first, found);
    if (found == last)
      break;
    first = ++found;
  }
}

struct TimeInterval {
  int start;
  int end;
  int k_level;

  explicit TimeInterval(const int start_time, const int end_time, const int kl)
      : start{start_time}, end{end_time}, k_level{kl} {}
};

ostream& operator<<(ostream& os, const vector<TimeInterval>& data) {
  if (data.empty()) {
    os << "data is empty\n";
    return os;
  }
  os << '\n';
  for (const TimeInterval& ti : data)
    os << '[' << ti.start << ',' << ti.end << "]:" << ti.k_level << ", ";

  return os;
}

namespace std {
template <>
struct hash<pair<int, int>> {
  uint64_t operator()(const pair<int, int>& p) const {
    const uint64_t hash_index{(static_cast<uint64_t>(p.first) << 32) +
                              static_cast<uint64_t>(p.second)};
    return hash_index;
  }
};
}  // namespace std

class MyCalendarThree {
  int max_booking_level{};
  vector<TimeInterval> time_intervals{};
  vector<TimeInterval> precalculated_k_levels{};
  unordered_set<pair<int, int>> visited_intersections{};

 public:
  MyCalendarThree() = default;

  int book(const int start_time, const int end_time) {
    if (time_intervals.empty()) {
      time_intervals.emplace_back(start_time, end_time, 1);
      max_booking_level = 1;
      return 1;
    }
    const TimeInterval ti{start_time, end_time, 1};
    bool inserted{};

    auto lb = lower_bound(begin(time_intervals), end(time_intervals), ti,
                          [](const TimeInterval& lti, const TimeInterval& rti) {
                            return lti.start < rti.start;
                          });

    if (end(time_intervals) == lb) {
      time_intervals.emplace_back(start_time, end_time, 1);
      inserted = true;
    } else if (start_time == lb->start) {
      while (start_time == lb->start) {
        if (end_time == lb->end) {
          lb->k_level++;
          inserted = true;
          break;
        }
        ++lb;
      }
    }

    if (!inserted)
      time_intervals.emplace(lb, start_time, end_time, 1);

    for (int ri = precalculated_k_levels.size() - 1; ri >= 0; ri--) {
      const pair<int, int> intersection{
          make_pair(max(start_time, precalculated_k_levels[ri].start),
                    min(end_time, precalculated_k_levels[ri].end))};
      if (intersection.first < intersection.second) {
        const int max_booking_factor{precalculated_k_levels[ri].k_level + 1};
        if (max_booking_factor > max_booking_level) {
          max_booking_level = max_booking_factor;
          precalculated_k_levels.emplace_back(
              intersection.first, intersection.second, max_booking_factor);
          return max_booking_level;
        }

        if (max_booking_factor <= max_booking_level)
          break;
      }
    }

    visited_intersections.clear();

    for (size_t i{}; i < time_intervals.size(); i++) {
      int max_booking_factor{time_intervals[i].k_level};

      if (time_intervals[i].end <= start_time)
        continue;
      if (time_intervals[i].start >= end_time)
        break;

      pair<int, int> intersection{
          make_pair(max(start_time, time_intervals[i].start),
                    min(end_time, time_intervals[i].end))};

      if (visited_intersections.find(intersection) !=
          end(visited_intersections))
        continue;

      visited_intersections.insert(intersection);

      for (size_t j{}; j < time_intervals.size(); j++) {
        if (i == j || time_intervals[j].end <= intersection.first)
          continue;

        if (intersection.second <= time_intervals[j].start)
          break;

        intersection.first = max(intersection.first, time_intervals[j].start);
        intersection.second = min(intersection.second, time_intervals[j].end);
        max_booking_factor += time_intervals[j].k_level;
      }

      if (max_booking_factor >= max_booking_level) {
        max_booking_level = max_booking_factor;
        precalculated_k_levels.emplace_back(
            intersection.first, intersection.second, max_booking_factor);
      }
    }

    return max_booking_level;
  }
};

/**
 * Your MyCalendarThree object will be instantiated and called as such:
 * MyCalendarThree obj = new MyCalendarThree();
 * int param_1 = obj.book(start,end);
 */

int main() {
  experimental::unused_args(sres);
  MyCalendarThree calendar_tree1{};
  cout << "calendar_tree1.book(10, 20) -> " << calendar_tree1.book(10, 20)
       << '\n';  // returns 1
  cout << "calendar_tree1.book(50, 60) -> " << calendar_tree1.book(50, 60)
       << '\n';  // returns 1
  cout << "calendar_tree1.book(10, 40) -> " << calendar_tree1.book(10, 40)
       << '\n';  // returns 2
  cout << "calendar_tree1.book(5, 15) -> " << calendar_tree1.book(5, 15)
       << '\n';  // returns 3
  cout << "calendar_tree1.book(5, 10) -> " << calendar_tree1.book(5, 10)
       << '\n';  // returns 3
  cout << "calendar_tree1.book(25, 55) -> " << calendar_tree1.book(25, 55)
       << '\n';  // returns 3

  cout << '\n';

  MyCalendarThree calendar_tree2{};
  cout << "calendar_tree2.book(24, 40) -> " << calendar_tree2.book(24, 40)
       << '\n';  // returns 1
  cout << "calendar_tree2.book(43, 50) -> " << calendar_tree2.book(43, 50)
       << '\n';  // returns 1
  cout << "calendar_tree2.book(27, 43) -> " << calendar_tree2.book(27, 43)
       << '\n';  // returns 2
  cout << "calendar_tree2.book(5, 21) -> " << calendar_tree2.book(5, 21)
       << '\n';  // returns 2
  cout << "calendar_tree2.book(30, 40) -> " << calendar_tree2.book(30, 40)
       << '\n';  // returns 3
  cout << "calendar_tree2.book(14, 29) -> " << calendar_tree2.book(14, 29)
       << '\n';  // returns 3
  cout << "calendar_tree2.book(3, 19) -> " << calendar_tree2.book(3, 19)
       << '\n';  // returns 3
  cout << "calendar_tree2.book(3, 14) -> " << calendar_tree2.book(3, 14)
       << '\n';  // returns 3
  cout << "calendar_tree2.book(25, 39) -> " << calendar_tree2.book(25, 39)
       << '\n';  // returns 4
  cout << "calendar_tree2.book(6, 19) -> " << calendar_tree2.book(6, 19)
       << '\n';  // returns 4

  cout << '\n';

  MyCalendarThree calendar_tree3{};
  cout << "calendar_tree3.book(47,50) -> " << calendar_tree3.book(47, 50)
       << '\n';  // returns 1
  cout << "calendar_tree3.book(1,10) -> " << calendar_tree3.book(1, 10)
       << '\n';  // returns 1
  cout << "calendar_tree3.book(27,36) -> " << calendar_tree3.book(27, 36)
       << '\n';  // returns 1
  cout << "calendar_tree3.book(40,47) -> " << calendar_tree3.book(40, 47)
       << '\n';  // returns 1
  cout << "calendar_tree3.book(20,27) -> " << calendar_tree3.book(20, 27)
       << '\n';  // returns 1
  cout << "calendar_tree3.book(15,23) -> " << calendar_tree3.book(15, 23)
       << '\n';  // returns 2
  cout << "calendar_tree3.book(10,18) -> " << calendar_tree3.book(10, 18)
       << '\n';  // returns 2
  cout << "calendar_tree3.book(27,36) -> " << calendar_tree3.book(27, 36)
       << '\n';  // returns 2
  cout << "calendar_tree3.book(17,25) -> " << calendar_tree3.book(17, 25)
       << '\n';  // returns 3
  cout << "calendar_tree3.book(8,17) -> " << calendar_tree3.book(8, 17)
       << '\n';  // returns 3
  cout << "calendar_tree3.book(24,33) -> " << calendar_tree3.book(24, 33)
       << '\n';  // returns 3
  cout << "calendar_tree3.book(23,28) -> " << calendar_tree3.book(23, 28)
       << '\n';  // returns 4
  cout << "calendar_tree3.book(21,27) -> " << calendar_tree3.book(21, 27)
       << '\n';  // returns 5
  cout << "calendar_tree3.book(47,50) -> " << calendar_tree3.book(47, 50)
       << '\n';  // returns 5
  cout << "calendar_tree3.book(14,21) -> " << calendar_tree3.book(14, 21)
       << '\n';  // returns 5
  cout << "calendar_tree3.book(26,32) -> " << calendar_tree3.book(26, 32)
       << '\n';  // returns 5
  cout << "calendar_tree3.book(16,21) -> " << calendar_tree3.book(16, 21)
       << '\n';  // returns 5
  cout << "calendar_tree3.book(2,7) -> " << calendar_tree3.book(2, 7)
       << '\n';  // returns 5
  cout << "calendar_tree3.book(24,33) -> " << calendar_tree3.book(24, 33)
       << '\n';  // returns 6
  cout << "calendar_tree3.book(6,13) -> " << calendar_tree3.book(6, 13)
       << '\n';  // returns 6
  cout << "calendar_tree3.book(44,50) -> " << calendar_tree3.book(44, 50)
       << '\n';  // returns 6
  cout << "calendar_tree3.book(33,39) -> " << calendar_tree3.book(33, 39)
       << '\n';  // returns 6
  cout << "calendar_tree3.book(30,36) -> " << calendar_tree3.book(30, 36)
       << '\n';  // returns 6
  cout << "calendar_tree3.book(6,15) -> " << calendar_tree3.book(6, 15)
       << '\n';  // returns 6
  cout << "calendar_tree3.book(21,27) -> " << calendar_tree3.book(21, 27)
       << '\n';  // returns 7
  cout << "calendar_tree3.book(49,50) -> " << calendar_tree3.book(49, 50)
       << '\n';  // returns 7
  cout << "calendar_tree3.book(38,45) -> " << calendar_tree3.book(38, 45)
       << '\n';  // returns 7
  cout << "calendar_tree3.book(4,12) -> " << calendar_tree3.book(4, 12)
       << '\n';  // returns 7
  cout << "calendar_tree3.book(46,50) -> " << calendar_tree3.book(46, 50)
       << '\n';  // returns 7
  cout << "calendar_tree3.book(13,21) -> " << calendar_tree3.book(13, 21)
       << '\n';  // returns 7

  cout << '\n';

  MyCalendarThree calendar_tree4{};
  cout << "calendar_tree4.book(8,23) -> " << calendar_tree4.book(8, 23)
       << '\n';  // returns 1
  cout << "calendar_tree4.book(35,48) -> " << calendar_tree4.book(35, 48)
       << '\n';  // returns 1
  cout << "calendar_tree4.book(24,39) -> " << calendar_tree4.book(24, 39)
       << '\n';  // returns 2
  cout << "calendar_tree4.book(10,22) -> " << calendar_tree4.book(10, 22)
       << '\n';  // returns 2
  cout << "calendar_tree4.book(10,23) -> " << calendar_tree4.book(10, 23)
       << '\n';  // returns 3
  cout << "calendar_tree4.book(8,22) -> " << calendar_tree4.book(8, 22)
       << '\n';  // returns 4
  cout << "calendar_tree4.book(1,14) -> " << calendar_tree4.book(1, 14)
       << '\n';  // returns 5
  cout << "calendar_tree4.book(36,50) -> " << calendar_tree4.book(36, 50)
       << '\n';  // returns 5
  cout << "calendar_tree4.book(42,50) -> " << calendar_tree4.book(42, 50)
       << '\n';  // returns 5
  cout << "calendar_tree4.book(42,50) -> " << calendar_tree4.book(42, 50)
       << '\n';  // returns 5

  return 0;
}

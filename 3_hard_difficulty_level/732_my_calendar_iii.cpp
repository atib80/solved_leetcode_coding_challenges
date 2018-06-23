/*
Implement a MyCalendarThree class to store your events. A new event can always
be added.

Your class will have one method, book(int start, int end). Formally, this
represents a booking on the half open interval [start, end), the range of real
numbers x such that start <= x < end.

A K-booking happens when K events have some non-empty intersection (ie., there
is some time that is common to all K events.)

For each call to the method MyCalendar.book, return an integer K representing
the largest integer such that there exists a K-booking in the calendar. Your
class will be called like this: MyCalendarThree cal = new MyCalendarThree();
MyCalendarThree.book(start, end)

Example 1:

MyCalendarThree();
MyCalendarThree.book(10, 20); // returns 1
MyCalendarThree.book(50, 60); // returns 1
MyCalendarThree.book(10, 40); // returns 2
MyCalendarThree.book(5, 15); // returns 3
MyCalendarThree.book(5, 10); // returns 3
MyCalendarThree.book(25, 55); // returns 3
Explanation:
The first two events can be booked and are disjoint, so the maximum K-booking is
a 1-booking. The third event [10, 40) intersects the first event, and the
maximum K-booking is a 2-booking. The remaining events cause the maximum
K-booking to be only a 3-booking. Note that the last event locally causes a
2-booking, but the answer is still 3 because eg. [10, 20), [10, 40), and [5, 15)
are still triple booked.

Note:
The number of calls to MyCalendarThree.book per test case will be at most 400.
In calls to MyCalendarThree.book(start, end), start and end are integers in the
range [0, 10^9].
*/

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

static int sres = []() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  return 0;
}();

struct TimeInterval {
  int start;
  int end;

  explicit TimeInterval(const int start, const int end)
      : start{start}, end{end} {}
};

class MyCalendarThree {
  int max_booking_level{};
  vector<TimeInterval> time_intervals{};

  void find_max_booking_level_for_specified_time_interval(
      const size_t last_index,
      const int start,
      const int end,
      vector<int>& already_visited,
      int& max_booking_factor,
      const int count = 1) {
    for (size_t i{}; i < last_index; i++) {
      if (already_visited[i])
        continue;
      if ((start <= time_intervals[i].start && end > time_intervals[i].start) ||
          (start < time_intervals[i].end && end > time_intervals[i].start)) {
        already_visited[i] = 1;
        find_max_booking_level_for_specified_time_interval(
            last_index, max(start, time_intervals[i].start),
            min(end, time_intervals[i].end), already_visited,
            max_booking_factor, count + 1);
        already_visited[i] = 0;
      }
    }

    if (count > max_booking_factor)
      max_booking_factor = count;
  }

 public:
  MyCalendarThree() { time_intervals.reserve(400); }

  int book(const int start, const int end) {
    // if (start >= end) return max_booking_level;
    time_intervals.emplace_back(start, end);

    if (1 == time_intervals.size()) {
      max_booking_level = 1;
      return 1;
    }

    int count{1};
    int max_booking_factor{1};
    const size_t last_index{time_intervals.size() - 1};
    vector<int> already_visited(last_index, 0);

    for (size_t i{}; i < last_index; i++) {
      if ((start <= time_intervals[i].start && end > time_intervals[i].start) ||
          (start < time_intervals[i].end && end > time_intervals[i].start)) {
        already_visited[i] = 1;
        find_max_booking_level_for_specified_time_interval(
            last_index, max(start, time_intervals[i].start),
            min(end, time_intervals[i].end), already_visited,
            max_booking_factor, count + 1);
        already_visited[i] = 0;
      }
    }

    max_booking_level = max_booking_factor > max_booking_level
                            ? max_booking_factor
                            : max_booking_level;
    return max_booking_level;
  }
};

/**
 * Your MyCalendarThree object will be instantiated and called as such:
 * MyCalendarThree obj = new MyCalendarThree();
 * int param_1 = obj.book(start,end);
 */

int main() {
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
  cout << "calendar_tree2.book(14, 29) -> " << calendar_tree2.book(3, 19)
       << '\n';  // returns 3
  cout << "calendar_tree2.book(14, 29) -> " << calendar_tree2.book(3, 14)
       << '\n';  // returns 3
  cout << "calendar_tree2.book(14, 29) -> " << calendar_tree2.book(25, 39)
       << '\n';  // returns 4
  cout << "calendar_tree2.book(14, 29) -> " << calendar_tree2.book(6, 19)
       << '\n';  // returns 4

  return 0;
}

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
#include <algorithm>
#include <iostream>
#include <map>
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

/*
struct TimeInterval {
        int start_;
        int end_;
        int k_level_;

        explicit TimeInterval(const int start_time,
                const int end_time,
                const int k_level)
                : start_{ start_time }, end_{ end_time }, k_level_{ k_level } {}
};
*/

ostream& operator<<(ostream& os, const map<pair<int, int>, int>& data) {
  if (data.empty()) {
    os << "data is empty\n";
    return os;
  }
  os << '\n';
  for (const auto& p : data)
    os << '[' << p.first.first << ',' << p.first.second << "]:" << p.second
       << ", ";

  return os;
}

// namespace std {
//	template <>
//	struct less<pair<int, int>>
//	{
//		pair<int, int> p_;
//
//		explicit less(const pair<int, int>& p) : p_{p} noexcept { }
//
//		bool operator<(const pair<int, int>& p) const
//		noexcept
//		{
//			if (p.first < p_.first)
//				return true;
//			if (p.first == p_.first && p.second < p_.second)
//			    return true;
//			return false;
//		}
//	};
//}

class MyCalendarThree {
  int max_booking_level{};
  map<pair<int, int>, int> ti_diff{};
  vector<pair<int, int>> time_intervals{};

  void find_max_booking_factor(const size_t ti_size,
                               const int start_time,
                               const int end_time,
                               unordered_set<size_t>& visited_indices,
                               int& max_booking_factor,
                               const int iter_count = 1) {
    if (iter_count > max_booking_factor)
      max_booking_factor = iter_count;

    for (size_t i{}; i < ti_size; i++) {
      if (visited_indices.count(i))
        continue;

      if (end_time <= time_intervals[i].first)
        return;

      if (start_time >= time_intervals[i].second)
        continue;

      visited_indices.insert(i);
      const int intersect_start{max(start_time, time_intervals[i].first)};
      const int intersect_end{min(end_time, time_intervals[i].second)};
      if (intersect_start >= intersect_end) {
        visited_indices.erase(i);
        continue;
      }
      find_max_booking_factor(ti_size, intersect_start, intersect_end,
                              visited_indices, max_booking_factor,
                              iter_count + 1);
      visited_indices.erase(i);
    }
  }

 public:
  MyCalendarThree() = default;

  int book(const int start_time, const int end_time) {
    if (ti_diff.empty()) {
      const pair<int, int> key{make_pair(start_time, end_time)};
      ti_diff.insert(make_pair(key, 1));
      max_booking_level = 1;
      return 1;
    }

    const pair<int, int> key{make_pair(start_time, end_time)};
    ti_diff[key]++;

    for (const auto& f : ti_diff) {
      int max_booking_factor{f.second};
      pair<int, int> prev_intersection{
          make_pair(f.first.first, f.first.second)};

      for (const auto& s : ti_diff) {
        if (f == s)
          continue;

        if (s.first.second <= prev_intersection.first)
          continue;

        if (s.first.first >= prev_intersection.second)
          break;

        const pair<int, int> next_intersection{
            make_pair(max(prev_intersection.first, s.first.first),
                      min(prev_intersection.second, s.first.second))};

        if (next_intersection.first >= next_intersection.second)
          continue;

        prev_intersection = next_intersection;

        max_booking_factor += s.second;  // increase max_booking_factor by count
                                         // of identical time intervals
      }

      if (max_booking_factor > max_booking_level)
        max_booking_level = max_booking_factor;
    }

    return max_booking_level;
  }

  int book2(const int start_time, const int end_time) {
    if (time_intervals.empty()) {
      time_intervals.emplace_back(make_pair(start_time, end_time));
      max_booking_level = 1;
      return 1;
    }

    const size_t ti_size{time_intervals.size()};
    if (1 == ti_size) {
      if (end_time <= time_intervals.front().first ||
          start_time >= time_intervals.front().second) {
        time_intervals.emplace_back(make_pair(start_time, end_time));
        return 1;
      }

      time_intervals.emplace_back(make_pair(start_time, end_time));
      max_booking_level = 2;
      return 2;
    }

    time_intervals.emplace_back(make_pair(start_time, end_time));
    sort(begin(time_intervals), end(time_intervals));
    int max_booking_factor{max_booking_level};
    unordered_set<size_t> visited_indices{};
    for (size_t i{}; i < ti_size; i++) {
      visited_indices.insert(i);
      find_max_booking_factor(ti_size, time_intervals[i].first,
                              time_intervals[i].second, visited_indices,
                              max_booking_factor);
      visited_indices.erase(i);
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

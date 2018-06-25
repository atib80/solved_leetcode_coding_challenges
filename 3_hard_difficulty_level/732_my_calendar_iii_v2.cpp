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

#include <conio.h>
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
  unordered_set<string> skip_ti{};

  static string generate_hash_index_value(int start_time, int end_time) {
    string index{};
    index.reserve(32);

    index.clear();
    while (start_time) {
      index.insert(0, 1, start_time % 10 + '0');
      start_time /= 10;
    }

    index.push_back('-');

    const size_t next_start_pos{index.length()};

    while (end_time) {
      index.insert(next_start_pos, 1, end_time % 10 + '0');
      end_time /= 10;
    }

    return index;
  }

 public:
  MyCalendarThree() = default;

  int book(const int start_time, const int end_time) {
    // static size_t iter{};

    if (ti_diff.empty()) {
      ti_diff.insert(make_pair(make_pair(start_time, end_time), 1));
      max_booking_level = 1;
      // ++iter;
      cout << ti_diff << '\n';
      _getch();
      return 1;
    }

    // skip_ti.clear();
    // bool inserted{};
    const pair<int, int> key{make_pair(start_time, end_time)};
    ti_diff[key]++;
    int max_booking_factor{ti_diff[key]};

    for (auto& p : ti_diff) {
      // if (skip_ti.find(generate_hash_index_value(p.first.first,
      // p.first.second)) != end(skip_ti)) continue;

      if (start_time == p.first.first && end_time == p.first.second) continue;      

      /*if (end_time <= p.first.first || start_time >= p.first.second) {
        if (!max_booking_factor)
          return 1;
        return max_booking_factor;
      }
      */

      /*
      if (start_time == p.first.first && end_time == p.first.second) {
        p.second++;
        max_booking_factor += p.second;
        // if (p.second > max_booking_factor) max_booking_factor = p.second;
        // skip_ti.insert(generate_hash_index_value(start_time, end_time));
        // inserted = true;
        continue;
      }
      */

      if (start_time < p.first.first && end_time > p.first.second) {
        // p.second++;
        max_booking_factor++;
        // if (p.second > max_booking_factor) max_booking_factor = p.second;

        /*
        const pair<int, int> lower_time_interval_diff{
            make_pair(start_time, p.first.first)};

        ti_diff[lower_time_interval_diff]++;
        if (ti_diff[lower_time_interval_diff] > max_booking_factor)
          max_booking_factor = ti_diff[lower_time_interval_diff];

        skip_ti.insert(generate_hash_index_value(
            lower_time_interval_diff.first, lower_time_interval_diff.second));

        const pair<int, int> upper_time_interval_diff{
            make_pair(p.first.second, end_time)};

        ti_diff[upper_time_interval_diff]++;
        if (ti_diff[upper_time_interval_diff] > max_booking_factor)
          max_booking_factor = ti_diff[upper_time_interval_diff];
        skip_ti.insert(generate_hash_index_value(
            upper_time_interval_diff.first, upper_time_interval_diff.second));

        inserted = true;
        */
        // continue;
      }

      else if ((start_time <= p.first.first && end_time > p.first.first) ||
               (start_time < p.first.second && end_time >= p.first.second)) {
        // p.second++;
        max_booking_factor++;

        /* const pair<int, int> key{make_pair(max(p.first.first, start_time),
        min(p.first.second, end_time))}; ti_diff[key] = p.second + 1; if
        (ti_diff[key] > max_booking_factor) max_booking_factor = ti_diff[key];

        skip_ti.insert(generate_hash_index_value(key.first, key.second));

        if (start_time != p.first.first) {
          const pair<int, int> lower_time_interval_diff{make_pair(
              min(start_time, p.first.first), max(start_time, p.first.first))};

          if (start_time < p.first.first ||
              ti_diff.find(lower_time_interval_diff) != end(ti_diff))
            ti_diff[lower_time_interval_diff]++;
          else if (ti_diff.find(lower_time_interval_diff) == end(ti_diff))
            ti_diff.insert(make_pair(lower_time_interval_diff, p.second));
          if (ti_diff[lower_time_interval_diff] > max_booking_factor)
            max_booking_factor = ti_diff[lower_time_interval_diff];

          skip_ti.insert(generate_hash_index_value(
              lower_time_interval_diff.first, lower_time_interval_diff.second));
        }

        if (end_time != p.first.second) {
          const pair<int, int> upper_time_interval_diff{make_pair(
              min(end_time, p.first.second), max(end_time, p.first.second))};
          if (end_time > p.first.second ||
              ti_diff.find(upper_time_interval_diff) != end(ti_diff))
            ti_diff[upper_time_interval_diff]++;
          else if (ti_diff.find(upper_time_interval_diff) == end(ti_diff))
            ti_diff.insert(make_pair(upper_time_interval_diff, p.second));
          if (ti_diff[upper_time_interval_diff] > max_booking_factor)
            max_booking_factor = ti_diff[upper_time_interval_diff];

          skip_ti.insert(generate_hash_index_value(
              upper_time_interval_diff.first, upper_time_interval_diff.second));
          ti_diff.erase(p.first);
        }
        inserted = true;
        */
      }
    }

    /*
    if (!inserted) {
      const pair<int, int> key{make_pair(start_time, end_time)};
      ti_diff.insert(make_pair(key, 1));
      max_booking_factor++;
    }
    */

    max_booking_level = max_booking_factor > max_booking_level ? max_booking_factor : max_booking_level;

    // ++iter;
    cout << ti_diff << '\n';
    _getch();

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

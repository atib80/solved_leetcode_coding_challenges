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
#include <iostream>
#include <utility>
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
  int k_level;

  explicit TimeInterval(const int start_time, const int end_time, const int kl)
      : start{start_time}, end{end_time}, k_level{kl} {}
};

class MyCalendarThree {
  int max_booking_level{};
  vector<TimeInterval> ti_diff{};

 public:
  MyCalendarThree() { ti_diff.reserve(1024); }

  // [8,23],[35,48],[24,39],[10,22],[10,23],[8,22],[1,14],[36,50],[42,50],[42,50]

  // 1. [8,23] -> 1
  // 2. [35,48]:1 -> 1
  // 3. [8,23]:1, [24,35]:1, [35,39]:2, [39,48]:1

  int book(const int start, const int end) {
    if (ti_diff.empty()) {
      ti_diff.emplace_back(start, end, 1);
      max_booking_level = 1;
      return 1;
    }

    int max_booking_factor{1};
    bool inserted{};

    const size_t ti_diff_size{ti_diff.size()};

    for (size_t i{}; i < ti_diff_size; i++) {
      if (start == ti_diff[i].start && end == ti_diff[i].end) {
        ti_diff[i].k_level++;
        if (ti_diff[i].k_level > max_booking_factor)
          max_booking_factor = ti_diff[i].k_level;
        inserted = true;
        continue;
      }

      if (start < ti_diff[i].start && end > ti_diff[i].end) {
        ti_diff[i].k_level++;
        if (ti_diff[i].k_level > max_booking_factor)
          max_booking_factor = ti_diff[i].k_level;
        ti_diff.emplace_back(start, ti_diff[i].start, 1);
        ti_diff.emplace_back(ti_diff[i].end, end, 1);
        inserted = true;
        continue;
      }

      if ((start <= ti_diff[i].start && end > ti_diff[i].start) ||
          (start < ti_diff[i].end && end >= ti_diff[i].end)) {
        ti_diff.emplace_back(max(ti_diff[i].start, start),
                             min(ti_diff[i].end, end), ti_diff[i].k_level + 1);
        if (ti_diff[i].k_level + 1 > max_booking_factor)
          max_booking_factor = ti_diff[i].k_level + 1;
        ti_diff.emplace_back(min(start, ti_diff[i].start),
                             max(start, ti_diff[i].start), 1);
        ti_diff.emplace_back(min(end, ti_diff[i].end), max(end, ti_diff[i].end),
                             1);
        ti_diff.erase(begin(ti_diff) + i);
        inserted = true;
      }
    }

    if (!inserted)
      ti_diff.emplace_back(start, end, 1);

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
                 /*
                 ["MyCalendarThree","book","book","book","book","book","book","book","book","book","book"]
                 [[],[8,23],[35,48],[24,39],[10,22],[10,23],[8,22],[1,14],[36,50],[42,50],[42,50]]
                 Expected: [null,1,1,2,2,3,4,5,5,5,5]
                 */

  return 0;
}
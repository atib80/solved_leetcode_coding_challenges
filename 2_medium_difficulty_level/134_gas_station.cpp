/*
134. Gas station (difficulty level: medium)

There are N gas stations along a circular route, where the amount of gas at
station i is gas[i].

You have a car with an unlimited gas tank and it costs cost[i] of gas to travel
from station i to its next station (i+1). You begin the journey with an empty
tank at one of the gas stations.

Return the starting gas station's index if you can travel around the circuit
once in the clockwise direction, otherwise return -1.

Note:

    If there exists a solution, it is guaranteed to be unique.
    Both input arrays are non-empty and have the same length.
    Each element in the input arrays is a non-negative integer.

Example 1:

Input:
gas  = [1,2,3,4,5]
cost = [3,4,5,1,2]

Output: 3

Explanation:
Start at station 3 (index 3) and fill up with 4 unit of gas. Your tank = 0 + 4 =
4 Travel to station 4. Your tank = 4 - 1 + 5 = 8 Travel to station 0. Your tank
= 8 - 2 + 1 = 7 Travel to station 1. Your tank = 7 - 3 + 2 = 6 Travel to
station 2. Your tank = 6 - 4 + 3 = 5 Travel to station 3. The cost is 5. Your
gas is just enough to travel back to station 3. Therefore, return 3 as the
starting index.

Example 2:

Input:
gas  = [2,3,4]
cost = [3,4,3]

Output: -1

Explanation:
You can't start at station 0 or 1, as there is not enough gas to travel to the
next station. Let's start at station 2 and fill up with 4 unit of gas. Your tank
= 0 + 4 = 4 Travel to station 0. Your tank = 4 - 3 + 2 = 3 Travel to station 1.
Your tank = 3 - 3 + 3 = 3 You cannot travel back to station 2, as it requires 4
unit of gas but you only have 3. Therefore, you can't travel around the circuit
once no matter where you start.
*/

#include <iostream>
#include <vector>

using namespace std;

struct travel_path {
  size_t start_gas_station_index;
  size_t current_gas_station_index;
  int total_gas;
  bool out_of_gas;

  travel_path(const size_t start_index,
              const size_t current_index,
              const int gas,
              const bool no_more_gas = false)
      : start_gas_station_index{start_index},
        current_gas_station_index{current_index},
        total_gas{gas},
        out_of_gas{no_more_gas} {}
};

class Solution {
 public:
  int canCompleteCircuit(const vector<int>& gas,
                         const vector<int>& cost) const {
    const size_t count_of_gas_stations{gas.size()};

    vector<travel_path> travel_paths{};
    travel_paths.reserve(count_of_gas_stations);

    for (size_t i{}; i < count_of_gas_stations; i++)
      travel_paths.emplace_back(i, i, gas[i]);

    for (size_t c{}; c < count_of_gas_stations; c++) {
      for (size_t i{}; i < count_of_gas_stations; i++) {
        if (travel_paths[i].out_of_gas)
          continue;

        const size_t current_index{travel_paths[i].current_gas_station_index};

        if (cost[current_index] > travel_paths[i].total_gas) {
          travel_paths[i].out_of_gas = true;
          continue;
        }

        travel_paths[i].total_gas -= cost[current_index];
        const size_t next_index{
            current_index + 1 == count_of_gas_stations ? 0 : current_index + 1};

        if (next_index == travel_paths[i].start_gas_station_index)
          return next_index;

        travel_paths[i].current_gas_station_index = next_index;
        travel_paths[i].total_gas += gas[next_index];
      }
    }

    return -1;
  }
};

int main() {
  Solution s{};

  cout << "s.canCompleteCircuit([1,2,3,4,5], [3,4,5,1,2]) -> "
       << s.canCompleteCircuit({1, 2, 3, 4, 5}, {3, 4, 5, 1, 2})
       << '\n';  // expected output: 3
  cout << "s.canCompleteCircuit([2,3,4], [3,4,3]) -> "
       << s.canCompleteCircuit({2, 3, 4}, {3, 4, 3})
       << '\n';  // expected output: -1

  return 0;
}

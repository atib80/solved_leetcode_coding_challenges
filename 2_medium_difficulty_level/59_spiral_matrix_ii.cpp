/*
59. leetcode coding challenge: Spiral Matrix II

Given a positive integer n, generate a square matrix filled with elements from 1
to n2 in spiral order.

Example:

Input: 3
Output:
[
 [ 1, 2, 3 ],
 [ 8, 9, 4 ],
 [ 7, 6, 5 ]
]
*/

#include <algorithm>
#include <cstring>
#include <iostream>
#include <type_traits>
#include <vector>

using namespace std;

static int sres = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  return 0;
}();

/*
template <typename ConstCharPointerType = const char*, typename... Args>
int print(ConstCharPointerType format = "\n", Args&&... args) {
  static_assert(is_same<ConstCharPointerType, const char*>::value ||
                    is_same<ConstCharPointerType, const wchar_t*>::value,
                "Specified format parameter's type (template parameter "
                "'ConstCharPointerType') must be either const char* or const "
                "wchar_t*!");

  if constexpr (is_same<ConstCharPointerType, const char*>::value) {
    return printf(format, std::forward<Args>(args)...);
  }

  if constexpr (is_same<ConstCharPointerType, const wchar_t*>::value) {
        if (!strcmp(format, "\n")) format = L"\n";
    return wprintf(format, std::forward<Args>(args)...);
  }
}
*/

void printArgument() {
  cout << '\n';
}

template <typename T, typename... Args>
void printArgument(T&& arg, Args&&... args) {
  cout << arg << ' ';
  printArgument(args...);
}

template <typename... Args>
void print(Args&&... args) {
  printArgument(std::forward<Args>(args)...);
}

template <typename T>
ostream& operator<<(ostream& os, const vector<T>& data) {
  if (data.empty()) {
    os << "data is empty\n";
    return os;
  }
  os << "\n[";
  for (size_t i{}; i < data.size() - 1; i++)
    os << data[i] << ',';
  os << data.back() << "]\n";
  return os;
}

template <typename T>
ostream& operator<<(ostream& os, const vector<vector<T>>& data) {
  if (data.empty()) {
    os << "data is empty\n";
    return os;
  }
  os << "\n[\n";
  for (size_t i{}; i < data.size() - 1; i++) {
    os << "  [";
    for (size_t j{}; j < data[i].size() - 1; j++)
      os << data[i][j] << ',';
    os << data[i].back() << "],\n";
  }

  os << "  [";
  for (size_t j{}; j < data.back().size() - 1; j++)
    os << data.back()[j] << ',';
  os << data.back().back() << "]\n]\n";

  return os;
}

class Solution {
 public:
  vector<vector<int>> generateMatrix(const int n) {
    if (!n)
      return vector<vector<int>>{};
    if (1 == n)
      return vector<vector<int>>(1, vector<int>{1});

    if (2 == n)
      return vector<vector<int>>{{1, 2}, {4, 3}};

    vector<vector<int>> result(n, vector<int>(n));
    int min_x{}, max_x{n - 1};
    int min_y{}, max_y{n - 1};
    int x{min_x}, y{min_y};
    const int max_cells{n * n};
    int cells_visited{};

    while (true) {
      while (y <= max_y && cells_visited < max_cells) {
        result[min_x][y] = cells_visited + 1;
        cells_visited++;
        y++;
      }

      if (max_cells == cells_visited)
        break;

      min_x++;
      x = min_x;
      y = max_y;

      while (x <= max_x && cells_visited < max_cells) {
        result[x][max_y] = cells_visited + 1;
        cells_visited++;
        x++;
      }

      if (max_cells == cells_visited)
        break;

      max_y--;
      y = max_y;
      x = max_x;

      while (y >= min_y && cells_visited < max_cells) {
        result[max_x][y] = cells_visited + 1;
        cells_visited++;
        y--;
      }

      if (max_cells == cells_visited)
        break;

      max_x--;
      x = max_x;
      y = min_y;

      while (x >= min_x && cells_visited < max_cells) {
        result[x][min_y] = cells_visited + 1;
        cells_visited++;
        x--;
      }

      if (max_cells == cells_visited)
        break;

      min_y++;
      y = min_y;
      x = min_x;
    }

    return result;
  }
};

int main() {
  Solution s{};
  vector<vector<int>> output{s.generateMatrix(3)};
  cout << "s.generateMatrix(3) -> " << output << '\n';
  /*
  [
   [ 1, 2, 3 ],
   [ 8, 9, 4 ],
   [ 7, 6, 5 ]
  ]
  */
  return 0;
}

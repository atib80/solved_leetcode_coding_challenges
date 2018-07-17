/*
79. Leetcode coding challenge: Word search

Given a 2D board and a word, find if the word exists in the grid.

The word can be constructed from letters of sequentially adjacent cell, where
"adjacent" cells are those horizontally or vertically neighboring. The same
letter cell may not be used more than once.

Example:

board =
[
  ['A','B','C','E'],
  ['S','F','C','S'],
  ['A','D','E','E']
]

Given word = "ABCCED", return true.
Given word = "SEE", return true.
Given word = "ABCB", return false.
*/

#include <iomanip>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

static int sres = []() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  return 0;
}();

class Solution {
  bool search_word_in_matrix_at_specified_position(
      const vector<vector<char>>& m,
      const size_t m_width,
      const size_t m_height,
      const size_t i,
      const size_t j,
      const string& word,
      const size_t word_last,
      unordered_set<size_t>& visited_coordinates,
      const size_t offset = 0) {
    visited_coordinates.insert(i * m_width + j);

    if (offset == word_last)
      return true;

    // N direction
    if (i > 0 && offset < word_last &&
        !visited_coordinates.count((i - 1) * m_width + j) &&
        word[offset + 1] == m[i - 1][j] &&
        search_word_in_matrix_at_specified_position(
            m, m_width, m_height, i - 1, j, word, word_last,
            visited_coordinates, offset + 1))
      return true;

    // E direction
    if (j < m_width - 1 && offset < word_last &&
        !visited_coordinates.count(i * m_width + j + 1) &&
        word[offset + 1] == m[i][j + 1] &&
        search_word_in_matrix_at_specified_position(
            m, m_width, m_height, i, j + 1, word, word_last,
            visited_coordinates, offset + 1))
      return true;

    // S direction
    if (i < m_height - 1 && offset < word_last &&
        !visited_coordinates.count((i + 1) * m_width + j) &&
        word[offset + 1] == m[i + 1][j] &&
        search_word_in_matrix_at_specified_position(
            m, m_width, m_height, i + 1, j, word, word_last,
            visited_coordinates, offset + 1))
      return true;

    // W direction
    if (j > 0 && offset < word_last &&
        !visited_coordinates.count(i * m_width + j - 1) &&
        word[offset + 1] == m[i][j - 1] &&
        search_word_in_matrix_at_specified_position(
            m, m_width, m_height, i, j - 1, word, word_last,
            visited_coordinates, offset + 1))
      return true;

    visited_coordinates.erase(i * m_width + j);

    return false;
  }

 public:
  bool exist(const vector<vector<char>>& board, const string& word) {
    if (board.empty() || word.empty())
      return false;
    const size_t board_height{board.size()};
    const size_t board_width{board[0].size()};
    const size_t word_last{word.length() - 1};

    for (size_t i{}; i < board_height; i++) {
      for (size_t j{}; j < board_width; j++) {
        if (board[i][j] == word.front()) {
          unordered_set<size_t> visited_coordinates{};
          if (search_word_in_matrix_at_specified_position(
                  board, board_width, board_height, i, j, word, word_last,
                  visited_coordinates))
            return true;
        }
      }
    }

    return false;
  }
};

int main() {
  Solution s{};

  vector<vector<char>> board{
      {'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};

  cout << boolalpha << "s.exist(board, \"ABCCED\") -> "
       << s.exist(board, "ABCCED") << '\n'  // expected output: true
       << "s.exist(board, \"SEE\") -> " << s.exist(board, "SEE")
       << '\n'  // expected output: true
       << "s.exist(board, \"ABCB\") -> " << s.exist(board, "ABCB")
       << '\n';  // expected output: false

  vector<vector<char>> board2{
      {'A', 'B', 'C', 'E'}, {'S', 'F', 'E', 'S'}, {'A', 'D', 'E', 'E'}};

  // |A|B|C|E|
  // |S|F|E|S|
  // |A|D|E|E|

  // "ABCEFSADEESE"

  cout << "s.exist(board2, \"ABCEFSADEESE\") -> "
       << s.exist(board2, "ABCEFSADEESE") << '\n';

  cout << noboolalpha << '\n';

  return 0;
}

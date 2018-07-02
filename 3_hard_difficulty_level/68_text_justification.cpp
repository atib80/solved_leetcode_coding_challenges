/*
68. Leetcode coding challenge: Text justification

Given an array of words and a width maxWidth, format the text such that each
line has exactly maxWidth characters and is fully (left and right) justified.

You should pack your words in a greedy approach; that is, pack as many words as
you can in each line. Pad extra spaces ' ' when necessary so that each line has
exactly maxWidth characters.

Extra spaces between words should be distributed as evenly as possible. If the
number of spaces on a line do not divide evenly between words, the empty slots
on the left will be assigned more spaces than the slots on the right.

For the last line of text, it should be left justified and no extra space is
inserted between words.

Note:

    A word is defined as a character sequence consisting of non-space characters
only. Each word's length is guaranteed to be greater than 0 and not exceed
maxWidth. The input array words contains at least one word.

Example 1:

Input:
words = ["This", "is", "an", "example", "of", "text", "justification."]
maxWidth = 16
Output:
[
   "This    is    an",
   "example  of text",
   "justification.  "
]

Example 2:

Input:
words = ["What","must","be","acknowledgment","shall","be"]
maxWidth = 16
Output:
[
  "What   must   be",
  "acknowledgment  ",
  "shall be        "
]
Explanation: Note that the last line is "shall be    " instead of "shall be",
             because the last line must be left-justified instead of
fully-justified. Note that the second line is also left-justified becase it
contains only one word.

Example 3:

Input:
words = ["Science","is","what","we","understand","well","enough","to","explain",
         "to","a","computer.","Art","is","everything","else","we","do"]
maxWidth = 20
Output:
[
  "Science  is  what we",
  "understand      well",
  "enough to explain to",
  "a  computer.  Art is",
  "everything  else  we",
  "do                  "
]
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

static int sres = []() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  return 0;
}();

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

class Solution {
 public:
  vector<string> fullJustify(vector<string>& words, const size_t maxWidth) {
    const size_t cnt_words{words.size()};
    size_t cnt_processed_words{};

    string line{};
    line.reserve(2 * maxWidth);
    size_t index{};

    if (!cnt_words)
      return move(words);

    if (1 == cnt_words) {
      line += words[0];
      const size_t cnt_of_all_spaces{maxWidth - words[0].length()};
      if (cnt_of_all_spaces)
        line += string(cnt_of_all_spaces, ' ');
      words[0] = move(line);
      return words;
    }

    while (true) {
      size_t cnt_of_words_for_line{1};
      size_t start{cnt_processed_words};
      size_t cnt_of_letters{words[start].length()};
      size_t last{start + 1};
      for (; last < cnt_words; last++) {
        if (cnt_of_letters + cnt_of_words_for_line + words[last].length() >
            maxWidth)
          break;
        cnt_of_words_for_line++;
        cnt_of_letters += words[last].length();
      }

      cnt_processed_words += cnt_of_words_for_line;
      const bool last_line{cnt_processed_words == cnt_words};
      const size_t cnt_of_space_locations{cnt_of_words_for_line - 1};
      size_t cnt_of_all_spaces{maxWidth - cnt_of_letters};
      const size_t cnt_of_word_spaces{
          cnt_of_space_locations ? cnt_of_all_spaces / cnt_of_space_locations
                                 : cnt_of_all_spaces};
      size_t cnt_of_excess_spaces{
          cnt_of_space_locations ? cnt_of_all_spaces % cnt_of_space_locations
                                 : 0};

      line.clear();
      const string spaces_str(cnt_of_word_spaces, ' ');

      while (start < last - 1) {
        line += words[start];
        if (!last_line) {
          line += spaces_str;
          if (cnt_of_excess_spaces) {
            cnt_of_excess_spaces--;
            line.push_back(' ');
          }
        } else {
          line.push_back(' ');
          cnt_of_all_spaces--;
        }

        ++start;
      }

      line += words[start];
      if (last_line || 1 == cnt_of_words_for_line)
        line += string(cnt_of_all_spaces, ' ');

      words[index++] = move(line);

      if (last_line) {
        words.erase(begin(words) + index, end(words));
        return move(words);
      }
    }
  }
};

int main() {
  Solution s{};

  vector<string> input{"This",          "is", "an", "example", "of", "text",
                       "justification."};
  vector<string> output{s.fullJustify(input, 16)};

  cout << " s.fullJustify(input, 16) -> " << output << '\n';

  input.assign({"What", "must", "be", "acknowledgment", "shall", "be"});
  output = s.fullJustify(input, 16);

  cout << " s.fullJustify(input, 16) -> " << output << '\n';

  input.assign({"Science", "is", "what", "we", "understand", "well", "enough",
                "to", "explain", "to", "a", "computer.", "Art", "is",
                "everything", "else", "we", "do"});
  output = s.fullJustify(input, 20);

  cout << " s.fullJustify(input, 20) -> " << output << '\n';

  return 0;
}
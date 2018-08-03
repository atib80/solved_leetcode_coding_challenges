/*
157. Leetcode coding challenge: Read N Characters Given Read4

The API: int read4(char *buf) reads 4 characters at a time from a file.
The return value is the actual number of characters read. For example, it
returns 3 if there is only 3 characters left in the file. By using the read4
API, implement the function int read(char *buf, int n) that reads n characters
from the file. Note: The read function will only be called once for each test
case. Understand the problem: This seemingly easy coding question has some
tricky edge cases. When read4 returns less than 4, we know it must reached the
end of file. However, take note that read4 returning 4 could mean the last 4
bytes of the file.

To make sure that the buffer is not copied more than n bytes, copy the remaining
bytes (n – readBytes) or the number of bytes read, whichever is smaller.
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

int read4(char* buffer) {
  static ifstream input_file{"../157_read_n_characters_given_read4.cpp",
                             ios::in};
  static int offset{};
  if (!input_file)
  	throw runtime_error{"Could not open specified file!"};
  
  input_file.seekg(offset);

  if (!input_file.eof() && !input_file.fail()) {
    input_file.read(buffer, 4);
    const int count{static_cast<int>(input_file.gcount())};
    offset += count;
    return count;
  }

  return 0;
}

class Solution {
 public:
  int read(char* buf, const int n) {
    if (!buf || n < 1)
      return 0;

    char buf4[4];
    int count{};
    bool eof{};

    while (!eof && count < n) {
      int read_count{read4(buf4)};
      if (read_count < 4)
        eof = true;

      if (count + read_count > n)
        read_count = n - count;

      copy(buf4, buf4 + read_count, buf + count);
      count += read_count;
    }

    buf[n] = '\0';
    return count;
  }
};

int main() {
  Solution s{};
  char buffer[257];
  cout << "s.read(buffer, 256) -> " << s.read(buffer, 256) << '\n';

  return 0;
}
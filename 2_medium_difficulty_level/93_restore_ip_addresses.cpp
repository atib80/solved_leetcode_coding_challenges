/*
93. Leetcode coding challenge: Restore IP addresses

Given a string containing only digits, restore it by returning all possible
valid IP address combinations.

Example:

Input:  "25525511135"
Output: ["255.255.11.135", "255.255.111.35"]

Input string's length should be a value from the following valid range [4,12].
*/

#include <iostream>
#include <queue>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

template <typename T>
ostream& operator<<(ostream& os, const vector<T>& data) {
  if (data.empty()) {
    os << "data is empty\n";
    return os;
  }
  os << '[';
  for (size_t i{}; i < data.size() - 1; i++)
    os << data[i] << ", ";
  os << data.back() << ']';
  return os;
}

class Solution {
 public:
  vector<string> restoreIpAddresses(const string& s) {
    const size_t s_len{s.length()};

    if (s_len < 4 || s_len > 12)
      return vector<string>{};

    if (s == "0000")
      return vector<string>{"0.0.0.0"};

    vector<string> ip_addresses{};
    string ip_address{};
    ip_address.reserve(16);  // 111.222.111.123 + 1 = 16
    queue<tuple<size_t, size_t, string>> q{
        {make_tuple(0u, 0u, move(ip_address))}};

    while (!q.empty()) {
      size_t pos{get<0>(q.front())};
      size_t dots{get<1>(q.front())};
      string ip{move(get<2>(q.front()))};
      q.pop();

      if (dots == 3) {
        const size_t substr_len{s_len - pos};
        if (!substr_len || substr_len > 3 || (substr_len > 1 && '0' == s[pos]))
          continue;
        if (3 == substr_len) {
          const int octet_value{(s[pos] - '0') * 100 + (s[pos + 1] - '0') * 10 +
                                s[pos + 2] - '0'};
          if (octet_value > 255)
            continue;
        }

        ip.push_back('.');
        ip += s.substr(pos);
        ip_addresses.emplace_back(move(ip));
        continue;
      }

      size_t unused_digits_len{s_len - pos};

      string ip_part{ip};

      if (unused_digits_len > 0) {
        if (dots > 0)
          ip_part.push_back('.');
        ip_part.push_back(s[pos]);
        q.emplace(make_tuple(pos + 1, dots + 1, ip_part));
        ip_part.pop_back();
      }

      if (unused_digits_len > 1 && '0' != s[pos]) {
        ip_part.push_back(s[pos]);
        ip_part.push_back(s[pos + 1]);
        q.emplace(make_tuple(pos + 2, dots + 1, ip_part));
        ip_part.pop_back();
        ip_part.pop_back();
      }

      if (unused_digits_len > 2 && '0' != s[pos]) {
        const int octet_value{(s[pos] - '0') * 100 + (s[pos + 1] - '0') * 10 +
                              s[pos + 2] - '0'};
        if (octet_value < 256) {
          ip_part.push_back(s[pos]);
          ip_part.push_back(s[pos + 1]);
          ip_part.push_back(s[pos + 2]);
          q.emplace(make_tuple(pos + 3, dots + 1, move(ip_part)));
        }
      }
    }

    return ip_addresses;
  }
};

int main() {
  Solution s{};

  vector<string> output{s.restoreIpAddresses("25525511135")};
  cout << "s.restoreIpAddresses(\"25525511135\") -> " << output
       << '\n';  // expected output: [255.255.11.135, 255.255.111.35]

  output = s.restoreIpAddresses("12345");
  cout << "s.restoreIpAddresses(\"12345\") -> " << output
       << '\n';  // expected output: [1.2.3.45, 1.2.34.5, 1.23.4.5, 12.3.4.5]

  output = s.restoreIpAddresses("0000");
  cout << "s.restoreIpAddresses(\"0000\") -> " << output
       << '\n';  // expected output: [0.0.0.0]

  output = s.restoreIpAddresses("010010");
  cout << "s.restoreIpAddresses(\"010010\") -> " << output
       << '\n';  // expected output: [0.10.0.10, 0.100.1.0]

  return 0;
}

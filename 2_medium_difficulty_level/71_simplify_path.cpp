/*
Given an absolute path for a file (Unix-style), simplify it.

For example,
path = "/home/", => "/home"
path = "/a/./b/../../c/", => "/c"

Corner Cases:

    Did you consider the case where path = "/../"?
    In this case, you should return "/".
    Another corner case is the path might contain multiple slashes '/' together,
such as "/home//foo/". In this case, you should ignore redundant slashes and
return "/home/foo".
*/

#include <iostream>
#include <string>
#include <string_view>

using namespace std;

static int sres = []() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  return 0;
}();

class Solution {
 public:
  string simplifyPath(string path) {
    size_t path_len{path.length()};
    size_t start{};
    string absolute_path{};
    absolute_path.reserve(path_len);

    while ('/' == path[start])
      ++start;

    while (start < path_len) {
      size_t next{path.find('/', start)};

      if (string::npos == next || path_len - 1 == next) {
        if (string::npos == next) {
          path.push_back('/');
          next = path_len;
          path_len++;
        }

        const string_view path_segment(&path[start], next - start);
        if (".." == path_segment) {
          if (absolute_path.empty() || "/" == absolute_path)
            return string(1, '/');
          const size_t pos{absolute_path.rfind('/')};
          if (!pos)
            return string(1, '/');
          absolute_path.erase(pos);
          return absolute_path;
        } else if ("." == path_segment) {
          if (absolute_path.empty() || "/" == absolute_path)
            return string(1, '/');
          return absolute_path;
        } else {
          absolute_path.push_back('/');
          for (size_t i{start}; i < next; i++)
            absolute_path.push_back(path[i]);
          return absolute_path;
        }
      }

      const string_view path_segment(&path[start], next - start);

      if (".." == path_segment) {
        const size_t pos{absolute_path.rfind('/')};
        if (string::npos != pos)
          absolute_path.erase(pos);
      } else if ("." != path_segment) {
        absolute_path.push_back('/');
        for (size_t i{start}; i < next; i++)
          absolute_path.push_back(path[i]);
      }

      start = next + 1;
      while ('/' == path[start])
        start++;
    }

    if (absolute_path.empty())
      return string(1, '/');

    return absolute_path;
  }
};

int main() {
  Solution s{};

  cout << "s.simplifyPath(\"/home/\") -> " << s.simplifyPath(string{"/home/"})
       << '\n';  // expected output: "/home"
  cout << "s.simplifyPath(\"/a/./b/../../c/\") -> "
       << s.simplifyPath(string{"/a/./b/../../c/"})
       << '\n';  // expected output: "/c"
  cout << "s.simplifyPath(\"/home//foo/\") -> "
       << s.simplifyPath(string{"/home//foo/"})
       << '\n';  // expected output: "/home/foo"
  cout << "s.simplifyPath(\"/../\") -> " << s.simplifyPath(string{"/../"})
       << '\n';  // expected output: "/"
  cout << "s.simplifyPath(\"/..\") -> " << s.simplifyPath(string{"/.."})
       << '\n';  // expected output: "/"
  cout << "s.simplifyPath(\"/./\") -> " << s.simplifyPath(string{"/./"})
       << '\n';  // expected output: "/"
  cout << "s.simplifyPath(\"/.\") -> " << s.simplifyPath(string{"/."})
       << '\n';  // expected output: "/"
  cout << "s.simplifyPath(\"/home/../../..\") -> "
       << s.simplifyPath(string{"/home/../../.."})
       << '\n';  // expected output: "/"
  cout << "s.simplifyPath(\"/\") -> " << s.simplifyPath(string{"/"})
       << '\n';  // expected output: "/"
  cout << "s.simplifyPath(\"/...\") -> " << s.simplifyPath(string{"/..."})
       << '\n';  // expected output: "/..."
  cout << "s.simplifyPath(\"///TJbrd/owxdG//\") -> "
       << s.simplifyPath(string{"///TJbrd/owxdG//"})
       << '\n';  // expected output: "/TJbrd/owxdG"

  return 0;
}
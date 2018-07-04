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

using namespace std;

class Solution {
 public:
  string simplifyPath(string path) {
    if ("/../" == path || "/./" == path)
      return "/";

    size_t path_len{path.length()};
    size_t start{1};
    string absolute_path{};
    absolute_path.reserve(path_len);

    while (start < path_len) {
      size_t next{path.find('/', start)};

      if (string::npos == next || path_len - 1 == next) {
        if (string::npos == next) {
          path.push_back('/');
          next = path_len;
          path_len++;
        }
        if ('.' == path[next - 2] && '.' == path[next - 1]) {
          const size_t pos{absolute_path.rfind('/')};
          if (!pos)
            return string(1, '/');
          absolute_path.erase(pos);
          return absolute_path;
        } else if ('.' == path[next])
          return absolute_path;
        else {
          absolute_path.push_back('/');
          for (size_t i{start}; i < next; i++)
            absolute_path.push_back(path[i]);
          return absolute_path;
        }
      }

      if ('.' == path[next - 1] && '.' == path[next - 2]) {
        const size_t pos{absolute_path.rfind('/')};
        absolute_path.erase(pos);
      } else if ('.' != path[next - 1]) {
        absolute_path.push_back('/');
        for (size_t i{start}; i < next; i++)
          absolute_path.push_back(path[i]);
      }

      start = next + 1;
      while ('/' == path[start])
        start++;
    }

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
  cout << "s.simplifyPath(\"/../\") -> " << s.simplifyPath(string{"/../"})
       << '\n';  // expected output: "/"
  cout << "s.simplifyPath(\"/home//foo/\") -> "
       << s.simplifyPath(string{"/home//foo/"})
       << '\n';  // expected output: "/home/foo"

  return 0;
}
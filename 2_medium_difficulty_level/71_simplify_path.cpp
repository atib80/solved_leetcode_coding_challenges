/*
Given an absolute path for a file (Unix-style), simplify it.

For example,
path = "/home/", => "/home"
path = "/a/./b/../../c/", => "/c"
/c



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

static int sres = []() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  return 0;
}();

class Solution {
 public:
  string simplifyPath(string path) {

    if ('/' != path.back())
      path.push_back('/');
    const size_t path_len{path.length()};
    string apsolute_path(1, '/');
    apsolute_path.reserve(path_len);

    size_t start{};

    while (true) {
      while ('/' == path[start] && start < path_len)
        ++start;

      if (start >= path_len) {
        if ('/' == apsolute_path.back() && apsolute_path.length() > 1)
          apsolute_path.pop_back();
        return apsolute_path;
      }

      size_t next{path.find('/', start)};

      const string path_segment{path.substr(start, next - start)};

      if (".." == path_segment && apsolute_path.length() > 1) {
        const size_t pos{apsolute_path.rfind('/', apsolute_path.length() - 2)};
        if (string::npos != pos)
          apsolute_path.erase(pos + 1);
      } else if ("." != path_segment) {
        apsolute_path.append(move(path_segment));
        apsolute_path.push_back('/');
      }

      start = next + 1;
    }

    return apsolute_path;
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
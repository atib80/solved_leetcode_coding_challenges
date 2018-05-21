/*
Leetcode coding challenge: Substring with concatenation of all words
(iterative solution implemented by using queue)

You are given a string, s, and a list of words, words, that are all of the same
length. Find all starting indices of substring(s) in s that is a concatenation
of each word in words exactly once and without any intervening characters.

Example 1:

Input:
  s = "barfoothefoobarman",
  words = ["foo","bar"]

Output: [0,9]

Explanation: Substrings starting at index 0 and 9 are "barfoor" and "foobar"
respectively. The output order does not matter, returning [9,0] is fine too.

Example 2:

Input:
  s = "wordgoodstudentgoodword",
  words = ["word","student"]

Output: []
*/

#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> findSubstring(const string& s, vector<string>& words) {
    vector<int> start_indices{};
    const size_t s_len{s.length()};
    const size_t words_count{words.size()};

    if (0 == words_count || !s_len)
      return {};

    if (1 == words_count) {
      if (s == words[0])
        return {0};
      size_t offset{};

      const string& word{words.front()};

      while ((offset = s.find(word, offset)) != string::npos) {
        start_indices.emplace_back(offset);
        offset++;
      }

      return start_indices;
    }

    size_t words_substr_len{};
    for_each(cbegin(words), cend(words),
             [&words_substr_len](const string& word) {
               words_substr_len += word.length();
             });

    if (s_len < words_substr_len)
      return {};

    unordered_set<string> unique_words_set(begin(words), end(words));
    vector<string> unique_words(begin(unique_words_set), end(unique_words_set));
    const size_t unique_words_size{unique_words.size()};

    if (unique_words_size < 4) {
      sort(begin(unique_words), end(unique_words));
      bool found_needle{};
      do {
        string needle{unique_words.front()};

        for (size_t i{1}; i < unique_words_size; i++) {
          needle += unique_words[i];
        }

        if (string::npos != s.find(needle)) {
          found_needle = true;
          break;
        }

      } while (next_permutation(begin(unique_words), end(unique_words)));

      if (!found_needle)
        return {};
    }

    unordered_set<string> already_visited_words{};

    for (size_t i{}; i < words_count; i++) {
      const string& word{words[i]};
      if (already_visited_words.find(word) != end(already_visited_words))
        continue;
      already_visited_words.insert(word);
      size_t prev_word_start{};
      while ((prev_word_start = s.find(word, prev_word_start)) !=
             string::npos) {
        if (prev_word_start + words_substr_len > s_len)
          break;
        const size_t first_word_start_index{prev_word_start};
        queue<pair<size_t, unordered_set<size_t>>> q{{make_pair(
            prev_word_start + word.length(), unordered_set<size_t>{i})}};

        bool found_substring{};

        while (!q.empty()) {
          const size_t next_word_start{q.front().first};
          unordered_set<size_t> visited_words{move(q.front().second)};
          q.pop();

          for (size_t j{}; j < words_count; j++) {
            if (visited_words.count(j))
              continue;
            visited_words.insert(j);
            const string& next_word{words[j]};
            const size_t word_len{next_word.length()};
            bool not_found{};
            for (size_t m{next_word_start}, n{}; n < word_len; m++, n++) {
              if (s[m] != next_word[n]) {
                not_found = true;
                break;
              }
            }

            if (!not_found) {
              if (visited_words.size() == words.size()) {
                start_indices.emplace_back(first_word_start_index);
                found_substring = true;
                break;
              }

              q.emplace(
                  make_pair(next_word_start + word_len, move(visited_words)));
            }

            visited_words.erase(j);
          }

          if (found_substring)
            break;
        }

        prev_word_start++;
      }
    }

    return start_indices;
  }
};

int main() {
  const string s{
      "pjzkrkevzztxductzzxmxsvwjkxpvukmfjywwetvfnujhweiybwvvsrfequzkhossmootkmy"
      "xgjgfordrpapjuunmqnxxdrqrfgkrsjqbszgiqlcfnrpjlcwdrvbumtotzylshdvccdmsqoa"
      "dfrpsvnwpizlwszrtyclhgilklydbmfhuywotjmktnwrfvizvnmfvvqfiokkdprznnnjyctt"
      "prkxpuykhmpchiksyucbmtabiqkisgbhxngmhezrrqvayfsxauampdpxtafniiwfvdufhtwa"
      "jrbkxtjzqjnfocdhekumttuqwovfjrgulhekcpjszyynadxhnttgmnxkduqmmyhzfnjhduce"
      "sctufqbumxbamalqudeibljgbspeotkgvddcwgxidaiqcvgwykhbysjzlzfbupkqunuqtrax"
      "rlptivshhbihtsigtpipguhbhctcvubnhqipncyxfjebdnjyetnlnvmuxhzsdahkrscewabe"
      "jifmxombiamxvauuitoltyymsarqcuuoezcbqpdaprxmsrickwpgwpsoplhugbikbkotzrtq"
      "kscekkgwjycfnvwfgdzogjzjvpcvixnsqsxacfwndzvrwrycwxrcismdhqapoojegggkocyr"
      "dtkzmiekhxoppctytvphjynrhtcvxcobxbcjjivtfjiwmduhzjokkbctweqtigwfhzorjlkp"
      "uuliaipbtfldinyetoybvugevwvhhhweejogrghllsouipabfafcxnhukcbtmxzshoyyufjh"
      "zadhrelweszbfgwpkzlwxkogyogutscvuhcllphshivnoteztpxsaoaacgxyaztuixhunrow"
      "zljqfqrahosheukhahhbiaxqzfmmwcjxountkevsvpbzjnilwpoermxrtlfroqoclexxisrd"
      "hvfsindffslyekrzwzqkpeocilatftymodgztjgybtyheqgcpwogdcjlnlesefgvimwbxcbz"
      "vaibspdjnrpqtyeilkcspknyylbwndvkffmzuriilxagyerjptbgeqgebiaqnvdubrtxibhv"
      "akcyotkfonmseszhczapxdlauexehhaireihxsplgdgmxfvaevrbadbwjbdrkfbbjjkgcztk"
      "cbwagtcnrtqryuqixtzhaakjlurnumzyovawrcjiwabuwretmdamfkxrgqgcdgbrdbnugzec"
      "bgyxxdqmisaqcyjkqrntxqmdrczxbebemcblftxplafnyoxqimkhcykwamvdsxjezkpgdpvo"
      "pddptdfbprjustquhlazkjfluxrzopqdstulybnqvyknrchbphcarknnhhovweaqawdyxsqs"
      "qahkepluypwrzjegqtdoxfgzdkydeoxvrfhxusrujnmjzqrrlxglcmkiykldbiasnhrjbjek"
      "ystzilrwkzhontwmehrfsrzfaqrbbxncphbzuuxeteshyrveamjsfiaharkcqxefghgceeix"
      "kdgkuboupxnwhnfigpkwnqdvzlydpidcljmflbccarbiegsmweklwngvygbqpescpeichmfi"
      "dgsjmkvkofvkuehsmkkbocgejoiqcnafvuokelwuqsgkyoekaroptuvekfvmtxtqshcwsztk"
      "rzwrpabqrrhnlerxjojemcxel"};

  vector<string> words{"dhvf", "sind", "ffsl", "yekr", "zwzq", "kpeo",
                       "cila", "tfty", "modg", "ztjg", "ybty", "heqg",
                       "cpwo", "gdcj", "lnle", "sefg", "vimw", "bxcb"};
  /*
  const string s{
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababababababab"
      "abababababababababababababababababababababababababababababababab"};
  vector<string> words{"ab", "ba", "ab", "ba", "ab", "ba", "ab", "ba",
                       "ab", "ba", "ab", "ba", "ab", "ba", "ab", "ba",
                       "ab", "ba", "ab", "ba", "ab", "ba"};

  */

  // const string s{"barfoothefoobarman"};
  // vector<string> words{"foo","bar"};

  Solution solution{};

  const vector<int> result{solution.findSubstring(s, words)};

  if (!result.empty()) {
    for (size_t i{}; i < result.size() - 1; i++)
      cout << result[i] << ',';
    cout << result.back() << '\n';
  }

  return 0;
}

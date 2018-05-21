/*
Leetcode coding challenge: Substring with concatenation of all words

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
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
  bool find_all_start_indices_of_substring(const string& s,
                                           const vector<string>& words,
                                           const size_t words_count,
                                           unordered_set<size_t>& visited_words,
                                           vector<int>& start_indices,
                                           const size_t prev_word_end_pos,
                                           const int first_word_start_index) {
    for (size_t i{}; i < words_count; i++) {
      if (visited_words.count(i))
        continue;

      visited_words.insert(i);
      const string& word{words[i]};
      const size_t word_len{words[i].length()};
      bool not_found{};
      for (size_t j{prev_word_end_pos}, k{}; k < word_len; j++, k++) {
        if (s[j] != word[k]) {
          not_found = true;
          break;
        }
      }

      if (!not_found) {
        if (visited_words.size() == words.size()) {
          start_indices.emplace_back(first_word_start_index);
          visited_words.erase(i);
          return true;
        }

        if (find_all_start_indices_of_substring(
                s, words, words_count, visited_words, start_indices,
                prev_word_end_pos + word_len, first_word_start_index)) {
          visited_words.erase(i);
          return true;
        }
      }

      visited_words.erase(i);
    }

    return false;
  }

 public:
  vector<int> findSubstring(const string& s, vector<string>& words) {
    vector<int> start_indices{};
    unordered_set<size_t> visited_words{};
    const size_t s_len{s.length()};
    const size_t words_count{words.size()};

    if (0 == words_count || !s_len)
      return {};

    if (1 == words_count) {
      if (s == words[0])
        return {0};
      size_t offset{};

      while (string::npos != (offset = s.find(words[0], offset))) {
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
      while (string::npos !=
             (prev_word_start = s.find(word, prev_word_start))) {
        if (prev_word_start + words_substr_len > s_len)
          break;
        visited_words.insert(i);
        find_all_start_indices_of_substring(
            s, words, words_count, visited_words, start_indices,
            prev_word_start + word.length(), prev_word_start);
        prev_word_start++;
      }
      visited_words.erase(i);
    }

    return start_indices;
  }
};

int main() {
  /*
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
                 */

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

  // const string s{"barfoothefoobarman"};
  // vector<string> words{"foo","bar"};

  Solution solution{};

  const auto result = solution.findSubstring(s, words);
  cout << '\n';
  for (const auto index : result)
    cout << index << ',';
  cout << '\n';

  return 0;
}

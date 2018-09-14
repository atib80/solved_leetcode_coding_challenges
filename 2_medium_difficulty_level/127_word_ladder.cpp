/*
127. Word ladder (difficulty level: medium)

Given two words (beginWord and endWord), and a dictionary's word list, find the
length of shortest transformation sequence from beginWord to endWord, such that:

    Only one letter can be changed at a time.
    Each transformed word must exist in the word list. Note that beginWord is
not a transformed word.

Note:

    Return 0 if there is no such transformation sequence.
    All words have the same length.
    All words contain only lowercase alphabetic characters.
    You may assume no duplicates in the word list.
    You may assume beginWord and endWord are non-empty and are not the same.

Example 1:

Input:
beginWord = "hit",
endWord = "cog",
wordList = ["hot","dot","dog","lot","log","cog"]

Output: 5

Explanation: As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog"
-> "cog", return its length 5.

Example 2:

Input:
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log"]

Output: 0

Explanation: The endWord "cog" is not in wordList, therefore no possible
transformation.
*/

#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
  vector<string> words_;
  vector<int> visited_word_indices_;
  unordered_set<string> skip_words_;
  string begin_word_;
  string end_word_;
  size_t words_size_;

  static bool check_if_given_two_words_only_differ_in_one_char(
      const string& lw,
      const string& rw) {
    size_t diff_count{};

    for (size_t i{}; i < lw.length(); i++) {
      if (lw[i] != rw[i]) {
        ++diff_count;
        if (diff_count > 1)
          return false;
      }
    }

    return 1 == diff_count;
  }

  void find_minimum_number_of_transformation_sequences(
      const size_t current_pos,
      size_t& minimum_number_of_steps,
      bool& found_seq,
      const size_t step_count) {
    if (step_count + 1 >= minimum_number_of_steps)
      return;

    if (check_if_given_two_words_only_differ_in_one_char(words_[current_pos],
                                                         end_word_)) {
      minimum_number_of_steps = step_count + 1;
      found_seq = true;
      return;
    }

    for (size_t i{}; i < words_size_; ++i) {
      if (visited_word_indices_[i])
        continue;

      if (check_if_given_two_words_only_differ_in_one_char(words_[current_pos],
                                                           words_[i]) &&
          skip_words_.find(words_[i]) == end(skip_words_)) {
        if (end_word_ == words_[i]) {
          minimum_number_of_steps = step_count + 1;
          found_seq = true;
          return;
        }

        visited_word_indices_[i] = 1;
        find_minimum_number_of_transformation_sequences(
            i, minimum_number_of_steps, found_seq, step_count + 1);
        visited_word_indices_[i] = 0;
      }
    }
  }

 public:
  size_t ladderLength(string beginWord,
                      string endWord,
                      vector<string>& wordList) {
    begin_word_ = move(beginWord);
    end_word_ = move(endWord);
    if (begin_word_ == end_word_)
      return 0;
    words_ = move(wordList);
    words_size_ = words_.size();
    visited_word_indices_.clear();
    visited_word_indices_.resize(words_size_);
    words_.emplace_back(begin_word_);
    skip_words_.clear();
    skip_words_.insert(begin_word_);

    bool end_word_found{};
    const int word_len = end_word_.length();

    for (const auto& w : words_) {
      if (w.front() == end_word_.front() && w.back() == end_word_.back()) {
        end_word_found = true;
        for (int i{1}; i < word_len - 1; ++i) {
          if (w[i] != end_word_[i]) {
            end_word_found = false;
            break;
          }
        }

        if (end_word_found)
          break;
      }
    }

    if (!end_word_found)
      return 0;

    size_t minimum_number_of_steps{string::npos};

    for (size_t i{}; i < words_size_; ++i) {
      if (begin_word_ == words_[i])
        continue;

      if (check_if_given_two_words_only_differ_in_one_char(begin_word_,
                                                           words_[i])) {
        if (end_word_ == words_[i])
          return 2;

        visited_word_indices_[i] = 1;
        bool found_seq{};

        find_minimum_number_of_transformation_sequences(
            i, minimum_number_of_steps, found_seq, 2);
        if (!found_seq)
          skip_words_.insert(words_[i]);
        visited_word_indices_[i] = 0;
      }
    }

    return minimum_number_of_steps != string::npos ? minimum_number_of_steps
                                                   : 0;
  }
};

int main() {
  Solution s{};

  vector<string> words_list1{"hot", "dot", "dog", "lot", "log", "cog"};
  cout << "s.ladderLength(hit, cog, [hot, dot, dog, lot, log, cog]) -> "
       << s.ladderLength("hit", "cog", words_list1)
       << '\n';  // expected output: 5

  vector<string> words_list2{"hot", "dot", "dog", "lot", "log"};
  cout << "s.ladderLength(hit, cog, [hot, dot, dog, lot, log]) -> "
       << s.ladderLength("hit", "cog", words_list2)
       << '\n';  // expected output: 0

  // vector<string> words_list3{
  //     "kid", "tag", "pup", "ail", "tun", "woo", "erg", "luz", "brr", "gay",
  //     "sip", "kay", "per", "val", "mes", "ohs", "now", "boa", "cet", "pal",
  //     "bar", "die", "war", "hay", "eco", "pub", "lob", "rue", "fry", "lit",
  //     "rex", "jan", "cot", "bid", "ali", "pay", "col", "gum", "ger", "row",
  //     "won", "dan", "rum", "fad", "tut", "sag", "yip", "sui", "ark", "has",
  //     "zip", "fez", "own", "ump", "dis", "ads", "max", "jaw", "out", "btu",
  //     "ana", "gap", "cry", "led", "abe", "box", "ore", "pig", "fie", "toy",
  //     "fat", "cal", "lie", "noh", "sew", "ono", "tam", "flu", "mgm", "ply",
  //     "awe", "pry", "tit", "tie", "yet", "too", "tax", "jim", "san", "pan",
  //     "map", "ski", "ova", "wed", "non", "wac", "nut", "why", "bye", "lye",
  //     "oct", "old", "fin", "feb", "chi", "sap", "owl", "log", "tod", "dot",
  //     "bow", "fob", "for", "joe", "ivy", "fan", "age", "fax", "hip", "jib",
  //     "mel", "hus", "sob", "ifs", "tab", "ara", "dab", "jag", "jar", "arm",
  //     "lot", "tom", "sax", "tex", "yum", "pei", "wen", "wry", "ire", "irk",
  //     "far", "mew", "wit", "doe", "gas", "rte", "ian", "pot", "ask", "wag",
  //     "hag", "amy", "nag", "ron", "soy", "gin", "don", "tug", "fay", "vic",
  //     "boo", "nam", "ave", "buy", "sop", "but", "orb", "fen", "paw", "his",
  //     "sub", "bob", "yea", "oft", "inn", "rod", "yam", "pew", "web", "hod",
  //     "hun", "gyp", "wei", "wis", "rob", "gad", "pie", "mon", "dog", "bib",
  //     "rub", "ere", "dig", "era", "cat", "fox", "bee", "mod", "day", "apr",
  //     "vie", "nev", "jam", "pam", "new", "aye", "ani", "and", "ibm", "yap",
  //     "can", "pyx", "tar", "kin", "fog", "hum", "pip", "cup", "dye", "lyx",
  //     "jog", "nun", "par", "wan", "fey", "bus", "oak", "bad", "ats", "set",
  //     "qom", "vat", "eat", "pus", "rev", "axe", "ion", "six", "ila", "lao",
  //     "mom", "mas", "pro", "few", "opt", "poe", "art", "ash", "oar", "cap",
  //     "lop", "may", "shy", "rid", "bat", "sum", "rim", "fee", "bmw", "sky",
  //     "maj", "hue", "thy", "ava", "rap", "den", "fla", "auk", "cox", "ibo",
  //     "hey", "saw", "vim", "sec", "ltd", "you", "its", "tat", "dew", "eva",
  //     "tog", "ram", "let", "see", "zit", "maw", "nix", "ate", "gig", "rep",
  //     "owe", "ind", "hog", "eve", "sam", "zoo", "any", "dow", "cod", "bed",
  //     "vet", "ham", "sis", "hex", "via", "fir", "nod", "mao", "aug", "mum",
  //     "hoe", "bah", "hal", "keg", "hew", "zed", "tow", "gog", "ass", "dem",
  //     "who", "bet", "gos", "son", "ear", "spy", "kit", "boy", "due", "sen",
  //     "oaf", "mix", "hep", "fur", "ada", "bin", "nil", "mia", "ewe", "hit",
  //     "fix", "sad", "rib", "eye", "hop", "haw", "wax", "mid", "tad", "ken",
  //     "wad", "rye", "pap", "bog", "gut", "ito", "woe", "our", "ado", "sin",
  //     "mad", "ray", "hon", "roy", "dip", "hen", "iva", "lug", "asp", "hui",
  //     "yak", "bay", "poi", "yep", "bun", "try", "lad", "elm", "nat", "wyo",
  //     "gym", "dug", "toe", "dee", "wig", "sly", "rip", "geo", "cog", "pas",
  //     "zen", "odd", "nan", "lay", "pod", "fit", "hem", "joy", "bum", "rio",
  //     "yon", "dec", "leg", "put", "sue", "dim", "pet", "yaw", "nub", "bit",
  //     "bur", "sid", "sun", "oil", "red", "doc", "moe", "caw", "eel", "dix",
  //     "cub", "end", "gem", "off", "yew", "hug", "pop", "tub", "sgt", "lid",
  //     "pun", "ton", "sol", "din", "yup", "jab", "pea", "bug", "gag", "mil",
  //     "jig", "hub", "low", "did", "tin", "get", "gte", "sox", "lei", "mig",
  //     "fig", "lon", "use", "ban", "flo", "nov", "jut", "bag", "mir", "sty",
  //     "lap", "two", "ins", "con", "ant", "net", "tux", "ode", "stu", "mug",
  //     "cad", "nap", "gun", "fop", "tot", "sow", "sal", "sic", "ted", "wot",
  //     "del", "imp", "cob", "way", "ann", "tan", "mci", "job", "wet", "ism",
  //     "err", "him", "all", "pad", "hah", "hie", "aim", "ike", "jed", "ego",
  //     "mac", "baa", "min", "com", "ill", "was", "cab", "ago", "ina", "big",
  //     "ilk", "gal", "tap", "duh", "ola", "ran", "lab", "top", "gob", "hot",
  //     "ora", "tia", "kip", "han", "met", "hut", "she", "sac", "fed", "goo",
  //     "tee", "ell", "not", "act", "gil", "rut", "ala", "ape", "rig", "cid",
  //     "god", "duo", "lin", "aid", "gel", "awl", "lag", "elf", "liz", "ref",
  //     "aha", "fib", "oho", "tho", "her", "nor", "ace", "adz", "fun", "ned",
  //     "coo", "win", "tao", "coy", "van", "man", "pit", "guy", "foe", "hid",
  //     "mai", "sup", "jay", "hob", "mow", "jot", "are", "pol", "arc", "lax",
  //     "aft", "alb", "len", "air", "pug", "pox", "vow", "got", "meg", "zoe",
  //     "amp", "ale", "bud", "gee", "pin", "dun", "pat", "ten", "mob"};

  // cout << "s.ladderLength(cet, ism, words_list3) -> "
  //      << s.ladderLength("cet", "ism", words_list3)
  //      << '\n';

  return 0;
}

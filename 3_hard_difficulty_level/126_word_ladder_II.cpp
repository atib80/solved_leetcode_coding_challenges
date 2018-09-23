/*
126. Word ladder II (difficulty level: hard)

Given two words (beginWord and endWord), and a dictionary's word list, find all
shortest transformation sequence(s) from beginWord to endWord, such that:

  Only one letter can be changed at a time
  Each transformed word must exist in the word list. Note that beginWord is
not a transformed word.

Note:

  Return an empty list if there is no such transformation sequence.
  All words have the same length.
  All words contain only lowercase alphabetic characters.
  You may assume no duplicates in the word list.
  You may assume beginWord and endWord are non-empty and are not the same.

Example 1:

Input:
beginWord = "hit",
endWord = "cog",
wordList = ["hot","dot","dog","lot","log","cog"]

Output:
[
  ["hit","hot","dot","dog","cog"],
  ["hit","hot","lot","log","cog"]
]

Example 2:

Input:
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log"]

Output: []

Explanation: The endWord "cog" is not in wordList, therefore no possible
transformation.
*/

#include <algorithm>
#include <chrono>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

template <typename T>
ostream& operator<<(ostream& os, const vector<T>& data) {
  if (data.empty()) {
    os << "\n  []";
    return os;
  }
  os << "\n[";
  for (size_t i{}; i < data.size() - 1; i++)
    os << data[i] << ',';
  os << data.back() << ']';
  return os;
}

template <typename T>
ostream& operator<<(ostream& os, const vector<vector<T>>& data) {
  if (data.empty()) {
    os << "[[]]\n";
    return os;
  }

  os << "\n[";
  for (const auto& row : data)
    os << row;
  os << "\n]\n";

  return os;
}

class Solution {
  vector<string> current_sequence_;
  vector<vector<string>> found_sequences_;
  unordered_set<string> word_dict_;
  vector<unordered_map<string, vector<char>>> substr_key_existing_chars_dict;
  string begin_word_;
  string end_word_;
  size_t word_len_{};
  size_t min_ladder_length_{};

  size_t get_count_of_different_chars(const string& str) const {
    size_t diff_count{};

    for (size_t i{}; i < word_len_; ++i) {
      if (str[i] != begin_word_[i])
        diff_count++;
    }

    return diff_count;
  }

  size_t find_min_ladder_length() {
    queue<string> q{{begin_word_}};

    size_t min_seq_len{2};

    while (!q.empty()) {
      const size_t q_len{q.size()};
      for (size_t i{}; i < q_len; i++) {
        string next_word{move(q.front())};
        q.pop();
        for (size_t j{}; j < next_word.length(); j++) {
          const char temp_char{next_word[j]};
          for (char ch{'a'}; ch <= 'z'; ch++) {
            next_word[j] = ch;
            if (word_dict_.find(next_word) != end(word_dict_)) {
              if (end_word_ == next_word)
                return min_seq_len;
              word_dict_.erase(next_word);
              q.emplace(next_word);
            }
          }

          next_word[j] = temp_char;
        }
      }

      min_seq_len++;
    }

    return 0;
  }

  void find_minimum_number_of_transformation_sequences(
      string& current_word,
      string& key,
      const size_t step_count) {
    if (step_count + get_count_of_different_chars(current_word) >
        min_ladder_length_)
      return;

    for (size_t i{}; i < current_word.length(); ++i) {
      const char orig_char{current_word[i]};
      key.clear();
      for (size_t j{}; j < word_len_; ++j) {
        if (i == j)
          continue;
        key.push_back(current_word[j]);
      }

      vector<char>& chars{substr_key_existing_chars_dict[i].at(key)};

      for (char& visited_ch : chars) {
        if (!visited_ch || orig_char == visited_ch)
          continue;
        current_word[i] = visited_ch;
        if (current_word == begin_word_) {
          current_sequence_.emplace_back(begin_word_);
          reverse(begin(current_sequence_), end(current_sequence_));
          found_sequences_.emplace_back(current_sequence_);
          reverse(begin(current_sequence_), end(current_sequence_));
          current_sequence_.pop_back();
          current_word[i] = orig_char;
          return;
        }

        visited_ch = 0;
        current_sequence_.emplace_back(current_word);
        find_minimum_number_of_transformation_sequences(current_word, key,
                                                        step_count + 1);
        current_sequence_.pop_back();
        visited_ch = current_word[i];
      }

      current_word[i] = orig_char;
    }
  }

 public:
  static double start_stop_timer(const bool is_start_timer = false) {
    static chrono::high_resolution_clock::time_point start_time;
    if (is_start_timer)
      start_time = chrono::high_resolution_clock::now();

    return chrono::duration_cast<chrono::duration<double>>(
               chrono::high_resolution_clock::now() - start_time)
        .count();
  }

  vector<vector<string>> findLadders(string begin_word,
                                     string end_word,
                                     const vector<string>& word_list) {
    vector<vector<string>> result_set{};
    begin_word_ = move(begin_word);
    end_word_ = move(end_word);
    word_dict_.clear();
    word_dict_.insert(cbegin(word_list), cend(word_list));
    if (word_dict_.find(end_word_) == end(word_dict_))
      return {};

    const bool begin_word_found{word_dict_.find(begin_word_) !=
                                end(word_dict_)};
    word_dict_.erase(begin_word_);

    min_ladder_length_ = find_min_ladder_length();

    if (!min_ladder_length_)
      return {};
    if (2 == min_ladder_length_)
      return {{begin_word_, end_word_}};

    current_sequence_.clear();
    current_sequence_.emplace_back(end_word_);
    found_sequences_.clear();

    word_len_ = begin_word_.length();

    substr_key_existing_chars_dict.clear();
    substr_key_existing_chars_dict.resize(
        word_len_, unordered_map<string, vector<char>>{});

    string key{};
    key.reserve(word_len_);

    for (const string& w : word_list) {
      for (size_t i{}; i < word_len_; ++i) {
        key.clear();
        for (size_t j{}; j < word_len_; ++j) {
          if (i == j)
            continue;
          key.push_back(w[j]);
        }

        substr_key_existing_chars_dict[i][key].emplace_back(w[i]);
      }
    }

    if (!begin_word_found) {
      for (size_t i{}; i < word_len_; ++i) {
        key.clear();
        for (size_t j{}; j < word_len_; ++j) {
          if (i == j)
            continue;
          key.push_back(begin_word_[j]);
        }

        substr_key_existing_chars_dict[i][key].emplace_back(begin_word_[i]);
      }
    }

    find_minimum_number_of_transformation_sequences(end_word_, key, 1);

    return move(found_sequences_);
  }
};

int main() {
  Solution s{};

  Solution::start_stop_timer(true);

  vector<string> words_list1{"hot", "dot", "dog", "lot", "log", "cog"};
  const vector<vector<string>> output1{
      s.findLadders("hit", "cog", words_list1)};
  cout << "s.findLadders(hit, cog, [hot, dot, dog, lot, log, cog]) -> "
       << output1 << '\n';  // expected output: [[hit,hot,dot,dog,cog],
  // [hit,hot,lot,log,cog]]

  vector<string> words_list2{"hot", "dot", "dog", "lot", "log"};
  const vector<vector<string>> output2{
      s.findLadders("hit", "cog", words_list2)};
  cout << "s.findLadders(hit, cog, [hot, dot, dog, lot, log]) -> " << output2
       << '\n';  // expected output: [[]]

  vector<string> words_list3{
      "kid", "tag", "pup", "ail", "tun", "woo", "erg", "luz", "brr", "gay",
      "sip", "kay", "per", "val", "mes", "ohs", "now", "boa", "cet", "pal",
      "bar", "die", "war", "hay", "eco", "pub", "lob", "rue", "fry", "lit",
      "rex", "jan", "cot", "bid", "ali", "pay", "col", "gum", "ger", "row",
      "won", "dan", "rum", "fad", "tut", "sag", "yip", "sui", "ark", "has",
      "zip", "fez", "own", "ump", "dis", "ads", "max", "jaw", "out", "btu",
      "ana", "gap", "cry", "led", "abe", "box", "ore", "pig", "fie", "toy",
      "fat", "cal", "lie", "noh", "sew", "ono", "tam", "flu", "mgm", "ply",
      "awe", "pry", "tit", "tie", "yet", "too", "tax", "jim", "san", "pan",
      "map", "ski", "ova", "wed", "non", "wac", "nut", "why", "bye", "lye",
      "oct", "old", "fin", "feb", "chi", "sap", "owl", "log", "tod", "dot",
      "bow", "fob", "for", "joe", "ivy", "fan", "age", "fax", "hip", "jib",
      "mel", "hus", "sob", "ifs", "tab", "ara", "dab", "jag", "jar", "arm",
      "lot", "tom", "sax", "tex", "yum", "pei", "wen", "wry", "ire", "irk",
      "far", "mew", "wit", "doe", "gas", "rte", "ian", "pot", "ask", "wag",
      "hag", "amy", "nag", "ron", "soy", "gin", "don", "tug", "fay", "vic",
      "boo", "nam", "ave", "buy", "sop", "but", "orb", "fen", "paw", "his",
      "sub", "bob", "yea", "oft", "inn", "rod", "yam", "pew", "web", "hod",
      "hun", "gyp", "wei", "wis", "rob", "gad", "pie", "mon", "dog", "bib",
      "rub", "ere", "dig", "era", "cat", "fox", "bee", "mod", "day", "apr",
      "vie", "nev", "jam", "pam", "new", "aye", "ani", "and", "ibm", "yap",
      "can", "pyx", "tar", "kin", "fog", "hum", "pip", "cup", "dye", "lyx",
      "jog", "nun", "par", "wan", "fey", "bus", "oak", "bad", "ats", "set",
      "qom", "vat", "eat", "pus", "rev", "axe", "ion", "six", "ila", "lao",
      "mom", "mas", "pro", "few", "opt", "poe", "art", "ash", "oar", "cap",
      "lop", "may", "shy", "rid", "bat", "sum", "rim", "fee", "bmw", "sky",
      "maj", "hue", "thy", "ava", "rap", "den", "fla", "auk", "cox", "ibo",
      "hey", "saw", "vim", "sec", "ltd", "you", "its", "tat", "dew", "eva",
      "tog", "ram", "let", "see", "zit", "maw", "nix", "ate", "gig", "rep",
      "owe", "ind", "hog", "eve", "sam", "zoo", "any", "dow", "cod", "bed",
      "vet", "ham", "sis", "hex", "via", "fir", "nod", "mao", "aug", "mum",
      "hoe", "bah", "hal", "keg", "hew", "zed", "tow", "gog", "ass", "dem",
      "who", "bet", "gos", "son", "ear", "spy", "kit", "boy", "due", "sen",
      "oaf", "mix", "hep", "fur", "ada", "bin", "nil", "mia", "ewe", "hit",
      "fix", "sad", "rib", "eye", "hop", "haw", "wax", "mid", "tad", "ken",
      "wad", "rye", "pap", "bog", "gut", "ito", "woe", "our", "ado", "sin",
      "mad", "ray", "hon", "roy", "dip", "hen", "iva", "lug", "asp", "hui",
      "yak", "bay", "poi", "yep", "bun", "try", "lad", "elm", "nat", "wyo",
      "gym", "dug", "toe", "dee", "wig", "sly", "rip", "geo", "cog", "pas",
      "zen", "odd", "nan", "lay", "pod", "fit", "hem", "joy", "bum", "rio",
      "yon", "dec", "leg", "put", "sue", "dim", "pet", "yaw", "nub", "bit",
      "bur", "sid", "sun", "oil", "red", "doc", "moe", "caw", "eel", "dix",
      "cub", "end", "gem", "off", "yew", "hug", "pop", "tub", "sgt", "lid",
      "pun", "ton", "sol", "din", "yup", "jab", "pea", "bug", "gag", "mil",
      "jig", "hub", "low", "did", "tin", "get", "gte", "sox", "lei", "mig",
      "fig", "lon", "use", "ban", "flo", "nov", "jut", "bag", "mir", "sty",
      "lap", "two", "ins", "con", "ant", "net", "tux", "ode", "stu", "mug",
      "cad", "nap", "gun", "fop", "tot", "sow", "sal", "sic", "ted", "wot",
      "del", "imp", "cob", "way", "ann", "tan", "mci", "job", "wet", "ism",
      "err", "him", "all", "pad", "hah", "hie", "aim", "ike", "jed", "ego",
      "mac", "baa", "min", "com", "ill", "was", "cab", "ago", "ina", "big",
      "ilk", "gal", "tap", "duh", "ola", "ran", "lab", "top", "gob", "hot",
      "ora", "tia", "kip", "han", "met", "hut", "she", "sac", "fed", "goo",
      "tee", "ell", "not", "act", "gil", "rut", "ala", "ape", "rig", "cid",
      "god", "duo", "lin", "aid", "gel", "awl", "lag", "elf", "liz", "ref",
      "aha", "fib", "oho", "tho", "her", "nor", "ace", "adz", "fun", "ned",
      "coo", "win", "tao", "coy", "van", "man", "pit", "guy", "foe", "hid",
      "mai", "sup", "jay", "hob", "mow", "jot", "are", "pol", "arc", "lax",
      "aft", "alb", "len", "air", "pug", "pox", "vow", "got", "meg", "zoe",
      "amp", "ale", "bud", "gee", "pin", "dun", "pat", "ten", "mob"};
  const vector<vector<string>> output3{
      s.findLadders("cet", "ism", words_list3)};
  cout << "s.findLadders(cet, ism, words_list3) -> " << output3
       << '\n';  // expected output:
                 // [[cet,get,gee,gte,ate,ats,its,ito,ibo,ibm,ism],
                 // [cet,cat,can,ian,inn,ins,its,ito,ibo,ibm,ism],
                 // [cet,cot,con,ion,inn,ins,its,ito,ibo,ibm,ism]]

  vector<string> word_list4{
      "slit", "bunk", "wars", "ping", "viva", "wynn", "wows", "irks", "gang",
      "pool", "mock", "fort", "heel", "send", "ship", "cols", "alec", "foal",
      "nabs", "gaze", "giza", "mays", "dogs", "karo", "cums", "jedi", "webb",
      "lend", "mire", "jose", "catt", "grow", "toss", "magi", "leis", "bead",
      "kara", "hoof", "than", "ires", "baas", "vein", "kari", "riga", "oars",
      "gags", "thug", "yawn", "wive", "view", "germ", "flab", "july", "tuck",
      "rory", "bean", "feed", "rhee", "jeez", "gobs", "lath", "desk", "yoko",
      "cute", "zeus", "thus", "dims", "link", "dirt", "mara", "disc", "limy",
      "lewd", "maud", "duly", "elsa", "hart", "rays", "rues", "camp", "lack",
      "okra", "tome", "math", "plug", "monk", "orly", "friz", "hogs", "yoda",
      "poop", "tick", "plod", "cloy", "pees", "imps", "lead", "pope", "mall",
      "frey", "been", "plea", "poll", "male", "teak", "soho", "glob", "bell",
      "mary", "hail", "scan", "yips", "like", "mull", "kory", "odor", "byte",
      "kaye", "word", "honk", "asks", "slid", "hopi", "toke", "gore", "flew",
      "tins", "mown", "oise", "hall", "vega", "sing", "fool", "boat", "bobs",
      "lain", "soft", "hard", "rots", "sees", "apex", "chan", "told", "woos",
      "unit", "scow", "gilt", "beef", "jars", "tyre", "imus", "neon", "soap",
      "dabs", "rein", "ovid", "hose", "husk", "loll", "asia", "cope", "tail",
      "hazy", "clad", "lash", "sags", "moll", "eddy", "fuel", "lift", "flog",
      "land", "sigh", "saks", "sail", "hook", "visa", "tier", "maws", "roeg",
      "gila", "eyes", "noah", "hypo", "tore", "eggs", "rove", "chap", "room",
      "wait", "lurk", "race", "host", "dada", "lola", "gabs", "sobs", "joel",
      "keck", "axed", "mead", "gust", "laid", "ends", "oort", "nose", "peer",
      "kept", "abet", "iran", "mick", "dead", "hags", "tens", "gown", "sick",
      "odis", "miro", "bill", "fawn", "sumo", "kilt", "huge", "ores", "oran",
      "flag", "tost", "seth", "sift", "poet", "reds", "pips", "cape", "togo",
      "wale", "limn", "toll", "ploy", "inns", "snag", "hoes", "jerk", "flux",
      "fido", "zane", "arab", "gamy", "raze", "lank", "hurt", "rail", "hind",
      "hoot", "dogy", "away", "pest", "hoed", "pose", "lose", "pole", "alva",
      "dino", "kind", "clan", "dips", "soup", "veto", "edna", "damp", "gush",
      "amen", "wits", "pubs", "fuzz", "cash", "pine", "trod", "gunk", "nude",
      "lost", "rite", "cory", "walt", "mica", "cart", "avow", "wind", "book",
      "leon", "life", "bang", "draw", "leek", "skis", "dram", "ripe", "mine",
      "urea", "tiff", "over", "gale", "weir", "defy", "norm", "tull", "whiz",
      "gill", "ward", "crag", "when", "mill", "firs", "sans", "flue", "reid",
      "ekes", "jain", "mutt", "hems", "laps", "piss", "pall", "rowe", "prey",
      "cull", "knew", "size", "wets", "hurl", "wont", "suva", "girt", "prys",
      "prow", "warn", "naps", "gong", "thru", "livy", "boar", "sade", "amok",
      "vice", "slat", "emir", "jade", "karl", "loyd", "cerf", "bess", "loss",
      "rums", "lats", "bode", "subs", "muss", "maim", "kits", "thin", "york",
      "punt", "gays", "alpo", "aids", "drag", "eras", "mats", "pyre", "clot",
      "step", "oath", "lout", "wary", "carp", "hums", "tang", "pout", "whip",
      "fled", "omar", "such", "kano", "jake", "stan", "loop", "fuss", "mini",
      "byrd", "exit", "fizz", "lire", "emil", "prop", "noes", "awed", "gift",
      "soli", "sale", "gage", "orin", "slur", "limp", "saar", "arks", "mast",
      "gnat", "port", "into", "geed", "pave", "awls", "cent", "cunt", "full",
      "dint", "hank", "mate", "coin", "tars", "scud", "veer", "coax", "bops",
      "uris", "loom", "shod", "crib", "lids", "drys", "fish", "edit", "dick",
      "erna", "else", "hahs", "alga", "moho", "wire", "fora", "tums", "ruth",
      "bets", "duns", "mold", "mush", "swop", "ruby", "bolt", "nave", "kite",
      "ahem", "brad", "tern", "nips", "whew", "bait", "ooze", "gino", "yuck",
      "drum", "shoe", "lobe", "dusk", "cult", "paws", "anew", "dado", "nook",
      "half", "lams", "rich", "cato", "java", "kemp", "vain", "fees", "sham",
      "auks", "gish", "fire", "elam", "salt", "sour", "loth", "whit", "yogi",
      "shes", "scam", "yous", "lucy", "inez", "geld", "whig", "thee", "kelp",
      "loaf", "harm", "tomb", "ever", "airs", "page", "laud", "stun", "paid",
      "goop", "cobs", "judy", "grab", "doha", "crew", "item", "fogs", "tong",
      "blip", "vest", "bran", "wend", "bawl", "feel", "jets", "mixt", "tell",
      "dire", "devi", "milo", "deng", "yews", "weak", "mark", "doug", "fare",
      "rigs", "poke", "hies", "sian", "suez", "quip", "kens", "lass", "zips",
      "elva", "brat", "cosy", "teri", "hull", "spun", "russ", "pupa", "weed",
      "pulp", "main", "grim", "hone", "cord", "barf", "olav", "gaps", "rote",
      "wilt", "lars", "roll", "balm", "jana", "give", "eire", "faun", "suck",
      "kegs", "nita", "weer", "tush", "spry", "loge", "nays", "heir", "dope",
      "roar", "peep", "nags", "ates", "bane", "seas", "sign", "fred", "they",
      "lien", "kiev", "fops", "said", "lawn", "lind", "miff", "mass", "trig",
      "sins", "furl", "ruin", "sent", "cray", "maya", "clog", "puns", "silk",
      "axis", "grog", "jots", "dyer", "mope", "rand", "vend", "keen", "chou",
      "dose", "rain", "eats", "sped", "maui", "evan", "time", "todd", "skit",
      "lief", "sops", "outs", "moot", "faze", "biro", "gook", "fill", "oval",
      "skew", "veil", "born", "slob", "hyde", "twin", "eloy", "beat", "ergs",
      "sure", "kobe", "eggo", "hens", "jive", "flax", "mons", "dunk", "yest",
      "begs", "dial", "lodz", "burp", "pile", "much", "dock", "rene", "sago",
      "racy", "have", "yalu", "glow", "move", "peps", "hods", "kins", "salk",
      "hand", "cons", "dare", "myra", "sega", "type", "mari", "pelt", "hula",
      "gulf", "jugs", "flay", "fest", "spat", "toms", "zeno", "taps", "deny",
      "swag", "afro", "baud", "jabs", "smut", "egos", "lara", "toes", "song",
      "fray", "luis", "brut", "olen", "mere", "ruff", "slum", "glad", "buds",
      "silt", "rued", "gelt", "hive", "teem", "ides", "sink", "ands", "wisp",
      "omen", "lyre", "yuks", "curb", "loam", "darn", "liar", "pugs", "pane",
      "carl", "sang", "scar", "zeds", "claw", "berg", "hits", "mile", "lite",
      "khan", "erik", "slug", "loon", "dena", "ruse", "talk", "tusk", "gaol",
      "tads", "beds", "sock", "howe", "gave", "snob", "ahab", "part", "meir",
      "jell", "stir", "tels", "spit", "hash", "omit", "jinx", "lyra", "puck",
      "laue", "beep", "eros", "owed", "cede", "brew", "slue", "mitt", "jest",
      "lynx", "wads", "gena", "dank", "volt", "gray", "pony", "veld", "bask",
      "fens", "argo", "work", "taxi", "afar", "boon", "lube", "pass", "lazy",
      "mist", "blot", "mach", "poky", "rams", "sits", "rend", "dome", "pray",
      "duck", "hers", "lure", "keep", "gory", "chat", "runt", "jams", "lays",
      "posy", "bats", "hoff", "rock", "keri", "raul", "yves", "lama", "ramp",
      "vote", "jody", "pock", "gist", "sass", "iago", "coos", "rank", "lowe",
      "vows", "koch", "taco", "jinn", "juno", "rape", "band", "aces", "goal",
      "huck", "lila", "tuft", "swan", "blab", "leda", "gems", "hide", "tack",
      "porn", "scum", "frat", "plum", "duds", "shad", "arms", "pare", "chin",
      "gain", "knee", "foot", "line", "dove", "vera", "jays", "fund", "reno",
      "skid", "boys", "corn", "gwyn", "sash", "weld", "ruiz", "dior", "jess",
      "leaf", "pars", "cote", "zing", "scat", "nice", "dart", "only", "owls",
      "hike", "trey", "whys", "ding", "klan", "ross", "barb", "ants", "lean",
      "dopy", "hock", "tour", "grip", "aldo", "whim", "prom", "rear", "dins",
      "duff", "dell", "loch", "lava", "sung", "yank", "thar", "curl", "venn",
      "blow", "pomp", "heat", "trap", "dali", "nets", "seen", "gash", "twig",
      "dads", "emmy", "rhea", "navy", "haws", "mite", "bows", "alas", "ives",
      "play", "soon", "doll", "chum", "ajar", "foam", "call", "puke", "kris",
      "wily", "came", "ales", "reef", "raid", "diet", "prod", "prut", "loot",
      "soar", "coed", "celt", "seam", "dray", "lump", "jags", "nods", "sole",
      "kink", "peso", "howl", "cost", "tsar", "uric", "sore", "woes", "sewn",
      "sake", "cask", "caps", "burl", "tame", "bulk", "neva", "from", "meet",
      "webs", "spar", "fuck", "buoy", "wept", "west", "dual", "pica", "sold",
      "seed", "gads", "riff", "neck", "deed", "rudy", "drop", "vale", "flit",
      "romp", "peak", "jape", "jews", "fain", "dens", "hugo", "elba", "mink",
      "town", "clam", "feud", "fern", "dung", "newt", "mime", "deem", "inti",
      "gigs", "sosa", "lope", "lard", "cara", "smug", "lego", "flex", "doth",
      "paar", "moon", "wren", "tale", "kant", "eels", "muck", "toga", "zens",
      "lops", "duet", "coil", "gall", "teal", "glib", "muir", "ails", "boer",
      "them", "rake", "conn", "neat", "frog", "trip", "coma", "must", "mono",
      "lira", "craw", "sled", "wear", "toby", "reel", "hips", "nate", "pump",
      "mont", "died", "moss", "lair", "jibe", "oils", "pied", "hobs", "cads",
      "haze", "muse", "cogs", "figs", "cues", "roes", "whet", "boru", "cozy",
      "amos", "tans", "news", "hake", "cots", "boas", "tutu", "wavy", "pipe",
      "typo", "albs", "boom", "dyke", "wail", "woke", "ware", "rita", "fail",
      "slab", "owes", "jane", "rack", "hell", "lags", "mend", "mask", "hume",
      "wane", "acne", "team", "holy", "runs", "exes", "dole", "trim", "zola",
      "trek", "puma", "wacs", "veep", "yaps", "sums", "lush", "tubs", "most",
      "witt", "bong", "rule", "hear", "awry", "sots", "nils", "bash", "gasp",
      "inch", "pens", "fies", "juts", "pate", "vine", "zulu", "this", "bare",
      "veal", "josh", "reek", "ours", "cowl", "club", "farm", "teat", "coat",
      "dish", "fore", "weft", "exam", "vlad", "floe", "beak", "lane", "ella",
      "warp", "goth", "ming", "pits", "rent", "tito", "wish", "amps", "says",
      "hawk", "ways", "punk", "nark", "cagy", "east", "paul", "bose", "solo",
      "teed", "text", "hews", "snip", "lips", "emit", "orgy", "icon", "tuna",
      "soul", "kurd", "clod", "calk", "aunt", "bake", "copy", "acid", "duse",
      "kiln", "spec", "fans", "bani", "irma", "pads", "batu", "logo", "pack",
      "oder", "atop", "funk", "gide", "bede", "bibs", "taut", "guns", "dana",
      "puff", "lyme", "flat", "lake", "june", "sets", "gull", "hops", "earn",
      "clip", "fell", "kama", "seal", "diaz", "cite", "chew", "cuba", "bury",
      "yard", "bank", "byes", "apia", "cree", "nosh", "judo", "walk", "tape",
      "taro", "boot", "cods", "lade", "cong", "deft", "slim", "jeri", "rile",
      "park", "aeon", "fact", "slow", "goff", "cane", "earp", "tart", "does",
      "acts", "hope", "cant", "buts", "shin", "dude", "ergo", "mode", "gene",
      "lept", "chen", "beta", "eden", "pang", "saab", "fang", "whir", "cove",
      "perk", "fads", "rugs", "herb", "putt", "nous", "vane", "corm", "stay",
      "bids", "vela", "roof", "isms", "sics", "gone", "swum", "wiry", "cram",
      "rink", "pert", "heap", "sikh", "dais", "cell", "peel", "nuke", "buss",
      "rasp", "none", "slut", "bent", "dams", "serb", "dork", "bays", "kale",
      "cora", "wake", "welt", "rind", "trot", "sloe", "pity", "rout", "eves",
      "fats", "furs", "pogo", "beth", "hued", "edam", "iamb", "glee", "lute",
      "keel", "airy", "easy", "tire", "rube", "bogy", "sine", "chop", "rood",
      "elbe", "mike", "garb", "jill", "gaul", "chit", "dons", "bars", "ride",
      "beck", "toad", "make", "head", "suds", "pike", "snot", "swat", "peed",
      "same", "gaza", "lent", "gait", "gael", "elks", "hang", "nerf", "rosy",
      "shut", "glop", "pain", "dion", "deaf", "hero", "doer", "wost", "wage",
      "wash", "pats", "narc", "ions", "dice", "quay", "vied", "eons", "case",
      "pour", "urns", "reva", "rags", "aden", "bone", "rang", "aura", "iraq",
      "toot", "rome", "hals", "megs", "pond", "john", "yeps", "pawl", "warm",
      "bird", "tint", "jowl", "gibe", "come", "hold", "pail", "wipe", "bike",
      "rips", "eery", "kent", "hims", "inks", "fink", "mott", "ices", "macy",
      "serf", "keys", "tarp", "cops", "sods", "feet", "tear", "benz", "buys",
      "colo", "boil", "sews", "enos", "watt", "pull", "brag", "cork", "save",
      "mint", "feat", "jamb", "rubs", "roxy", "toys", "nosy", "yowl", "tamp",
      "lobs", "foul", "doom", "sown", "pigs", "hemp", "fame", "boor", "cube",
      "tops", "loco", "lads", "eyre", "alta", "aged", "flop", "pram", "lesa",
      "sawn", "plow", "aral", "load", "lied", "pled", "boob", "bert", "rows",
      "zits", "rick", "hint", "dido", "fist", "marc", "wuss", "node", "smog",
      "nora", "shim", "glut", "bale", "perl", "what", "tort", "meek", "brie",
      "bind", "cake", "psst", "dour", "jove", "tree", "chip", "stud", "thou",
      "mobs", "sows", "opts", "diva", "perm", "wise", "cuds", "sols", "alan",
      "mild", "pure", "gail", "wins", "offs", "nile", "yelp", "minn", "tors",
      "tran", "homy", "sadr", "erse", "nero", "scab", "finn", "mich", "turd",
      "then", "poem", "noun", "oxus", "brow", "door", "saws", "eben", "wart",
      "wand", "rosa", "left", "lina", "cabs", "rapt", "olin", "suet", "kalb",
      "mans", "dawn", "riel", "temp", "chug", "peal", "drew", "null", "hath",
      "many", "took", "fond", "gate", "sate", "leak", "zany", "vans", "mart",
      "hess", "home", "long", "dirk", "bile", "lace", "moog", "axes", "zone",
      "fork", "duct", "rico", "rife", "deep", "tiny", "hugh", "bilk", "waft",
      "swig", "pans", "with", "kern", "busy", "film", "lulu", "king", "lord",
      "veda", "tray", "legs", "soot", "ells", "wasp", "hunt", "earl", "ouch",
      "diem", "yell", "pegs", "blvd", "polk", "soda", "zorn", "liza", "slop",
      "week", "kill", "rusk", "eric", "sump", "haul", "rims", "crop", "blob",
      "face", "bins", "read", "care", "pele", "ritz", "beau", "golf", "drip",
      "dike", "stab", "jibs", "hove", "junk", "hoax", "tats", "fief", "quad",
      "peat", "ream", "hats", "root", "flak", "grit", "clap", "pugh", "bosh",
      "lock", "mute", "crow", "iced", "lisa", "bela", "fems", "oxes", "vies",
      "gybe", "huff", "bull", "cuss", "sunk", "pups", "fobs", "turf", "sect",
      "atom", "debt", "sane", "writ", "anon", "mayo", "aria", "seer", "thor",
      "brim", "gawk", "jack", "jazz", "menu", "yolk", "surf", "libs", "lets",
      "bans", "toil", "open", "aced", "poor", "mess", "wham", "fran", "gina",
      "dote", "love", "mood", "pale", "reps", "ines", "shot", "alar", "twit",
      "site", "dill", "yoga", "sear", "vamp", "abel", "lieu", "cuff", "orbs",
      "rose", "tank", "gape", "guam", "adar", "vole", "your", "dean", "dear",
      "hebe", "crab", "hump", "mole", "vase", "rode", "dash", "sera", "balk",
      "lela", "inca", "gaea", "bush", "loud", "pies", "aide", "blew", "mien",
      "side", "kerr", "ring", "tess", "prep", "rant", "lugs", "hobo", "joke",
      "odds", "yule", "aida", "true", "pone", "lode", "nona", "weep", "coda",
      "elmo", "skim", "wink", "bras", "pier", "bung", "pets", "tabs", "ryan",
      "jock", "body", "sofa", "joey", "zion", "mace", "kick", "vile", "leno",
      "bali", "fart", "that", "redo", "ills", "jogs", "pent", "drub", "slaw",
      "tide", "lena", "seep", "gyps", "wave", "amid", "fear", "ties", "flan",
      "wimp", "kali", "shun", "crap", "sage", "rune", "logs", "cain", "digs",
      "abut", "obit", "paps", "rids", "fair", "hack", "huns", "road", "caws",
      "curt", "jute", "fisk", "fowl", "duty", "holt", "miss", "rude", "vito",
      "baal", "ural", "mann", "mind", "belt", "clem", "last", "musk", "roam",
      "abed", "days", "bore", "fuze", "fall", "pict", "dump", "dies", "fiat",
      "vent", "pork", "eyed", "docs", "rive", "spas", "rope", "ariz", "tout",
      "game", "jump", "blur", "anti", "lisp", "turn", "sand", "food", "moos",
      "hoop", "saul", "arch", "fury", "rise", "diss", "hubs", "burs", "grid",
      "ilks", "suns", "flea", "soil", "lung", "want", "nola", "fins", "thud",
      "kidd", "juan", "heps", "nape", "rash", "burt", "bump", "tots", "brit",
      "mums", "bole", "shah", "tees", "skip", "limb", "umps", "ache", "arcs",
      "raft", "halo", "luce", "bahs", "leta", "conk", "duos", "siva", "went",
      "peek", "sulk", "reap", "free", "dubs", "lang", "toto", "hasp", "ball",
      "rats", "nair", "myst", "wang", "snug", "nash", "laos", "ante", "opal",
      "tina", "pore", "bite", "haas", "myth", "yugo", "foci", "dent", "bade",
      "pear", "mods", "auto", "shop", "etch", "lyly", "curs", "aron", "slew",
      "tyro", "sack", "wade", "clio", "gyro", "butt", "icky", "char", "itch",
      "halt", "gals", "yang", "tend", "pact", "bees", "suit", "puny", "hows",
      "nina", "brno", "oops", "lick", "sons", "kilo", "bust", "nome", "mona",
      "dull", "join", "hour", "papa", "stag", "bern", "wove", "lull", "slip",
      "laze", "roil", "alto", "bath", "buck", "alma", "anus", "evil", "dumb",
      "oreo", "rare", "near", "cure", "isis", "hill", "kyle", "pace", "comb",
      "nits", "flip", "clop", "mort", "thea", "wall", "kiel", "judd", "coop",
      "dave", "very", "amie", "blah", "flub", "talc", "bold", "fogy", "idea",
      "prof", "horn", "shoo", "aped", "pins", "helm", "wees", "beer", "womb",
      "clue", "alba", "aloe", "fine", "bard", "limo", "shaw", "pint", "swim",
      "dust", "indy", "hale", "cats", "troy", "wens", "luke", "vern", "deli",
      "both", "brig", "daub", "sara", "sued", "bier", "noel", "olga", "dupe",
      "look", "pisa", "knox", "murk", "dame", "matt", "gold", "jame", "toge",
      "luck", "peck", "tass", "calf", "pill", "wore", "wadi", "thur", "parr",
      "maul", "tzar", "ones", "lees", "dark", "fake", "bast", "zoom", "here",
      "moro", "wine", "bums", "cows", "jean", "palm", "fume", "plop", "help",
      "tuba", "leap", "cans", "back", "avid", "lice", "lust", "polo", "dory",
      "stew", "kate", "rama", "coke", "bled", "mugs", "ajax", "arts", "drug",
      "pena", "cody", "hole", "sean", "deck", "guts", "kong", "bate", "pitt",
      "como", "lyle", "siam", "rook", "baby", "jigs", "bret", "bark", "lori",
      "reba", "sups", "made", "buzz", "gnaw", "alps", "clay", "post", "viol",
      "dina", "card", "lana", "doff", "yups", "tons", "live", "kids", "pair",
      "yawl", "name", "oven", "sirs", "gyms", "prig", "down", "leos", "noon",
      "nibs", "cook", "safe", "cobb", "raja", "awes", "sari", "nerd", "fold",
      "lots", "pete", "deal", "bias", "zeal", "girl", "rage", "cool", "gout",
      "whey", "soak", "thaw", "bear", "wing", "nagy", "well", "oink", "sven",
      "kurt", "etna", "held", "wood", "high", "feta", "twee", "ford", "cave",
      "knot", "tory", "ibis", "yaks", "vets", "foxy", "sank", "cone", "pius",
      "tall", "seem", "wool", "flap", "gird", "lore", "coot", "mewl", "sere",
      "real", "puts", "sell", "nuts", "foil", "lilt", "saga", "heft", "dyed",
      "goat", "spew", "daze", "frye", "adds", "glen", "tojo", "pixy", "gobi",
      "stop", "tile", "hiss", "shed", "hahn", "baku", "ahas", "sill", "swap",
      "also", "carr", "manx", "lime", "debs", "moat", "eked", "bola", "pods",
      "coon", "lacy", "tube", "minx", "buff", "pres", "clew", "gaff", "flee",
      "burn", "whom", "cola", "fret", "purl", "wick", "wigs", "donn", "guys",
      "toni", "oxen", "wite", "vial", "spam", "huts", "vats", "lima", "core",
      "eula", "thad", "peon", "erie", "oats", "boyd", "cued", "olaf", "tams",
      "secs", "urey", "wile", "penn", "bred", "rill", "vary", "sues", "mail",
      "feds", "aves", "code", "beam", "reed", "neil", "hark", "pols", "gris",
      "gods", "mesa", "test", "coup", "heed", "dora", "hied", "tune", "doze",
      "pews", "oaks", "bloc", "tips", "maid", "goof", "four", "woof", "silo",
      "bray", "zest", "kiss", "yong", "file", "hilt", "iris", "tuns", "lily",
      "ears", "pant", "jury", "taft", "data", "gild", "pick", "kook", "colt",
      "bohr", "anal", "asps", "babe", "bach", "mash", "biko", "bowl", "huey",
      "jilt", "goes", "guff", "bend", "nike", "tami", "gosh", "tike", "gees",
      "urge", "path", "bony", "jude", "lynn", "lois", "teas", "dunn", "elul",
      "bonn", "moms", "bugs", "slay", "yeah", "loan", "hulk", "lows", "damn",
      "nell", "jung", "avis", "mane", "waco", "loin", "knob", "tyke", "anna",
      "hire", "luau", "tidy", "nuns", "pots", "quid", "exec", "hans", "hera",
      "hush", "shag", "scot", "moan", "wald", "ursa", "lorn", "hunk", "loft",
      "yore", "alum", "mows", "slog", "emma", "spud", "rice", "worn", "erma",
      "need", "bags", "lark", "kirk", "pooh", "dyes", "area", "dime", "luvs",
      "foch", "refs", "cast", "alit", "tugs", "even", "role", "toed", "caph",
      "nigh", "sony", "bide", "robs", "folk", "daft", "past", "blue", "flaw",
      "sana", "fits", "barr", "riot", "dots", "lamp", "cock", "fibs", "harp",
      "tent", "hate", "mali", "togs", "gear", "tues", "bass", "pros", "numb",
      "emus", "hare", "fate", "wife", "mean", "pink", "dune", "ares", "dine",
      "oily", "tony", "czar", "spay", "push", "glum", "till", "moth", "glue",
      "dive", "scad", "pops", "woks", "andy", "leah", "cusp", "hair", "alex",
      "vibe", "bulb", "boll", "firm", "joys", "tara", "cole", "levy", "owen",
      "chow", "rump", "jail", "lapp", "beet", "slap", "kith", "more", "maps",
      "bond", "hick", "opus", "rust", "wist", "shat", "phil", "snow", "lott",
      "lora", "cary", "mote", "rift", "oust", "klee", "goad", "pith", "heep",
      "lupe", "ivan", "mimi", "bald", "fuse", "cuts", "lens", "leer", "eyry",
      "know", "razz", "tare", "pals", "geek", "greg", "teen", "clef", "wags",
      "weal", "each", "haft", "nova", "waif", "rate", "katy", "yale", "dale",
      "leas", "axum", "quiz", "pawn", "fend", "capt", "laws", "city", "chad",
      "coal", "nail", "zaps", "sort", "loci", "less", "spur", "note", "foes",
      "fags", "gulp", "snap", "bogs", "wrap", "dane", "melt", "ease", "felt",
      "shea", "calm", "star", "swam", "aery", "year", "plan", "odin", "curd",
      "mira", "mops", "shit", "davy", "apes", "inky", "hues", "lome", "bits",
      "vila", "show", "best", "mice", "gins", "next", "roan", "ymir", "mars",
      "oman", "wild", "heal", "plus", "erin", "rave", "robe", "fast", "hutu",
      "aver", "jodi", "alms", "yams", "zero", "revs", "wean", "chic", "self",
      "jeep", "jobs", "waxy", "duel", "seek", "spot", "raps", "pimp", "adan",
      "slam", "tool", "morn", "futz", "ewes", "errs", "knit", "rung", "kans",
      "muff", "huhs", "tows", "lest", "meal", "azov", "gnus", "agar", "sips",
      "sway", "otis", "tone", "tate", "epic", "trio", "tics", "fade", "lear",
      "owns", "robt", "weds", "five", "lyon", "terr", "arno", "mama", "grey",
      "disk", "sept", "sire", "bart", "saps", "whoa", "turk", "stow", "pyle",
      "joni", "zinc", "negs", "task", "leif", "ribs", "malt", "nine", "bunt",
      "grin", "dona", "nope", "hams", "some", "molt", "smit", "sacs", "joan",
      "slav", "lady", "base", "heck", "list", "take", "herd", "will", "nubs",
      "burg", "hugs", "peru", "coif", "zoos", "nick", "idol", "levi", "grub",
      "roth", "adam", "elma", "tags", "tote", "yaws", "cali", "mete", "lula",
      "cubs", "prim", "luna", "jolt", "span", "pita", "dodo", "puss", "deer",
      "term", "dolt", "goon", "gary", "yarn", "aims", "just", "rena", "tine",
      "cyst", "meld", "loki", "wong", "were", "hung", "maze", "arid", "cars",
      "wolf", "marx", "faye", "eave", "raga", "flow", "neal", "lone", "anne",
      "cage", "tied", "tilt", "soto", "opel", "date", "buns", "dorm", "kane",
      "akin", "ewer", "drab", "thai", "jeer", "grad", "berm", "rods", "saki",
      "grus", "vast", "late", "lint", "mule", "risk", "labs", "snit", "gala",
      "find", "spin", "ired", "slot", "oafs", "lies", "mews", "wino", "milk",
      "bout", "onus", "tram", "jaws", "peas", "cleo", "seat", "gums", "cold",
      "vang", "dewy", "hood", "rush", "mack", "yuan", "odes", "boos", "jami",
      "mare", "plot", "swab", "borg", "hays", "form", "mesh", "mani", "fife",
      "good", "gram", "lion", "myna", "moor", "skin", "posh", "burr", "rime",
      "done", "ruts", "pays", "stem", "ting", "arty", "slag", "iron", "ayes",
      "stub", "oral", "gets", "chid", "yens", "snub", "ages", "wide", "bail",
      "verb", "lamb", "bomb", "army", "yoke", "gels", "tits", "bork", "mils",
      "nary", "barn", "hype", "odom", "avon", "hewn", "rios", "cams", "tact",
      "boss", "oleo", "duke", "eris", "gwen", "elms", "deon", "sims", "quit",
      "nest", "font", "dues", "yeas", "zeta", "bevy", "gent", "torn", "cups",
      "worm", "baum", "axon", "purr", "vise", "grew", "govs", "meat", "chef",
      "rest", "lame"};

  const vector<vector<string>> output4{
      s.findLadders("sand", "acne", word_list4)};
  cout << "s.findLadders(sand, acne, word_list4) -> " << output4
       << '\n';  // expected output:
                 // [[sand,sans,sins,sims,aims,arms,arts,ants,ante,anne,acne],
                 // [sand,sans,sins,bins,bids,aids,ands,ants,ante,anne,acne],
                 // [sand,sans,bans,bins,bids,aids,ands,ants,ante,anne,acne],
                 // [sand,band,bans,bins,bids,aids,ands,ants,ante,anne,acne],
                 // [sand,band,bind,bins,bids,aids,ands,ants,ante,anne,acne],
                 // [sand,sans,sins,kins,kids,aids,ands,ants,ante,anne,acne],
                 // [sand,sans,kans,kins,kids,aids,ands,ants,ante,anne,acne],
                 // [sand,sans,sins,sirs,airs,aids,ands,ants,ante,anne,acne],
                 // [sand,sans,sins,sims,aims,aids,ands,ants,ante,anne,acne],
                 // [sand,sane,sade,side,aide,aids,ands,ants,ante,anne,acne],
                 // [sand,sane,sine,side,aide,aids,ands,ants,ante,anne,acne]]

  vector<string> word_list5{
      "ricky", "grind", "cubic", "panic", "lover", "farce", "gofer", "sales",
      "flint", "omens", "lipid", "briny", "cloth", "anted", "slime", "oaten",
      "harsh", "touts", "stoop", "cabal", "lazed", "elton", "skunk", "nicer",
      "pesky", "kusch", "bused", "kinda", "tunis", "enjoy", "aches", "prowl",
      "babar", "rooms", "burst", "slush", "pines", "urine", "pinky", "bayed",
      "mania", "light", "flare", "wares", "women", "verne", "moron", "shine",
      "bluer", "zeros", "bleak", "brief", "tamra", "vasts", "jamie", "lairs",
      "penal", "worst", "yowls", "pills", "taros", "addle", "alyce", "creep",
      "saber", "floyd", "cures", "soggy", "vexed", "vilma", "cabby", "verde",
      "euler", "cling", "wanna", "jenny", "donor", "stole", "sakha", "blake",
      "sanes", "riffs", "forge", "horus", "sered", "piked", "prosy", "wases",
      "glove", "onset", "spake", "benin", "talks", "sites", "biers", "wendy",
      "dante", "allan", "haven", "nears", "shaka", "sloth", "perky", "spear",
      "spend", "clint", "dears", "sadly", "units", "vista", "hinds", "marat",
      "natal", "least", "bough", "pales", "boole", "ditch", "greys", "slunk",
      "bitch", "belts", "sense", "skits", "monty", "yawns", "music", "hails",
      "alien", "gibes", "lille", "spacy", "argot", "wasps", "drubs", "poops",
      "bella", "clone", "beast", "emend", "iring", "start", "darla", "bells",
      "cults", "dhaka", "sniff", "seers", "bantu", "pages", "fever", "tacky",
      "hoses", "strop", "climb", "pairs", "later", "grant", "raven", "stael",
      "drips", "lucid", "awing", "dines", "balms", "della", "galen", "toned",
      "snips", "shady", "chili", "fears", "nurse", "joint", "plump", "micky",
      "lions", "jamal", "queer", "ruins", "frats", "spoof", "semen", "pulps",
      "oldie", "coors", "rhone", "papal", "seals", "spans", "scaly", "sieve",
      "klaus", "drums", "tided", "needs", "rider", "lures", "treks", "hares",
      "liner", "hokey", "boots", "primp", "laval", "limes", "putts", "fonda",
      "damon", "pikes", "hobbs", "specs", "greet", "ketch", "braid", "purer",
      "tsars", "berne", "tarts", "clean", "grate", "trips", "chefs", "timex",
      "vicky", "pares", "price", "every", "beret", "vices", "jodie", "fanny",
      "mails", "built", "bossy", "farms", "pubic", "gongs", "magma", "quads",
      "shell", "jocks", "woods", "waded", "parka", "jells", "worse", "diner",
      "risks", "bliss", "bryan", "terse", "crier", "incur", "murky", "gamed",
      "edges", "keens", "bread", "raced", "vetch", "glint", "zions", "porno",
      "sizes", "mends", "ached", "allie", "bands", "plank", "forth", "fuels",
      "rhyme", "wimpy", "peels", "foggy", "wings", "frill", "edgar", "slave",
      "lotus", "point", "hints", "germs", "clung", "limed", "loafs", "realm",
      "myron", "loopy", "plush", "volts", "bimbo", "smash", "windy", "sours",
      "choke", "karin", "boast", "whirr", "tiber", "dimes", "basel", "cutes",
      "pinto", "troll", "thumb", "decor", "craft", "tared", "split", "josue",
      "tramp", "screw", "label", "lenny", "apses", "slept", "sikhs", "child",
      "bouts", "cites", "swipe", "lurks", "seeds", "fists", "hoard", "steed",
      "reams", "spoil", "diego", "peale", "bevel", "flags", "mazes", "quart",
      "snipe", "latch", "lards", "acted", "falls", "busby", "holed", "mummy",
      "wrong", "wipes", "carlo", "leers", "wails", "night", "pasty", "eater",
      "flunk", "vedas", "curse", "tyros", "mirth", "jacky", "butte", "wired",
      "fixes", "tares", "vague", "roved", "stove", "swoon", "scour", "coked",
      "marge", "cants", "comic", "corns", "zilch", "typos", "lives", "truer",
      "comma", "gaily", "teals", "witty", "hyper", "croat", "sways", "tills",
      "hones", "dowel", "llano", "clefs", "fores", "cinch", "brock", "vichy",
      "bleed", "nuder", "hoyle", "slams", "macro", "arabs", "tauts", "eager",
      "croak", "scoop", "crime", "lurch", "weals", "fates", "clipt", "teens",
      "bulls", "domed", "ghana", "culls", "frame", "hanky", "jared", "swain",
      "truss", "drank", "lobby", "lumps", "pansy", "whews", "saris", "trite",
      "weeps", "dozes", "jeans", "flood", "chimu", "foxes", "gelds", "sects",
      "scoff", "poses", "mares", "famed", "peers", "hells", "laked", "zests",
      "wring", "steal", "snoot", "yodel", "scamp", "ellis", "bandy", "marry",
      "jives", "vises", "blurb", "relay", "patch", "haley", "cubit", "heine",
      "place", "touch", "grain", "gerry", "badly", "hooke", "fuchs", "savor",
      "apron", "judge", "loren", "britt", "smith", "tammy", "altar", "duels",
      "huber", "baton", "dived", "apace", "sedan", "basts", "clark", "mired",
      "perch", "hulks", "jolly", "welts", "quack", "spore", "alums", "shave",
      "singe", "lanny", "dread", "profs", "skeet", "flout", "darin", "newed",
      "steer", "taine", "salvo", "mites", "rules", "crash", "thorn", "olive",
      "saves", "yawed", "pique", "salon", "ovens", "dusty", "janie", "elise",
      "carve", "winds", "abash", "cheep", "strap", "fared", "discs", "poxed",
      "hoots", "catch", "combo", "maize", "repay", "mario", "snuff", "delve",
      "cored", "bards", "sudan", "shuns", "yukon", "jowls", "wayne", "torus",
      "gales", "creek", "prove", "needy", "wisps", "terri", "ranks", "books",
      "dicky", "tapes", "aping", "padre", "roads", "nines", "seats", "flats",
      "rains", "moira", "basic", "loves", "pulls", "tough", "gills", "codes",
      "chest", "teeny", "jolts", "woody", "flame", "asked", "dulls", "hotly",
      "glare", "mucky", "spite", "flake", "vines", "lindy", "butts", "froth",
      "beeps", "sills", "bunny", "flied", "shaun", "mawed", "velds", "voled",
      "doily", "patel", "snake", "thigh", "adler", "calks", "desks", "janus",
      "spunk", "baled", "match", "strip", "hosed", "nippy", "wrest", "whams",
      "calfs", "sleet", "wives", "boars", "chain", "table", "duked", "riped",
      "edens", "galas", "huffs", "biddy", "claps", "aleut", "yucks", "bangs",
      "quids", "glenn", "evert", "drunk", "lusts", "senna", "slate", "manet",
      "roted", "sleep", "loxes", "fluky", "fence", "clamp", "doted", "broad",
      "sager", "spark", "belch", "mandy", "deana", "beyer", "hoist", "leafy",
      "levee", "libel", "tonic", "aloes", "steam", "skews", "tides", "stall",
      "rifts", "saxon", "mavis", "asama", "might", "dotes", "tangs", "wroth",
      "kited", "salad", "liens", "clink", "glows", "balky", "taffy", "sided",
      "sworn", "oasis", "tenth", "blurt", "tower", "often", "walsh", "sonny",
      "andes", "slump", "scans", "boded", "chive", "finer", "ponce", "prune",
      "sloes", "dined", "chums", "dingo", "harte", "ahead", "event", "freer",
      "heart", "fetch", "sated", "soapy", "skins", "royal", "cuter", "loire",
      "minot", "aisle", "horny", "slued", "panel", "eight", "snoop", "pries",
      "clive", "pored", "wrist", "piped", "daren", "cells", "parks", "slugs",
      "cubed", "highs", "booze", "weary", "stain", "hoped", "finny", "weeds",
      "fetid", "racer", "tasks", "right", "saint", "shahs", "basis", "refer",
      "chart", "seize", "lulls", "slant", "belay", "clots", "jinny", "tours",
      "modes", "gloat", "dunks", "flute", "conch", "marts", "aglow", "gayer",
      "lazes", "dicks", "chime", "bears", "sharp", "hatch", "forms", "terry",
      "gouda", "thins", "janet", "tonya", "axons", "sewed", "danny", "rowdy",
      "dolts", "hurry", "opine", "fifty", "noisy", "spiky", "humid", "verna",
      "poles", "jayne", "pecos", "hooky", "haney", "shams", "snots", "sally",
      "ruder", "tempe", "plunk", "shaft", "scows", "essie", "dated", "fleet",
      "spate", "bunin", "hikes", "sodas", "filly", "thyme", "fiefs", "perks",
      "chary", "kiths", "lidia", "lefty", "wolff", "withe", "three", "crawl",
      "wotan", "brown", "japed", "tolls", "taken", "threw", "crave", "clash",
      "layer", "tends", "notes", "fudge", "musky", "bawdy", "aline", "matts",
      "shirr", "balks", "stash", "wicks", "crepe", "foods", "fares", "rotes",
      "party", "petty", "press", "dolly", "mangy", "leeks", "silly", "leant",
      "nooks", "chapt", "loose", "caged", "wages", "grist", "alert", "sheri",
      "moody", "tamps", "hefts", "souls", "rubes", "rolex", "skulk", "veeps",
      "nonce", "state", "level", "whirl", "bight", "grits", "reset", "faked",
      "spiny", "mixes", "hunks", "major", "missy", "arius", "damns", "fitly",
      "caped", "mucus", "trace", "surat", "lloyd", "furry", "colin", "texts",
      "livia", "reply", "twill", "ships", "peons", "shear", "norms", "jumbo",
      "bring", "masks", "zippy", "brine", "dorks", "roded", "sinks", "river",
      "wolfs", "strew", "myths", "pulpy", "prank", "veins", "flues", "minus",
      "phone", "banns", "spell", "burro", "brags", "boyle", "lambs", "sides",
      "knees", "clews", "aired", "skirt", "heavy", "dimer", "bombs", "scums",
      "hayes", "chaps", "snugs", "dusky", "loxed", "ellen", "while", "swank",
      "track", "minim", "wiled", "hazed", "roofs", "cantu", "sorry", "roach",
      "loser", "brass", "stint", "jerks", "dirks", "emory", "campy", "poise",
      "sexed", "gamer", "catty", "comte", "bilbo", "fasts", "ledge", "drier",
      "idles", "doors", "waged", "rizal", "pured", "weirs", "crisp", "tasty",
      "sored", "palmy", "parts", "ethel", "unify", "crows", "crest", "udder",
      "delis", "punks", "dowse", "totes", "emile", "coded", "shops", "poppa",
      "pours", "gushy", "tiffs", "shads", "birds", "coils", "areas", "boons",
      "hulls", "alter", "lobes", "pleat", "depth", "fires", "pones", "serra",
      "sweat", "kline", "malay", "ruled", "calve", "tired", "drabs", "tubed",
      "wryer", "slung", "union", "sonya", "aided", "hewed", "dicey", "grids",
      "nixed", "whits", "mills", "buffs", "yucky", "drops", "ready", "yuppy",
      "tweet", "napes", "cadre", "teach", "rasps", "dowdy", "hoary", "canto",
      "posed", "dumbo", "kooks", "reese", "snaky", "binge", "byron", "phony",
      "safer", "friar", "novel", "scale", "huron", "adorn", "carla", "fauna",
      "myers", "hobby", "purse", "flesh", "smock", "along", "boils", "pails",
      "times", "panza", "lodge", "clubs", "colby", "great", "thing", "peaks",
      "diana", "vance", "whets", "bergs", "sling", "spade", "soaks", "beach",
      "traps", "aspen", "romps", "boxed", "fakir", "weave", "nerds", "swazi",
      "dotty", "curls", "diver", "jonas", "waite", "verbs", "yeast", "lapel",
      "barth", "soars", "hooks", "taxed", "slews", "gouge", "slags", "chang",
      "chafe", "saved", "josie", "syncs", "fonds", "anion", "actor", "seems",
      "pyrex", "isiah", "glued", "groin", "goren", "waxes", "tonia", "whine",
      "scads", "knelt", "teaks", "satan", "tromp", "spats", "merry", "wordy",
      "stake", "gland", "canal", "donna", "lends", "filed", "sacks", "shied",
      "moors", "paths", "older", "pooch", "balsa", "riced", "facet", "decaf",
      "attic", "elder", "akron", "chomp", "chump", "picky", "money", "sheer",
      "bolls", "crabs", "dorms", "water", "veers", "tease", "dummy", "dumbs",
      "lethe", "halls", "rifer", "demon", "fucks", "whips", "plops", "fuses",
      "focal", "taces", "snout", "edict", "flush", "burps", "dawes", "lorry",
      "spews", "sprat", "click", "deann", "sited", "aunts", "quips", "godly",
      "pupil", "nanny", "funks", "shoon", "aimed", "stacy", "helms", "mints",
      "banks", "pinch", "local", "twine", "pacts", "deers", "halos", "slink",
      "preys", "potty", "ruffs", "pusan", "suits", "finks", "slash", "prods",
      "dense", "edsel", "heeds", "palls", "slats", "snits", "mower", "rares",
      "ailed", "rouge", "ellie", "gated", "lyons", "duded", "links", "oaths",
      "letha", "kicks", "firms", "gravy", "month", "kongo", "mused", "ducal",
      "toted", "vocal", "disks", "spied", "studs", "macao", "erick", "coupe",
      "starr", "reaps", "decoy", "rayon", "nicks", "breed", "cosby", "haunt",
      "typed", "plain", "trays", "muled", "saith", "drano", "cower", "snows",
      "buses", "jewry", "argus", "doers", "flays", "swish", "resin", "boobs",
      "sicks", "spies", "bails", "wowed", "mabel", "check", "vapid", "bacon",
      "wilda", "ollie", "loony", "irked", "fraud", "doles", "facts", "lists",
      "gazed", "furls", "sunks", "stows", "wilde", "brick", "bowed", "guise",
      "suing", "gates", "niter", "heros", "hyped", "clomp", "never", "lolls",
      "rangy", "paddy", "chant", "casts", "terns", "tunas", "poker", "scary",
      "maims", "saran", "devon", "tripe", "lingo", "paler", "coped", "bride",
      "voted", "dodge", "gross", "curds", "sames", "those", "tithe", "steep",
      "flaks", "close", "swops", "stare", "notch", "prays", "roles", "crush",
      "feuds", "nudge", "baned", "brake", "plans", "weepy", "dazed", "jenna",
      "weiss", "tomes", "stews", "whist", "gibed", "death", "clank", "cover",
      "peeks", "quick", "abler", "daddy", "calls", "scald", "lilia", "flask",
      "cheer", "grabs", "megan", "canes", "jules", "blots", "mossy", "begun",
      "freak", "caved", "hello", "hades", "theed", "wards", "darcy", "malta",
      "peter", "whorl", "break", "downs", "odder", "hoofs", "kiddo", "macho",
      "fords", "liked", "flees", "swing", "elect", "hoods", "pluck", "brook",
      "astir", "bland", "sward", "modal", "flown", "ahmad", "waled", "craps",
      "cools", "roods", "hided", "plath", "kings", "grips", "gives", "gnats",
      "tabby", "gauls", "think", "bully", "fogey", "sawed", "lints", "pushy",
      "banes", "drake", "trail", "moral", "daley", "balds", "chugs", "geeky",
      "darts", "soddy", "haves", "opens", "rends", "buggy", "moles", "freud",
      "gored", "shock", "angus", "puree", "raves", "johns", "armed", "packs",
      "minis", "reich", "slots", "totem", "clown", "popes", "brute", "hedge",
      "latin", "stoke", "blend", "pease", "rubik", "greer", "hindi", "betsy",
      "flows", "funky", "kelli", "humps", "chewy", "welds", "scowl", "yells",
      "cough", "sasha", "sheaf", "jokes", "coast", "words", "irate", "hales",
      "camry", "spits", "burma", "rhine", "bends", "spill", "stubs", "power",
      "voles", "learn", "knoll", "style", "twila", "drove", "dacca", "sheen",
      "papas", "shale", "jones", "duped", "tunny", "mouse", "floss", "corks",
      "skims", "swaps", "inned", "boxer", "synch", "skies", "strep", "bucks",
      "belau", "lower", "flaky", "quill", "aural", "rufus", "floes", "pokes",
      "sends", "sates", "dally", "boyer", "hurts", "foyer", "gowns", "torch",
      "luria", "fangs", "moats", "heinz", "bolts", "filet", "firth", "begot",
      "argue", "youth", "chimp", "frogs", "kraft", "smite", "loges", "loons",
      "spine", "domes", "pokey", "timur", "noddy", "doggy", "wades", "lanes",
      "hence", "louts", "turks", "lurid", "goths", "moist", "bated", "giles",
      "stood", "winos", "shins", "potts", "brant", "vised", "alice", "rosie",
      "dents", "babes", "softy", "decay", "meats", "tanya", "rusks", "pasts",
      "karat", "nuked", "gorge", "kinks", "skull", "noyce", "aimee", "watch",
      "cleat", "stuck", "china", "testy", "doses", "safes", "stage", "bayes",
      "twins", "limps", "denis", "chars", "flaps", "paces", "abase", "grays",
      "deans", "maria", "asset", "smuts", "serbs", "whigs", "vases", "robyn",
      "girls", "pents", "alike", "nodal", "molly", "swigs", "swill", "slums",
      "rajah", "bleep", "beget", "thanh", "finns", "clock", "wafts", "wafer",
      "spicy", "sorer", "reach", "beats", "baker", "crown", "drugs", "daisy",
      "mocks", "scots", "fests", "newer", "agate", "drift", "marta", "chino",
      "flirt", "homed", "bribe", "scram", "bulks", "servo", "vesta", "divas",
      "preps", "naval", "tally", "shove", "ragas", "blown", "droll", "tryst",
      "lucky", "leech", "lines", "sires", "pyxed", "taper", "trump", "payee",
      "midge", "paris", "bored", "loads", "shuts", "lived", "swath", "snare",
      "boned", "scars", "aeons", "grime", "writs", "paige", "rungs", "blent",
      "signs", "davis", "dials", "daubs", "rainy", "fawns", "wrier", "golds",
      "wrath", "ducks", "allow", "hosea", "spike", "meals", "haber", "muses",
      "timed", "broom", "burks", "louis", "gangs", "pools", "vales", "altai",
      "elope", "plied", "slain", "chasm", "entry", "slide", "bawls", "title",
      "sings", "grief", "viola", "doyle", "peach", "davit", "bench", "devil",
      "latex", "miles", "pasha", "tokes", "coves", "wheel", "tried", "verdi",
      "wanda", "sivan", "prior", "fryer", "plots", "kicky", "porch", "shill",
      "coats", "borne", "brink", "pawed", "erwin", "tense", "stirs", "wends",
      "waxen", "carts", "smear", "rival", "scare", "phase", "bragg", "crane",
      "hocks", "conan", "bests", "dares", "molls", "roots", "dunes", "slips",
      "waked", "fours", "bolds", "slosh", "yemen", "poole", "solid", "ports",
      "fades", "legal", "cedes", "green", "curie", "seedy", "riper", "poled",
      "glade", "hosts", "tools", "razes", "tarry", "muddy", "shims", "sword",
      "thine", "lasts", "bloat", "soled", "tardy", "foots", "skiff", "volta",
      "murks", "croci", "gooks", "gamey", "pyxes", "poems", "kayla", "larva",
      "slaps", "abuse", "pings", "plows", "geese", "minks", "derby", "super",
      "inked", "manic", "leaks", "flops", "lajos", "fuzes", "swabs", "twigs",
      "gummy", "pyres", "shrew", "islet", "doled", "wooly", "lefts", "hunts",
      "toast", "faith", "macaw", "sonia", "leafs", "colas", "conks", "altos",
      "wiped", "scene", "boors", "patsy", "meany", "chung", "wakes", "clear",
      "ropes", "tahoe", "zones", "crate", "tombs", "nouns", "garth", "puked",
      "chats", "hanks", "baked", "binds", "fully", "soaps", "newel", "yarns",
      "puers", "carps", "spelt", "lully", "towed", "scabs", "prime", "blest",
      "patty", "silky", "abner", "temps", "lakes", "tests", "alias", "mines",
      "chips", "funds", "caret", "splat", "perry", "turds", "junks", "cramp",
      "saned", "peary", "snarl", "fired", "stung", "nancy", "bulge", "styli",
      "seams", "hived", "feast", "triad", "jaded", "elvin", "canny", "birth",
      "routs", "rimed", "pusey", "laces", "taste", "basie", "malls", "shout",
      "prier", "prone", "finis", "claus", "loops", "heron", "frump", "spare",
      "menus", "ariel", "crams", "bloom", "foxed", "moons", "mince", "mixed",
      "piers", "deres", "tempt", "dryer", "atone", "heats", "dario", "hawed",
      "swims", "sheet", "tasha", "dings", "clare", "aging", "daffy", "wried",
      "foals", "lunar", "havel", "irony", "ronny", "naves", "selma", "gurus",
      "crust", "percy", "murat", "mauro", "cowed", "clang", "biker", "harms",
      "barry", "thump", "crude", "ulnae", "thong", "pager", "oases", "mered",
      "locke", "merle", "soave", "petal", "poser", "store", "winch", "wedge",
      "inlet", "nerdy", "utter", "filth", "spray", "drape", "pukes", "ewers",
      "kinds", "dates", "meier", "tammi", "spoor", "curly", "chill", "loped",
      "gooey", "boles", "genet", "boost", "beets", "heath", "feeds", "growl",
      "livid", "midst", "rinds", "fresh", "waxed", "yearn", "keeps", "rimes",
      "naked", "flick", "plies", "deeps", "dirty", "hefty", "messy", "hairy",
      "walks", "leper", "sykes", "nerve", "rover", "jived", "brisk", "lenin",
      "viper", "chuck", "sinus", "luger", "ricks", "hying", "rusty", "kathy",
      "herds", "wider", "getty", "roman", "sandy", "pends", "fezes", "trios",
      "bites", "pants", "bless", "diced", "earth", "shack", "hinge", "melds",
      "jonah", "chose", "liver", "salts", "ratty", "ashed", "wacky", "yokes",
      "wanly", "bruce", "vowel", "black", "grail", "lungs", "arise", "gluts",
      "gluey", "navel", "coyer", "ramps", "miter", "aldan", "booth", "musty",
      "rills", "darns", "tined", "straw", "kerri", "hared", "lucks", "metes",
      "penny", "radon", "palms", "deeds", "earls", "shard", "pried", "tampa",
      "blank", "gybes", "vicki", "drool", "groom", "curer", "cubes", "riggs",
      "lanky", "tuber", "caves", "acing", "golly", "hodge", "beard", "ginny",
      "jibed", "fumes", "astor", "quito", "cargo", "randi", "gawky", "zings",
      "blind", "dhoti", "sneak", "fatah", "fixer", "lapps", "cline", "grimm",
      "fakes", "maine", "erika", "dealt", "mitch", "olden", "joist", "gents",
      "likes", "shelf", "silts", "goats", "leads", "marin", "spire", "louie",
      "evans", "amuse", "belly", "nails", "snead", "model", "whats", "shari",
      "quote", "tacks", "nutty", "lames", "caste", "hexes", "cooks", "miner",
      "shawn", "anise", "drama", "trike", "prate", "ayers", "loans", "botch",
      "vests", "cilia", "ridge", "thugs", "outed", "jails", "moped", "plead",
      "tunes", "nosed", "wills", "lager", "lacks", "cried", "wince", "berle",
      "flaws", "boise", "tibet", "bided", "shred", "cocky", "brice", "delta",
      "congo", "holly", "hicks", "wraps", "cocks", "aisha", "heard", "cured",
      "sades", "horsy", "umped", "trice", "dorky", "curve", "ferry", "haler",
      "ninth", "pasta", "jason", "honer", "kevin", "males", "fowls", "awake",
      "pores", "meter", "skate", "drink", "pussy", "soups", "bases", "noyes",
      "torts", "bogus", "still", "soupy", "dance", "worry", "eldon", "stern",
      "menes", "dolls", "dumpy", "gaunt", "grove", "coops", "mules", "berry",
      "sower", "roams", "brawl", "greed", "stags", "blurs", "swift", "treed",
      "taney", "shame", "easel", "moves", "leger", "ville", "order", "spock",
      "nifty", "brian", "elias", "idler", "serve", "ashen", "bizet", "gilts",
      "spook", "eaten", "pumas", "cotes", "broke", "toxin", "groan", "laths",
      "joins", "spots", "hated", "tokay", "elite", "rawer", "fiats", "cards",
      "sassy", "milks", "roost", "glean", "lutes", "chins", "drown", "marks",
      "pined", "grace", "fifth", "lodes", "rusts", "terms", "maxes", "savvy",
      "choir", "savoy", "spoon", "halve", "chord", "hulas", "sarah", "celia",
      "deems", "ninny", "wines", "boggy", "birch", "raved", "wales", "beams",
      "vibes", "riots", "warty", "nigel", "askew", "faxes", "sedge", "sheol",
      "pucks", "cynic", "relax", "boers", "whims", "bents", "candy", "luann",
      "slogs", "bonny", "barns", "iambs", "fused", "duffy", "guilt", "bruin",
      "pawls", "penis", "poppy", "owing", "tribe", "tuner", "moray", "timid",
      "ceded", "geeks", "kites", "curio", "puffy", "perot", "caddy", "peeve",
      "cause", "dills", "gavel", "manse", "joker", "lynch", "crank", "golda",
      "waits", "wises", "hasty", "paves", "grown", "reedy", "crypt", "tonne",
      "jerky", "axing", "swept", "posse", "rings", "staff", "tansy", "pared",
      "glaze", "grebe", "gonna", "shark", "jumps", "vials", "unset", "hires",
      "tying", "lured", "motes", "linen", "locks", "mamas", "nasty", "mamie",
      "clout", "nader", "velma", "abate", "tight", "dales", "serer", "rives",
      "bales", "loamy", "warps", "plato", "hooch", "togae", "damps", "ofter",
      "plumb", "fifes", "filmy", "wiper", "chess", "lousy", "sails", "brahe",
      "ounce", "flits", "hindu", "manly", "beaux", "mimed", "liken", "forts",
      "jambs", "peeps", "lelia", "brews", "handy", "lusty", "brads", "marne",
      "pesos", "earle", "arson", "scout", "showy", "chile", "sumps", "hiked",
      "crook", "herbs", "silks", "alamo", "mores", "dunce", "blaze", "stank",
      "haste", "howls", "trots", "creon", "lisle", "pause", "hates", "mulch",
      "mined", "moder", "devin", "types", "cindy", "beech", "tuned", "mowed",
      "pitts", "chaos", "colds", "bidet", "tines", "sighs", "slimy", "brain",
      "belle", "leery", "morse", "ruben", "prows", "frown", "disco", "regal",
      "oaken", "sheds", "hives", "corny", "baser", "fated", "throe", "revel",
      "bores", "waved", "shits", "elvia", "ferns", "maids", "color", "coifs",
      "cohan", "draft", "hmong", "alton", "stine", "cluck", "nodes", "emily",
      "brave", "blair", "blued", "dress", "bunts", "holst", "clogs", "rally",
      "knack", "demos", "brady", "blues", "flash", "goofy", "blocs", "diane",
      "colic", "smile", "yules", "foamy", "splay", "bilge", "faker", "foils",
      "condo", "knell", "crack", "gallo", "purls", "auras", "cakes", "doves",
      "joust", "aides", "lades", "muggy", "tanks", "middy", "tarps", "slack",
      "capet", "frays", "donny", "venal", "yeats", "misty", "denim", "glass",
      "nudes", "seeps", "gibbs", "blows", "bobbi", "shane", "yards", "pimps",
      "clued", "quiet", "witch", "boxes", "prawn", "kerry", "torah", "kinko",
      "dingy", "emote", "honor", "jelly", "grins", "trope", "vined", "bagel",
      "arden", "rapid", "paged", "loved", "agape", "mural", "budge", "ticks",
      "suers", "wendi", "slice", "salve", "robin", "bleat", "batik", "myles",
      "teddy", "flatt", "puppy", "gelid", "largo", "attar", "polls", "glide",
      "serum", "fundy", "sucks", "shalt", "sewer", "wreak", "dames", "fonts",
      "toxic", "hines", "wormy", "grass", "louse", "bowls", "crass", "benny",
      "moire", "margo", "golfs", "smart", "roxie", "wight", "reign", "dairy",
      "clops", "paled", "oddly", "sappy", "flair", "shown", "bulgy", "benet",
      "larch", "curry", "gulfs", "fends", "lunch", "dukes", "doris", "spoke",
      "coins", "manna", "conga", "jinns", "eases", "dunno", "tisha", "swore",
      "rhino", "calms", "irvin", "clans", "gully", "liege", "mains", "besot",
      "serge", "being", "welch", "wombs", "draco", "lynda", "forty", "mumps",
      "bloch", "ogden", "knits", "fussy", "alder", "danes", "loyal", "valet",
      "wooer", "quire", "liefs", "shana", "toyed", "forks", "gages", "slims",
      "cloys", "yates", "rails", "sheep", "nacho", "divan", "honks", "stone",
      "snack", "added", "basal", "hasps", "focus", "alone", "laxes", "arose",
      "lamed", "wrapt", "frail", "clams", "plait", "hover", "tacos", "mooch",
      "fault", "teeth", "marva", "mucks", "tread", "waves", "purim", "boron",
      "horde", "smack", "bongo", "monte", "swirl", "deals", "mikes", "scold",
      "muter", "sties", "lawns", "fluke", "jilts", "meuse", "fives", "sulky",
      "molds", "snore", "timmy", "ditty", "gasps", "kills", "carey", "jawed",
      "byers", "tommy", "homer", "hexed", "dumas", "given", "mewls", "smelt",
      "weird", "speck", "merck", "keats", "draws", "trent", "agave", "wells",
      "chews", "blabs", "roves", "grieg", "evens", "alive", "mulls", "cared",
      "garbo", "fined", "happy", "trued", "rodes", "thurs", "cadet", "alvin",
      "busch", "moths", "guild", "staci", "lever", "widen", "props", "hussy",
      "lamer", "riley", "bauer", "chirp", "rants", "poxes", "shyer", "pelts",
      "funny", "slits", "tinge", "ramos", "shift", "caper", "credo", "renal",
      "veils", "covey", "elmer", "mated", "tykes", "wooed", "briar", "gears",
      "foley", "shoes", "decry", "hypes", "dells", "wilds", "runts", "wilts",
      "white", "easts", "comer", "sammy", "lochs", "favor", "lance", "dawns",
      "bushy", "muted", "elsie", "creel", "pocks", "tenet", "cagey", "rides",
      "socks", "ogled", "soils", "sofas", "janna", "exile", "barks", "frank",
      "takes", "zooms", "hakes", "sagan", "scull", "heaps", "augur", "pouch",
      "blare", "bulbs", "wryly", "homey", "tubas", "limbo", "hardy", "hoagy",
      "minds", "bared", "gabby", "bilks", "float", "limns", "clasp", "laura",
      "range", "brush", "tummy", "kilts", "cooed", "worms", "leary", "feats",
      "robes", "suite", "veals", "bosch", "moans", "dozen", "rarer", "slyer",
      "cabin", "craze", "sweet", "talon", "treat", "yanks", "react", "creed",
      "eliza", "sluts", "cruet", "hafts", "noise", "seder", "flies", "weeks",
      "venus", "backs", "eider", "uriel", "vouch", "robed", "hacks", "perth",
      "shiny", "stilt", "torte", "throb", "merer", "twits", "reeds", "shawl",
      "clara", "slurs", "mixer", "newts", "fried", "woolf", "swoop", "kaaba",
      "oozed", "mayer", "caned", "laius", "lunge", "chits", "kenny", "lifts",
      "mafia", "sowed", "piled", "stein", "whack", "colts", "warms", "cleft",
      "girds", "seeks", "poets", "angel", "trade", "parsi", "tiers", "rojas",
      "vexes", "bryce", "moots", "grunt", "drain", "lumpy", "stabs", "poohs",
      "leapt", "polly", "cuffs", "giddy", "towns", "dacha", "quoth", "provo",
      "dilly", "carly", "mewed", "tzars", "crock", "toked", "speak", "mayas",
      "pssts", "ocher", "motel", "vogue", "camps", "tharp", "taunt", "drone",
      "taint", "badge", "scott", "scats", "bakes", "antes", "gruel", "snort",
      "capes", "plate", "folly", "adobe", "yours", "papaw", "hench", "moods",
      "clunk", "chevy", "tomas", "narcs", "vonda", "wiles", "prigs", "chock",
      "laser", "viced", "stiff", "rouse", "helps", "knead", "gazer", "blade",
      "tumid", "avail", "anger", "egged", "guide", "goads", "rabin", "toddy",
      "gulps", "flank", "brats", "pedal", "junky", "marco", "tinny", "tires",
      "flier", "satin", "darth", "paley", "gumbo", "rared", "muffs", "rower",
      "prude", "frees", "quays", "homes", "munch", "beefs", "leash", "aston",
      "colon", "finch", "bogey", "leaps", "tempo", "posts", "lined", "gapes",
      "locus", "maori", "nixes", "liven", "songs", "opted", "babel", "wader",
      "barer", "farts", "lisps", "koran", "lathe", "trill", "smirk", "mamma",
      "viler", "scurf", "ravel", "brigs", "cooky", "sachs", "fulls", "goals",
      "turfs", "norse", "hauls", "cores", "fairy", "pluto", "kneed", "cheek",
      "pangs", "risen", "czars", "milne", "cribs", "genes", "wefts", "vents",
      "sages", "seres", "owens", "wiley", "flume", "haded", "auger", "tatty",
      "onion", "cater", "wolfe", "magic", "bodes", "gulls", "gazes", "dandy",
      "snags", "rowed", "quell", "spurn", "shore", "veldt", "turns", "slavs",
      "coach", "stalk", "snuck", "piles", "orate", "joyed", "daily", "crone",
      "wager", "solos", "earns", "stark", "lauds", "kasey", "villa", "gnaws",
      "scent", "wears", "fains", "laced", "tamer", "pipes", "plant", "lorie",
      "rivet", "tamed", "cozen", "theme", "lifer", "sunny", "shags", "flack",
      "gassy", "eased", "jeeps", "shire", "fargo", "timer", "brash", "behan",
      "basin", "volga", "krone", "swiss", "docks", "booed", "ebert", "gusty",
      "delay", "oared", "grady", "buick", "curbs", "crete", "lucas", "strum",
      "besom", "gorse", "troth", "donne", "chink", "faced", "ahmed", "texas",
      "longs", "aloud", "bethe", "cacao", "hilda", "eagle", "karyn", "harks",
      "adder", "verse", "drays", "cello", "taped", "snide", "taxis", "kinky",
      "penes", "wicca", "sonja", "aways", "dyers", "bolas", "elfin", "slope",
      "lamps", "hutch", "lobed", "baaed", "masts", "ashes", "ionic", "joyce",
      "payed", "brays", "malts", "dregs", "leaky", "runny", "fecal", "woven",
      "hurls", "jorge", "henna", "dolby", "booty", "brett", "dykes", "rural",
      "fight", "feels", "flogs", "brunt", "preen", "elvis", "dopey", "gripe",
      "garry", "gamma", "fling", "space", "mange", "storm", "arron", "hairs",
      "rogue", "repel", "elgar", "ruddy", "cross", "medan", "loses", "howdy",
      "foams", "piker", "halts", "jewel", "avery", "stool", "cruel", "cases",
      "ruses", "cathy", "harem", "flour", "meted", "faces", "hobos", "charm",
      "jamar", "cameo", "crape", "hooey", "reefs", "denny", "mitts", "sores",
      "smoky", "nopes", "sooty", "twirl", "toads", "vader", "julep", "licks",
      "arias", "wrote", "north", "bunks", "heady", "batch", "snaps", "claws",
      "fouls", "faded", "beans", "wimps", "idled", "pulse", "goons", "noose",
      "vowed", "ronda", "rajas", "roast", "allah", "punic", "slows", "hours",
      "metal", "slier", "meaty", "hanna", "curvy", "mussy", "truth", "troys",
      "block", "reels", "print", "miffs", "busts", "bytes", "cream", "otter",
      "grads", "siren", "kilos", "dross", "batty", "debts", "sully", "bares",
      "baggy", "hippy", "berth", "gorky", "argon", "wacko", "harry", "smoke",
      "fails", "perms", "score", "steps", "unity", "couch", "kelly", "rumps",
      "fines", "mouth", "broth", "knows", "becky", "quits", "lauri", "trust",
      "grows", "logos", "apter", "burrs", "zincs", "buyer", "bayer", "moose",
      "overt", "croon", "ousts", "lands", "lithe", "poach", "jamel", "waive",
      "wiser", "surly", "works", "paine", "medal", "glads", "gybed", "paint",
      "lorre", "meant", "smugs", "bryon", "jinni", "sever", "viols", "flubs",
      "melts", "heads", "peals", "aiken", "named", "teary", "yalta", "styes",
      "heist", "bongs", "slops", "pouts", "grape", "belie", "cloak", "rocks",
      "scone", "lydia", "goofs", "rents", "drive", "crony", "orlon", "narks",
      "plays", "blips", "pence", "march", "alger", "baste", "acorn", "billy",
      "croce", "boone", "aaron", "slobs", "idyls", "irwin", "elves", "stoat",
      "doing", "globe", "verve", "icons", "trial", "olsen", "pecks", "there",
      "blame", "tilde", "milky", "sells", "tangy", "wrack", "fills", "lofty",
      "truce", "quark", "delia", "stowe", "marty", "overs", "putty", "coral",
      "swine", "stats", "swags", "weans", "spout", "bulky", "farsi", "brest",
      "gleam", "beaks", "coons", "hater", "peony", "huffy", "exert", "clips",
      "riven", "payer", "doped", "salas", "meyer", "dryad", "thuds", "tilts",
      "quilt", "jetty", "brood", "gulch", "corps", "tunic", "hubby", "slang",
      "wreck", "purrs", "punch", "drags", "chide", "sulks", "tints", "huger",
      "roped", "dopes", "booby", "rosin", "outer", "gusto", "tents", "elude",
      "brows", "lease", "ceres", "laxer", "worth", "necks", "races", "corey",
      "trait", "stuns", "soles", "teems", "scrip", "privy", "sight", "minor",
      "alisa", "stray", "spank", "cress", "nukes", "rises", "gusts", "aurae",
      "karma", "icing", "prose", "biked", "grand", "grasp", "skein", "shaky",
      "clump", "rummy", "stock", "twain", "zoned", "offed", "ghats", "mover",
      "randy", "vault", "craws", "thees", "salem", "downy", "sangs", "chore",
      "cited", "grave", "spinx", "erica", "raspy", "dying", "skips", "clerk",
      "paste", "moved", "rooks", "intel", "moses", "avers", "staid", "yawls",
      "blast", "lyres", "monks", "gaits", "floor", "saner", "waver", "assam",
      "infer", "wands", "bunch", "dryly", "weedy", "honey", "baths", "leach",
      "shorn", "shows", "dream", "value", "dooms", "spiro", "raped", "shook",
      "stead", "moran", "ditto", "loots", "tapir", "looms", "clove", "stops",
      "pinks", "soppy", "ripen", "wench", "shone", "bauds", "doric", "leans",
      "nadia", "cries", "camus", "boozy", "maris", "fools", "morns", "bides",
      "greek", "gauss", "roget", "lamar", "hazes", "beefy", "dupes", "refed",
      "felts", "larry", "guile", "ables", "wants", "warns", "toils", "bathe",
      "edger", "paced", "rinks", "shoos", "erich", "whore", "tiger", "jumpy",
      "lamas", "stack", "among", "punts", "scalp", "alloy", "solon", "quite",
      "comas", "whole", "parse", "tries", "reeve", "tiled", "deena", "roomy",
      "rodin", "aster", "twice", "musts", "globs", "parch", "drawn", "filch",
      "bonds", "tells", "droop", "janis", "holds", "scant", "lopes", "based",
      "keven", "whiny", "aspic", "gains", "franz", "jerri", "steel", "rowel",
      "vends", "yelps", "begin", "logic", "tress", "sunni", "going", "barge",
      "blood", "burns", "basks", "waifs", "bones", "skill", "hewer", "burly",
      "clime", "eking", "withs", "capek", "berta", "cheap", "films", "scoot",
      "tweed", "sizer", "wheat", "acton", "flung", "ponds", "tracy", "fiver",
      "berra", "roger", "mutes", "burke", "miked", "valve", "whisk", "runes",
      "parry", "toots", "japes", "roars", "rough", "irons", "romeo", "cages",
      "reeks", "cigar", "saiph", "dully", "hangs", "chops", "rolls", "prick",
      "acuff", "spent", "sulla", "train", "swell", "frets", "names", "anita",
      "crazy", "sixth", "blunt", "fewer", "large", "brand", "slick", "spitz",
      "rears", "ogres", "toffy", "yolks", "flock", "gnawn", "eries", "blink",
      "skier", "feted", "tones", "snail", "ether", "barbs", "noses", "hears",
      "upset", "awash", "cloud", "trunk", "degas", "dungs", "rated", "shall",
      "yeahs", "coven", "sands", "susan", "fable", "gunny", "began", "serfs",
      "balls", "dinky", "madge", "prong", "spilt", "lilly", "brawn", "comet",
      "spins", "raids", "dries", "sorts", "makes", "mason", "mayra", "royce",
      "stout", "mealy", "pagan", "nasal", "folds", "libby", "coups", "photo",
      "mosey", "amens", "speed", "lords", "board", "fetal", "lagos", "scope",
      "raked", "bonus", "mutts", "willy", "sport", "bingo", "thant", "araby",
      "bette", "rebel", "gases", "small", "humus", "grosz", "beset", "slays",
      "steve", "scrap", "blahs", "south", "pride", "heels", "tubes", "beady",
      "lacey", "genus", "mauls", "vying", "spice", "sexes", "ester", "drams",
      "today", "comae", "under", "jests", "direr", "yoked", "tempi", "early",
      "boats", "jesus", "warts", "guppy", "gilda", "quota", "token", "edwin",
      "ringo", "gaped", "lemon", "hurst", "manor", "arrow", "mists", "prize",
      "silas", "blobs", "diets", "ervin", "stony", "buddy", "bates", "rabid",
      "ducat", "ewing", "jaunt", "beads", "doyen", "blush", "thoth", "tiles",
      "piper", "short", "peron", "alley", "decks", "shunt", "whirs", "cushy",
      "roils", "betty", "plugs", "woken", "jibes", "foray", "merak", "ruing",
      "becks", "whale", "shoot", "dwelt", "spawn", "fairs", "dozed", "celts",
      "blond", "tikes", "sabin", "feint", "vamps", "cokes", "willa", "slues",
      "bills", "force", "curst", "yokel", "surer", "miler", "fices", "arced",
      "douse", "hilly", "lucio", "tongs", "togas", "minty", "sagas", "pates",
      "welsh", "bruno", "decal", "elate", "linux", "gyros", "pryor", "mousy",
      "pains", "shake", "spica", "pupal", "probe", "mount", "shirk", "purus",
      "kilns", "rests", "graze", "hague", "spuds", "sweep", "momma", "burch",
      "maces", "samar", "brace", "riser", "booms", "build", "camel", "flyer",
      "synge", "sauna", "tonga", "tings", "promo", "hides", "clair", "elisa",
      "bower", "reins", "diann", "lubed", "nulls", "picks", "laban", "milch",
      "buber", "stomp", "bosom", "lying", "haled", "avert", "wries", "macon",
      "skids", "fumed", "ogles", "clods", "antic", "nosey", "crimp", "purge",
      "mommy", "cased", "taxes", "covet", "clack", "butch", "panty", "lents",
      "machs", "exude", "tooth", "adore", "shuck", "asses", "after", "terra",
      "dices", "aryan", "regor", "romes", "stile", "cairo", "maura", "flail",
      "eaves", "estes", "sousa", "visas", "baron", "civet", "kitty", "freed",
      "ralph", "tango", "gawks", "cheat", "study", "fancy", "fiber", "musks",
      "souse", "brims", "claim", "bikes", "venue", "sired", "thymi", "rivas",
      "skimp", "pleas", "woman", "gimpy", "cawed", "minos", "pints", "knock",
      "poked", "bowen", "risky", "towel", "oinks", "linus", "heals", "pears",
      "codas", "inner", "pitch", "harpy", "niger", "madly", "bumpy", "stair",
      "files", "nobel", "celli", "spars", "jades", "balmy", "kooky", "plums",
      "trues", "gloss", "trims", "daunt", "tubby", "dared", "wadis", "smell",
      "darby", "stink", "drill", "dover", "ruler", "laden", "dikes", "layla",
      "fells", "maker", "joked", "horns", "these", "baize", "spahn", "whens",
      "edged", "mushy", "plume", "tucks", "spurs", "husky", "dried", "bigot",
      "pupas", "drily", "aware", "hagar", "newly", "knots", "pratt", "feces",
      "sabik", "watts", "cooke", "riles", "seamy", "fleas", "dusts", "barfs",
      "roans", "pawns", "vivid", "kirks", "tania", "feral", "tubae", "horne",
      "aries", "brits", "combs", "chunk", "stork", "waned", "texan", "elide",
      "glens", "emery", "autos", "trams", "dosed", "cheri", "baits", "jacks",
      "whose", "fazed", "matte", "swans", "maxed", "write", "spays", "orion",
      "traci", "horse", "stars", "strut", "goods", "verge", "scuff", "award",
      "dives", "wires", "burnt", "dimly", "sleds", "mayan", "biped", "quirk",
      "sofia", "slabs", "waste", "robby", "mayor", "fatty", "items", "bowel",
      "mires", "swarm", "route", "swash", "sooth", "paved", "steak", "upend",
      "sough", "throw", "perts", "stave", "carry", "burgs", "hilts", "plane",
      "toady", "nadir", "stick", "foist", "gnarl", "spain", "enter", "sises",
      "story", "scarf", "ryder", "glums", "nappy", "sixes", "honed", "marcy",
      "offer", "kneel", "leeds", "lites", "voter", "vince", "bursa", "heave",
      "roses", "trees", "argos", "leann", "grimy", "zelma", "crick", "tract",
      "flips", "folks", "smote", "brier", "moore", "goose", "baden", "riled",
      "looks", "sober", "tusks", "house", "acmes", "lubes", "chows", "neath",
      "vivas", "defer", "allay", "casey", "kmart", "pests", "proms", "eying",
      "cider", "leave", "shush", "shots", "karla", "scorn", "gifts", "sneer",
      "mercy", "copes", "faxed", "spurt", "monet", "awoke", "rocky", "share",
      "gores", "drawl", "tears", "mooed", "nones", "wined", "wrens", "modem",
      "beria", "hovel", "retch", "mates", "hands", "stymy", "peace", "carat",
      "coots", "hotel", "karen", "hayed", "mamet", "cuing", "paper", "rages",
      "suave", "reuse", "auden", "costs", "loner", "rapes", "hazel", "rites",
      "brent", "pumps", "dutch", "puffs", "noons", "grams", "teats", "cease",
      "honda", "pricy", "forgo", "fleck", "hired", "silos", "merge", "rafts",
      "halon", "larks", "deere", "jello", "cunts", "sifts", "boner", "morin",
      "mimes", "bungs", "marie", "harts", "snobs", "sonic", "hippo", "comes",
      "crops", "mango", "wrung", "garbs", "natty", "cents", "fitch", "moldy",
      "adams", "sorta", "coeds", "gilds", "kiddy", "nervy", "slurp", "ramon",
      "fuzed", "hiker", "winks", "vanes", "goody", "hawks", "crowd", "bract",
      "marla", "limbs", "solve", "gloom", "sloop", "eaton", "memos", "tames",
      "heirs", "berms", "wanes", "faint", "numbs", "holes", "grubs", "rakes",
      "waist", "miser", "stays", "antis", "marsh", "skyed", "payne", "champ",
      "jimmy", "clues", "fatal", "shoed", "freon", "lopez", "snowy", "loins",
      "stale", "thank", "reads", "isles", "grill", "align", "saxes", "rubin",
      "rigel", "walls", "beers", "wispy", "topic", "alden", "anton", "ducts",
      "david", "duets", "fries", "oiled", "waken", "allot", "swats", "woozy",
      "tuxes", "inter", "dunne", "known", "axles", "graph", "bumps", "jerry",
      "hitch", "crews", "lucia", "banal", "grope", "valid", "meres", "thick",
      "lofts", "chaff", "taker", "glues", "snubs", "trawl", "keels", "liker",
      "stand", "harps", "casks", "nelly", "debby", "panes", "dumps", "norma",
      "racks", "scams", "forte", "dwell", "dudes", "hypos", "sissy", "swamp",
      "faust", "slake", "maven", "lowed", "lilts", "bobby", "gorey", "swear",
      "nests", "marci", "palsy", "siege", "oozes", "rates", "stunt", "herod",
      "wilma", "other", "girts", "conic", "goner", "peppy", "class", "sized",
      "games", "snell", "newsy", "amend", "solis", "duane", "troop", "linda",
      "tails", "woofs", "scuds", "shies", "patti", "stunk", "acres", "tevet",
      "allen", "carpi", "meets", "trend", "salty", "galls", "crept", "toner",
      "panda", "cohen", "chase", "james", "bravo", "styed", "coals", "oates",
      "swami", "staph", "frisk", "cares", "cords", "stems", "razed", "since",
      "mopes", "rices", "junes", "raged", "liter", "manes", "rearm", "naive",
      "tyree", "medic", "laded", "pearl", "inset", "graft", "chair", "votes",
      "saver", "cains", "knobs", "gamay", "hunch", "crags", "olson", "teams",
      "surge", "wests", "boney", "limos", "ploys", "algae", "gaols", "caked",
      "molts", "glops", "tarot", "wheal", "cysts", "husks", "vaunt", "beaus",
      "fauns", "jeers", "mitty", "stuff", "shape", "sears", "buffy", "maced",
      "fazes", "vegas", "stamp", "borer", "gaged", "shade", "finds", "frock",
      "plods", "skied", "stump", "ripes", "chick", "cones", "fixed", "coled",
      "rodeo", "basil", "dazes", "sting", "surfs", "mindy", "creak", "swung",
      "cadge", "franc", "seven", "sices", "weest", "unite", "codex", "trick",
      "fusty", "plaid", "hills", "truck", "spiel", "sleek", "anons", "pupae",
      "chiba", "hoops", "trash", "noted", "boris", "dough", "shirt", "cowls",
      "seine", "spool", "miens", "yummy", "grade", "proxy", "hopes", "girth",
      "deter", "dowry", "aorta", "paean", "corms", "giant", "shank", "where",
      "means", "years", "vegan", "derek", "tales"};
  const vector<vector<string>> output5{
      s.findLadders("nanny", "aloud", word_list5)};
  cout
      << "s.findLadders(nanny, aloud, word_list5) -> " << output5
      << '\n';  // expected output:
                // [[nanny,canny,candy,sandy,sands,sends,seeds,sleds,slews,clews,clefs,cleft,cleat,bleat,bloat,float,flout,clout,cloud,aloud],
                // [nanny,danny,dandy,sandy,sands,sends,seeds,sleds,slews,clews,clefs,cleft,cleat,bleat,bloat,float,flout,clout,cloud,aloud]]

  cout << "Elapsed time: " << Solution::start_stop_timer() << " seconds\n";

  return 0;
}

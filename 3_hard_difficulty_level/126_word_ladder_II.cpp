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
  vector<string> current_sequence_{};
  vector<vector<string>> found_sequences_{};
  unordered_set<string> word_dict_{};
  string begin_word_{};
  string end_word_{};
  size_t word_len_{};
  size_t min_ladder_length_{};

  size_t find_min_ladder_length() {
    queue<string> q{{begin_word_}};

    vector<string> removed_dict_words{};
    removed_dict_words.reserve(word_dict_.size());
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
              if (end_word_ == next_word) {
                for (const string& w : removed_dict_words)
                  word_dict_.emplace(w);
                return min_seq_len;
              }
              word_dict_.erase(next_word);
              removed_dict_words.emplace_back(next_word);
              q.emplace(next_word);
            }
          }

          next_word[j] = temp_char;
        }
      }

      min_seq_len++;
    }

    for (const string& w : removed_dict_words)
      word_dict_.emplace(w);
    return 0;
  }

  void find_minimum_number_of_transformation_sequences(
      string current_word,
      vector<unordered_map<string, vector<char>>>&
          substr_key_missing_chars_dict,
      const size_t step_count) {
    if (step_count >= min_ladder_length_)
      return;

    string key{};
    key.reserve(word_len_);

    for (size_t i{}; i < current_word.length(); ++i) {
      const char orig_char{current_word[i]};
      key.clear();
      for (size_t j{}; j < word_len_; ++j) {
        if (i == j)
          continue;
        key.push_back(current_word[j]);
      }

      for (char& visited_ch : substr_key_missing_chars_dict[i].at(key)) {
        if (!visited_ch || orig_char == visited_ch)
          continue;
        current_word[i] = visited_ch;
        if (current_word == begin_word_) {
          current_sequence_.emplace_back(begin_word_);
          reverse(begin(current_sequence_), end(current_sequence_));
          found_sequences_.emplace_back(current_sequence_);
          reverse(begin(current_sequence_), end(current_sequence_));
          current_sequence_.pop_back();
          return;
        }

        visited_ch = 0;
        current_sequence_.emplace_back(current_word);
        find_minimum_number_of_transformation_sequences(
            current_word, substr_key_missing_chars_dict, step_count + 1);
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
      return {{}};

    const bool begin_word_found{word_dict_.find(begin_word_) !=
                                end(word_dict_)};
    word_dict_.erase(begin_word_);

    min_ladder_length_ = find_min_ladder_length();

    if (!min_ladder_length_)
      return {{}};
    if (2 == min_ladder_length_)
      return {{begin_word_, end_word_}};

    current_sequence_.clear();
    current_sequence_.emplace_back(end_word_);
    found_sequences_.clear();

    word_len_ = begin_word_.length();

    vector<unordered_map<string, vector<char>>> substr_key_existing_chars_dict(
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

    find_minimum_number_of_transformation_sequences(
        end_word_, substr_key_existing_chars_dict, 1);

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
       << '\n';  // expected output: 5

  /*
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
       << '\n';  // expected output: 5
  */

  cout << "Elapsed time: " << Solution::start_stop_timer() << " seconds\n";

  return 0;
}

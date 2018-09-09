/*
377. Combination sum IV (difficulty level: medium)

Given an integer array with all positive numbers and no duplicates, find the
number of possible combinations that add up to a positive integer target.

Example:

nums = [1,2,3]
target = 4

The possible combination ways are:
(1, 1, 1, 1)
(1, 1, 2)
(1, 2, 1)
(1, 3)
(2, 1, 1)
(2, 2)
(3, 1)

Note that different sequences are counted as different combinations.

Therefore the output is 7.

Follow up:
What if negative numbers are allowed in the given array?
How does it change the problem?
What limitation we need to add to the question to allow negative numbers?
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int combinationSum4(const vector<int>& nums, const int target) {
    const int dp_size{target + 1};
    vector<int> dp(dp_size, 0);
    dp[0] = 1;
    for (int i{1}; i < dp_size; i++) {
      for (size_t j{}; j < nums.size(); j++)
        dp[i] += i - nums[j] < 0 ? 0 : dp[i - nums[j]];
    }
    return dp[target];
  }
};

int main() {
  Solution s{};
  vector<int> input{1, 2, 3};
  cout << "s.combinationSum4([1, 2, 3], 4) -> " << s.combinationSum4(input, 4)
       << '\n';
  input.assign({1, 50});
  cout << "s.combinationSum4([1, 50], 200) -> " << s.combinationSum4(input, 200)
       << '\n';  // expected output: 28730
  input.assign({3, 33, 333});
  cout << "s.combinationSum4([3, 33, 333], 20000) -> "
       << s.combinationSum4(input, 20000) << '\n';  // expected output: 0

  input.assign({13,  17,  19,  23,  29,  31,  37,  41,  43,  47,  53,  59,
                61,  67,  71,  73,  79,  83,  89,  97,  101, 103, 107, 109,
                113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179,
                181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241,
                251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313,
                317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389,
                397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461,
                463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547,
                557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 615});
  cout << "s.combinationSum4([13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,"
          "79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,"
          "173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,"
          "269,271,277,281,283,293,307,311,313,317,331,337,347,349,353,359,367,"
          "373,379,383,389,397,401,409,419,421,431,433,439,443,449,457,461,463,"
          "467,479,487,491,499,503,509,521,523,541,547,557,563,569,571,577,587,"
          "593,599,601,607,615], 220) -> "
       << s.combinationSum4(input, 220) << '\n';  // expected output: 45452242

  input.assign({10,  20,  30,  40,  50,  60,  70,  80,  90,  100, 110, 120, 130,
                140, 150, 160, 170, 180, 190, 200, 210, 220, 230, 240, 250, 260,
                270, 280, 290, 300, 310, 320, 330, 340, 350, 360, 370, 380, 390,
                400, 410, 420, 430, 440, 450, 460, 470, 480, 490, 500, 510, 520,
                530, 540, 550, 560, 570, 580, 590, 600, 610, 620, 630, 640, 650,
                660, 670, 680, 690, 700, 710, 720, 730, 740, 750, 760, 770, 780,
                790, 800, 810, 820, 830, 840, 850, 860, 870, 880, 890, 900, 910,
                920, 930, 940, 950, 960, 970, 980, 990, 111});
  cout << "s.combinationSum4([10,20,30,40,50,60,70,80,90,100,110,120,130,140,"
          "150,160,170,180,190,200,210,220,230,240,250,260,270,280,290,300,310,"
          "320,330,340,350,360,370,380,390,400,410,420,430,440,450,460,470,480,"
          "490,500,510,520,530,540,550,560,570,580,590,600,610,620,630,640,650,"
          "660,670,680,690,700,710,720,730,740,750,760,770,780,790,800,810,820,"
          "830,840,850,860,870,880,890,900,910,920,930,940,950,960,970,980,990,"
          "111], 999) -> "
       << s.combinationSum4(input, 999) << '\n';  // expected output: 1

  return 0;
}

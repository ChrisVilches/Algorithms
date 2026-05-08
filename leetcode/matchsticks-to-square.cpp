#include <bits/stdc++.h>
using namespace std;

class Solution {
  vector<int> nums;
  int total;
  map<tuple<int, int, int>, bool> memo;

  bool dp(const int bitmask, const int length, const int sides) {
    const auto key = make_tuple(bitmask, length, sides);

    if (sides == 4) return true;
    if (memo.count(key)) return memo[key];

    bool res = false;

    for (size_t i = 0; i < nums.size(); i++) {
      if ((bitmask & (1 << i)) != 0) continue;

      const int new_length = length + nums[i];

      if (new_length > total / 4) continue;

      if (new_length == total / 4) {
        res = res || dp(bitmask | (1 << i), 0, sides + 1);
      } else {
        res = res || dp(bitmask | (1 << i), new_length, sides);
      }
    }

    return memo[key] = res;
  }

 public:
  bool makesquare(const vector<int>& matchsticks) {
    this->nums = matchsticks;

    total = accumulate(nums.begin(), nums.end(), 0);
    if (total % 4 != 0) return false;

    return dp(0, 0, 0);
  }
};

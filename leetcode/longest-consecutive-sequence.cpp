#include <bits/stdc++.h>
using namespace std;

class Solution {
  unordered_set<int> num_set;
  unordered_map<int, int> memo;

  int calculate(const int x) {
    if (memo.count(x)) return memo[x];
    if (!num_set.count(x)) return 0;
    return memo[x] = 1 + calculate(x + 1);
  }

 public:
  int longestConsecutive(const vector<int>& nums) {
    this->num_set = {nums.begin(), nums.end()};

    int ans = 0;
    for (const auto x : nums) {
      ans = max(ans, calculate(x));
    }
    return ans;
  }
};

#include <bits/stdc++.h>
using namespace std;

class Solution {
  int memo[100'000];
  vector<int> stones;
  int dp(const int i) {
    if (i >= stones.size()) return 0;
    if (memo[i] != -1) return memo[i];

    int res = -1e8;

    int accum = 0;
    for (int n = 0; n < 3; n++) {
      if (i + n >= stones.size()) break;

      accum += stones[i + n];
      res = max(res, accum - dp(i + n + 1));
    }

    return memo[i] = res;
  }

 public:
  string stoneGameIII(vector<int>& stoneValue) {
    memset(memo, -1, sizeof memo);
    this->stones = stoneValue;
    const int res = dp(0);

    if (res > 0) {
      return "Alice";
    } else if (res < 0) {
      return "Bob";
    }

    return "Tie";
  }
};

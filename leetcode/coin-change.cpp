#include <bits/stdc++.h>
using namespace std;

class Solution {
  vector<int> coins;
  int memo[15][10'007];

  long long dp(const size_t idx, const int amount) {
    if (amount == 0) return 0;
    if (idx == coins.size()) return INT_MAX;
    if (~memo[idx][amount]) return memo[idx][amount];

    long long res = INT_MAX;

    for (int cnt = 0;; cnt++) {
      const int new_amount = amount - (cnt * coins[idx]);
      if (new_amount < 0) break;
      res = min(res, cnt + dp(idx + 1, new_amount));
    }

    return memo[idx][amount] = res;
  }

 public:
  int coinChange(const vector<int>& arr, const int amount) {
    memset(memo, -1, sizeof memo);
    this->coins = arr;
    const int ans = dp(0, amount);

    if (ans == INT_MAX) return -1;

    return ans;
  }
};

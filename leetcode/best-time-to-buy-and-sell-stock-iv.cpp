#include <bits/stdc++.h>
using namespace std;

class Solution {
  int memo[1001][101];
  vector<int> prices;

  int dp(const int idx, const int k) {
    if (k == 0) return 0;
    if (idx == (int)prices.size()) return 0;
    if (~memo[idx][k]) return memo[idx][k];

    int result = 0;

    for (int i = idx; i < (int)prices.size(); i++) {
      const int profit = max(prices[i] - prices[idx], 0);
      result = max(result, profit + dp(i + 1, k - 1));
      result = max(result, dp(i + 1, k));
    }

    return memo[idx][k] = result;
  }

 public:
  int maxProfit(const int k, const vector<int>& prices) {
    memset(memo, -1, sizeof memo);
    this->prices = prices;
    return dp(0, k);
  }
};

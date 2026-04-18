#include <bits/stdc++.h>
using namespace std;

class Solution {
  vector<int> memo = vector<int>(30'007, -1);
  vector<int> prices;

  int dp(const int idx) {
    if (idx == (int)prices.size()) return 0;
    if (~memo[idx]) return memo[idx];

    int result = 0;

    for (int i = idx; i < (int)prices.size(); i++) {
      const int profit = max(prices[i] - prices[idx], 0);
      result = max(result, profit + dp(i + 1));
    }

    return memo[idx] = result;
  }

 public:
  int maxProfit(const vector<int>& prices) {
    this->prices = prices;
    return dp(0);
  }
};

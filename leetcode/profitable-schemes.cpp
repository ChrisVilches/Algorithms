#include <bits/stdc++.h>
using namespace std;

class Solution {
  using ll = long long;
  const ll mod = 1e9 + 7;
  vector<int> group, profit;
  int memo[101][101][101];

  int dp(const int i, const int rem_profit, const int members) {
    if (members < 0) return 0;
    if (i == (int)group.size()) return rem_profit == 0;

    int& m = memo[i][rem_profit][members];
    if (~m) return m;

    const ll take = dp(i + 1, max(rem_profit - profit[i], 0), members - group[i]);
    const ll dont_take = dp(i + 1, rem_profit, members);
    return m = (take + dont_take) % mod;
  }

 public:
  int profitableSchemes(const int n, const int minProfit, const vector<int>& group,
                        const vector<int>& profit) {
    memset(memo, -1, sizeof memo);
    this->group = group;
    this->profit = profit;
    return dp(0, minProfit, n);
  }
};

#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int minimumCoins(const vector<int>& prices) {
    const int n = prices.size();
    vector<int> dp(n, INT_MAX);
    dp.back() = prices.back();

    deque<int> q{n - 1};

    for (int i = n - 2; i >= 0; i--) {
      const int last_idx = i + i + 2;

      while (last_idx < q.back()) q.pop_back();

      dp[i] = prices[i] + (last_idx < n ? dp[last_idx] : 0);
      dp[i] = min(dp[i], prices[i] + dp[q.back()]);

      while (!q.empty() && dp[q.front()] > dp[i]) q.pop_front();

      q.emplace_front(i);
    }

    return dp.front();
  }
};

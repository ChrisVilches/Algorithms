#include <bits/stdc++.h>
using namespace std;

class Solution {
  const long long mod = 1e9 + 7;
  int memo[308][308];
  vector<int> pows;

  int dp(const int n, const int curr) {
    if (n == 0) return 1;
    if (~memo[n][curr]) return memo[n][curr];

    long long res = 0;

    for (size_t i = curr + 1; i < pows.size(); i++) {
      const int val = pows[i];

      if (n - val < 0) break;

      res += dp(n - val, i);
    }

    return memo[n][curr] = res % mod;
  }

 public:
  int numberOfWays(const int n, const int x) {
    for (int i = 0;; i++) {
      const auto val = pow(i, x);
      if (val > n) break;
      pows.emplace_back(val);
    }

    memset(memo, -1, sizeof memo);
    return dp(n, 0);
  }
};

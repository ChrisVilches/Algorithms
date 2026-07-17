#include <bits/stdc++.h>
using namespace std;

class Solution {
  const int MOD = 1e9 + 7;

 public:
  int distinctSubseqII(const string s) {
    const int n = s.size();

    vector<long long> dp(n + 1, 0);
    dp[0] = 1;

    unordered_map<char, int> last_idx;

    for (int i = 1; i <= n; ++i) {
      dp[i] = dp[i - 1] * 2;

      if (last_idx.count(s[i - 1])) {
        dp[i] -= dp[last_idx[s[i - 1]] - 1];
      }

      dp[i] = (dp[i] + MOD) % MOD;

      last_idx[s[i - 1]] = i;
    }

    return (dp[n] - 1 + MOD) % MOD;
  }
};

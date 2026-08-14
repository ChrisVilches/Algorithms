#include <bits/stdc++.h>
using namespace std;

class Solution {
  using ll = long long;
  const ll mod = 1e9 + 7;
  int memo[37][1007];
  int n, k;

  int dp(const int idx, const int target) {
    if (idx == n) return target == 0;
    if (target < 0) return 0;
    if (~memo[idx][target]) return memo[idx][target];

    ll res = 0;

    for (int i = 1; i <= k; i++) {
      res += dp(idx + 1, target - i);
      res %= mod;
    }

    return memo[idx][target] = res;
  }

 public:
  int numRollsToTarget(const int N, const int K, const int target) {
    memset(memo, -1, sizeof memo);
    this->n = N;
    this->k = K;

    return dp(0, target);
  }
};

#include <bits/stdc++.h>
using namespace std;

class Solution {
  const long long mod = 1e9 + 7;
  const array<int, 3> colors{1, 2, 3};

  int memo[5001][4][4][4];

  long long dp(const int rem, const int a, const int b, const int c) {
    int& m = memo[rem][a][b][c];
    if (~m) return m;
    if (rem == 0) return 1;

    long long res = 0;

    for (const int i : colors) {
      for (const int j : colors) {
        for (const int k : colors) {
          if (i == j || j == k) continue;
          if (i == a || j == b || k == c) continue;
          res += dp(rem - 1, i, j, k);
          res %= mod;
        }
      }
    }

    return m = res;
  }

 public:
  int numOfWays(const int n) {
    memset(memo, -1, sizeof memo);
    return dp(n, 0, 0, 0);
  }
};

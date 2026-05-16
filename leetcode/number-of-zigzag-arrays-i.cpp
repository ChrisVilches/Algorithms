#include <bits/stdc++.h>
using namespace std;

class Solution {
  const long long mod = 1e9 + 7;
  const int max_n = 2007;

 public:
  int zigZagArrays(const int n, const int l, const int r) {
    vector<array<int, 2>> dp1(max_n), dp2(max_n);

    for (int v = l; v <= r; v++) {
      dp1[v] = {1, 1};
    }

    for (int iter = 1; iter <= n; iter++) {
      for (int v = r, accum = 0; v >= l; v--) {
        accum += dp1[v + 1][0];
        accum %= mod;
        dp2[v][1] = accum;
      }

      for (int v = l, accum = 0; v <= r; v++) {
        accum += dp1[v - 1][1];
        accum %= mod;
        dp2[v][0] = accum;
      }

      swap(dp1, dp2);
    }

    return (dp1[l][1] + dp1[r][0]) % mod;
  }
};

#include <bits/stdc++.h>
using namespace std;

class Solution {
  const long long mod = 1e9 + 7;
  int n, m, psum[52][52], memo[51][51][11];

  bool valid(const int i, const int j, const int u, const int v) {
    return psum[u][v] - psum[i - 1][v] - psum[u][j - 1] + psum[i - 1][j - 1] > 0;
  }

  long long dp(const int u, const int v, const int k) {
    if (k == 0 && valid(u + 1, v + 1, n, m)) return 1;
    if (~memo[u][v][k]) return memo[u][v][k];

    long long res = 0;

    for (int i = u + 1; i < n; i++) {
      if (!valid(u + 1, v + 1, i, m)) continue;
      res += dp(i, v, k - 1);
      res %= mod;
    }

    for (int j = v + 1; j < m; j++) {
      if (!valid(u + 1, v + 1, n, j)) continue;
      res += dp(u, j, k - 1);
      res %= mod;
    }

    return memo[u][v][k] = res;
  }

 public:
  int ways(const vector<string>& pizza, const int k) {
    memset(memo, -1, sizeof memo);
    memset(psum, 0, sizeof psum);
    this->n = pizza.size();
    this->m = pizza.front().size();
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        psum[i][j] = (pizza[i - 1][j - 1] == 'A') - psum[i - 1][j - 1] + psum[i - 1][j] +
                     psum[i][j - 1];
      }
    }
    return dp(0, 0, k - 1);
  }
};

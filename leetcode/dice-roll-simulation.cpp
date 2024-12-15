#include <bits/stdc++.h>
using namespace std;

class Solution {
  const long long mod = 1e9 + 7;
  vector<int> roll_max;
  int memo[5007][8][17];
  int n;

  int dp(const int i, const int prev, const int times) {
    if (prev != 0 && times > roll_max[prev - 1]) return 0;
    if (i == n) return 1;
    int& m = memo[i][prev][times];
    if (m != -1) return m;

    long long res = 0;

    for (int d = 1; d <= 6; d++) {
      res += dp(i + 1, d, d == prev ? times + 1 : 1);
      res %= mod;
    }

    return m = res;
  }

 public:
  int dieSimulator(const int n, const vector<int>& rollMax) {
    memset(memo, -1, sizeof memo);
    this->roll_max = rollMax;
    this->n = n;
    return dp(0, 0, 0);
  }
};

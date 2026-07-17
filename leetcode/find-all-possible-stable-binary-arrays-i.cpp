#include <bits/stdc++.h>
using namespace std;

constexpr int max_n = 201;
int memo[2][max_n][max_n][max_n];

class Solution {
  const long long mod = 1e9 + 7;
  int limit;

  int dp(const bool is_one, const int z, const int o, const int consec) {
    if (z < 0 || o < 0 || consec > limit) return 0;
    if (z == 0 && o == 0) return 1;

    int& m = memo[is_one][z][o][consec];
    if (~m) return m;

    return m = (dp(true, z, o - 1, is_one ? consec + 1 : 1) +
                dp(false, z - 1, o, is_one ? 1 : consec + 1)) %
               mod;
  }

 public:
  int numberOfStableArrays(const int zero, const int one, const int limit_input) {
    memset(memo, -1, sizeof memo);
    this->limit = limit_input;
    return dp(false, zero, one, 0);
  }
};

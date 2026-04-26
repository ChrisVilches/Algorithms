#include <bits/stdc++.h>
using namespace std;

class Solution {
  int memo[1007][1007];
  string s, t;

  int dp(const size_t i, const size_t j) {
    if (~memo[i][j]) return memo[i][j];

    if (j == t.size()) return 1;
    if (i == s.size()) return 0;

    return memo[i][j] = dp(i + 1, j) + (s[i] == t[j] ? dp(i + 1, j + 1) : 0);
  }

 public:
  int numDistinct(const string source, const string target) {
    s = source;
    t = target;
    memset(memo, -1, sizeof memo);
    return dp(0, 0);
  }
};

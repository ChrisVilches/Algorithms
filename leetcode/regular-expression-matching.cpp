#include <bits/stdc++.h>
using namespace std;

class Solution {
  string s, p;
  int memo[21][21];

  int dp(const int i, const int j) {
    if (j == (int)p.size()) return i == (int)s.size();
    if (~memo[i][j]) return memo[i][j];

    bool res;

    if (j < (int)p.size() - 1 && p[j + 1] == '*') {
      if (i == (int)s.size()) {
        res = dp(i, j + 2);
      } else if (p[j] == '.') {
        res = dp(i + 1, j) || dp(i, j + 2);
      } else {
        res = dp(i, j + 2) || (s[i] == p[j] && (dp(i + 1, j) || dp(i + 1, j + 2)));
      }
    } else {
      if (i == (int)s.size()) {
        res = false;
      } else if (p[j] == '.') {
        res = dp(i + 1, j + 1);
      } else {
        res = s[i] == p[j] && dp(i + 1, j + 1);
      }
    }

    return memo[i][j] = res;
  }

 public:
  bool isMatch(const string s, const string p) {
    memset(memo, -1, sizeof memo);
    this->s = s;
    this->p = p;
    return dp(0, 0);
  }
};

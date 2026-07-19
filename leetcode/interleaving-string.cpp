#include <bits/stdc++.h>
using namespace std;

class Solution {
  string s1, s2, s3;
  int memo[201][201];

  bool dp(const int i, const int j) {
    if (i == (int)s1.size() && j == (int)s2.size()) return true;
    if (~memo[i][j]) return memo[i][j];

    bool res = false;
    const char c = s3[i + j];

    if (i < (int)s1.size()) {
      res = res || (c == s1[i] && dp(i + 1, j));
    }

    if (j < (int)s2.size()) {
      res = res || (c == s2[j] && dp(i, j + 1));
    }

    return memo[i][j] = res;
  }

 public:
  bool isInterleave(const string s1, const string s2, const string s3) {
    memset(memo, -1, sizeof memo);
    this->s1 = s1;
    this->s2 = s2;
    this->s3 = s3;

    if (s1.size() + s2.size() != s3.size()) return false;

    return dp(0, 0);
  }
};

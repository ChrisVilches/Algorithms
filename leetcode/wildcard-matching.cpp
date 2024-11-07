#include <bits/stdc++.h>
using namespace std;

class Solution {
  string s, p;
  int n, m;
  unordered_map<int, unordered_map<int, bool>> memo;

  bool dp(const int i, const int j) {
    if (i == n) return j == m || (j == m - 1 && p.back() == '*');
    if (i != n && j == m) return false;

    if (memo[i].count(j)) return memo[i][j];

    switch (p[j]) {
      case '?':
        memo[i][j] = dp(i + 1, j + 1);
        break;
      case '*':
        memo[i][j] = dp(i, j + 1) || dp(i + 1, j);
        break;
      default:
        memo[i][j] = s[i] == p[j] && dp(i + 1, j + 1);
    }

    return memo[i][j];
  }

 public:
  bool isMatch(string s, string p) {
    this->s = s;

    for (const char c : p) {
      if (this->p.empty() || c != '*' || this->p.back() != '*') {
        this->p += c;
      }
    }

    n = this->s.size();
    m = this->p.size();

    return dp(0, 0);
  }
};

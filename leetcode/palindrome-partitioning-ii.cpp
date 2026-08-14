#include <bits/stdc++.h>
using namespace std;

class Solution {
  string s;
  int memo[2001];

  bool is_palindrome(const int from, const int to) {
    for (int i = from; i <= (from + to) / 2; i++) {
      if (s[i] != s[to - i + from]) return false;
    }
    return true;
  }

  int dp(const int idx) {
    const int n = s.size();
    if (idx == n) return 0;
    if (is_palindrome(idx, n - 1)) return 0;
    if (~memo[idx]) return memo[idx];

    int res = 1e5;

    for (int i = idx; i < n; i++) {
      if (!is_palindrome(idx, i)) continue;

      res = min(res, 1 + dp(i + 1));
    }

    return memo[idx] = res;
  }

 public:
  int minCut(const string input) {
    memset(memo, -1, sizeof memo);
    this->s = input;
    return dp(0);
  }
};

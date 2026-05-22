#include <bits/stdc++.h>
using namespace std;

class Solution {
  string s;
  int memo[107][107];

  int dp(const int from, const int to) {
    if (from == (int)s.size()) return 0;
    if (from == to) return 1;
    if (memo[from][to] != -1) return memo[from][to];

    int res = 1 + dp(from + 1, to);

    for (int i = from + 1; i <= to; i++) {
      const int same = s[i] == s[from];
      const int value = 1 + dp(from + 1, i - 1) + dp(i, to) - same;

      res = min(res, value);
    }

    return memo[from][to] = res;
  }

  string compress(const string s) {
    string res;

    for (const char c : s) {
      if (res.empty() || res.back() != c) res += c;
    }

    return res;
  }

 public:
  int strangePrinter(const string s) {
    this->s = compress(s);
    memset(memo, -1, sizeof memo);
    return dp(0, this->s.size() - 1);
  }
};

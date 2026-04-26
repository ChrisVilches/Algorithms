#include <bits/stdc++.h>
using namespace std;

class Solution {
  string a, b;
  int n, m;
  int memo[507][507];

  int dp(const int i, const int j) {
    if (i == n || j == m) return max(n - i, m - j);
    if (~memo[i][j]) return memo[i][j];

    if (a[i] == b[j]) {
      return memo[i][j] = dp(i + 1, j + 1);
    }

    return memo[i][j] = 1 + min({
                                dp(i + 1, j),
                                dp(i, j + 1),
                                dp(i + 1, j + 1),
                            });
  }

 public:
  int minDistance(const string word1, const string word2) {
    memset(memo, -1, sizeof memo);
    this->a = word1;
    this->b = word2;
    this->n = a.size();
    this->m = b.size();
    return dp(0, 0);
  }
};

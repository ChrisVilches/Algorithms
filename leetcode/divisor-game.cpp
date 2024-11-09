#include <bits/stdc++.h>
using namespace std;

class Solution {
  vector<int> memo;

  bool dp(const int n) {
    if (n == 1) return false;
    if (memo[n] != -1) return memo[n];

    for (int x = 1; x < n; x++) {
      if (n % x != 0) continue;

      if (!dp(n - x)) {
        return memo[n] = true;
      }
    }

    return memo[n] = false;
  }

 public:
  bool divisorGame(int n) {
    memo.assign(n + 1, -1);
    return dp(n);
  }
};

#include <bits/stdc++.h>
using namespace std;

class Solution {
  vector<int> squares;
  int memo[100'001];

  bool dp(const int n) {
    if (n == 0) return false;
    if (memo[n] != -1) return memo[n];

    for (const int s : squares) {
      if (s > n) break;
      if (!dp(n - s)) {
        return memo[n] = true;
      }
    }

    return memo[n] = false;
  }

 public:
  bool winnerSquareGame(int n) {
    memset(memo, -1, sizeof memo);

    for (int i = 1;; i++) {
      const int sq = i * i;
      if (sq > 100'000) break;
      squares.emplace_back(sq);
    }

    return dp(n);
  }
};

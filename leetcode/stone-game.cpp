#include <bits/stdc++.h>
using namespace std;

class Solution {
  vector<int> piles;
  int memo[501][501];

  int dp(const int i, const int j) {
    if (j - i + 1 == 2) return max(piles[i], piles[j]);

    if (memo[i][j] != -1) return memo[i][j];

    const int left = piles[i] - dp(i + 1, j);
    const int right = piles[j] - dp(i, j - 1);

    return memo[i][j] = max(left, right);
  }

 public:
  bool stoneGame(vector<int>& piles) {
    memset(memo, -1, sizeof memo);
    this->piles = piles;
    return dp(0, piles.size() - 1) > 0;
  }
};

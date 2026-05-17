#include <bits/stdc++.h>
using namespace std;

class Solution {
  vector<int> piles;
  int memo[101][101][101];

  int dp(const int i, const int j, const int M) {
    if (i > j) return 0;

    if (memo[i][j][M] != -1) return memo[i][j][M];

    int res = -1e7;

    int accum = 0;

    for (int x = 0; x < min(2 * M, j - i + 1); x++) {
      accum += piles[i + x];
      res = max(res, accum - dp(i + x + 1, j, max(M, x + 1)));
    }

    return memo[i][j][M] = res;
  }

 public:
  int stoneGameII(vector<int>& piles) {
    memset(memo, -1, sizeof memo);
    this->piles = piles;

    const int diff = dp(0, piles.size() - 1, 1);
    const int sum = accumulate(piles.begin(), piles.end(), 0);
    return diff + (sum - diff) / 2;
  }
};

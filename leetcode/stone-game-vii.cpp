#include <bits/stdc++.h>
using namespace std;

class Solution {
  vector<int> psum;
  vector<int> stones;
  int memo[1001][1001];
  int range_sum(const int l, const int r) { return psum[r + 1] - psum[l]; }

  int dp(const int i, const int j) {
    if (j - i <= 1) return max(stones[i], stones[j]);
    if (memo[i][j] != -1) return memo[i][j];

    const int left = range_sum(i + 1, j) - dp(i + 1, j);
    const int right = range_sum(i, j - 1) - dp(i, j - 1);
    return memo[i][j] = max(left, right);
  }

 public:
  int stoneGameVII(vector<int>& stones) {
    memset(memo, -1, sizeof memo);
    this->stones = stones;
    psum.emplace_back(0);
    for (const int s : stones) {
      psum.emplace_back(psum.back() + s);
    }
    return dp(0, stones.size() - 1);
  }
};

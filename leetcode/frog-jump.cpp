#include <bits/stdc++.h>
using namespace std;

class Solution {
  int first_stone, last_stone;
  set<int> stones;
  unordered_map<int, unordered_map<int, int>> memo;

  int dp(const int i, const int j) {
    if (j < 1) return false;
    if (i == last_stone) return true;
    if (!stones.count(i)) return false;
    if (memo[i].count(j)) return memo[i][j];

    if (i == first_stone) {
      return memo[i][j] = dp(i + 1, 1);
    }

    return memo[i][j] = dp(i + j - 1, j - 1) || dp(i + j, j) || dp(i + j + 1, j + 1);
  }

 public:
  bool canCross(const vector<int>& stones) {
    first_stone = stones.front();
    last_stone = stones.back();
    this->stones = {stones.begin(), stones.end()};
    return dp(0, 1);
  }
};

#include <bits/stdc++.h>
using namespace std;

class Solution {
  string ring, key;
  int memo[101][101];

  int dp(const int i, const int j) {
    if (j == (int)key.size()) return 0;
    if (~memo[i][j]) return memo[i][j];

    int result = INT_MAX;

    for (const int d : {-1, 1}) {
      for (int k = i, steps = 1;; k += d, steps++) {
        k = (k + ring.size()) % ring.size();

        if (ring[k] == key[j]) {
          result = min(result, steps + dp(k, j + 1));
          break;
        }
      }
    }

    return memo[i][j] = result;
  }

 public:
  int findRotateSteps(const string ring, const string key) {
    this->ring = ring;
    this->key = key;
    memset(memo, -1, sizeof memo);

    return dp(0, 0);
  }
};

#include <bits/stdc++.h>
using namespace std;

class Solution {
  const array<string, 5> grid{"ABCDEF", "GHIJKL", "MNOPQR", "STUVWX", "YZ"};
  int memo[301][301];
  int dist[26][26];

  int dp(const int idx1, const int idx2, const string& w) {
    const int n = w.size();
    if (idx1 == n - 1 || idx2 == n - 1) return 0;
    if (~memo[idx1][idx2]) return memo[idx1][idx2];

    const int j = max(idx1, idx2) + 1;

    int res = dist[w[idx1] - 'A'][w[j] - 'A'] + dp(j, idx2, w);

    if (idx2 == 0) {
      res = min(res, dp(idx1, j, w));
    } else {
      res = min(res, dist[w[idx2] - 'A'][w[j] - 'A'] + dp(idx1, j, w));
    }

    return memo[idx1][idx2] = res;
  }

 public:
  int minimumDistance(const string word) {
    memset(memo, -1, sizeof memo);

    array<pair<int, int>, 26> pos;

    for (size_t i = 0; i < grid.size(); i++) {
      for (size_t j = 0; j < grid[i].size(); j++) {
        const char c = grid[i][j];
        pos[c - 'A'] = {i, j};
      }
    }

    for (char i = 'A'; i <= 'Z'; i++) {
      for (char j = 'A'; j <= 'Z'; j++) {
        const auto [x1, y1] = pos[i - 'A'];
        const auto [x2, y2] = pos[j - 'A'];
        dist[i - 'A'][j - 'A'] = abs(x1 - x2) + abs(y1 - y2);
      }
    }

    return dp(0, 0, word);
  }
};

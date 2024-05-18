#include <bits/stdc++.h>
using namespace std;

const int di[] = {0, 1};
const int dj[] = {1, 0};

class Solution {
  int n, m;
  vector<vector<int>> dungeon;
  int healths[201][201];
  bool visited[201][201];

  bool possible(const int health) {
    memset(healths, 0, sizeof healths);
    memset(visited, 0, sizeof visited);

    healths[0][0] = health + dungeon.at(0).at(0);
    visited[0][0] = true;

    queue<pair<int, int>> q;
    q.emplace(0, 0);

    while (!q.empty()) {
      const auto [i, j] = q.front();
      q.pop();

      const int h = healths[i][j];

      if (h <= 0) continue;

      if (i == n - 1 && j == m - 1) return true;

      for (int d = 0; d < 2; d++) {
        const int i2 = i + di[d];
        const int j2 = j + dj[d];

        if (i2 >= n || j2 >= m) continue;

        const int h2 = h + dungeon[i2][j2];
        if (h2 <= 0) continue;

        healths[i2][j2] = max(healths[i2][j2], h2);

        if (visited[i2][j2]) continue;
        q.emplace(i2, j2);
        visited[i2][j2] = true;
      }
    }

    return false;
  }

 public:
  int calculateMinimumHP(vector<vector<int>>& dungeon) {
    this->dungeon = dungeon;
    n = dungeon.size();
    m = dungeon.front().size();

    int lo = 1;
    int hi = 10000;
    while (lo < hi) {
      const int mid = (lo + hi) / 2;
      if (possible(mid)) {
        hi = mid;
      } else {
        lo = mid + 1;
      }
    }

    return hi;
  }
};

#include <bits/stdc++.h>
using namespace std;

class Solution {
  const int di[4]{-1, 1, 0, 0};
  const int dj[4]{0, 0, -1, 1};

 public:
  int cutOffTree(vector<vector<int>>& forest) {
    const int n = forest.size();
    const int m = forest.front().size();

    set<int> trees;

    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        if (forest[i][j] > 1) trees.emplace(forest[i][j]);

    queue<tuple<int, int, int>> q;
    q.emplace(0, 0, 0);

    while (!trees.empty()) {
      vector<vector<bool>> visited(n, vector<bool>(m, false));

      while (!q.empty()) {
        const auto [i, j, dist] = q.front();
        visited[i][j] = true;
        q.pop();

        if (forest[i][j] == *trees.begin()) {
          q = queue<tuple<int, int, int>>();
          q.emplace(i, j, dist);
          trees.erase(trees.begin());
          forest[i][j] = 1;
          if (trees.empty()) return dist;
          break;
        }

        for (int d = 0; d < 4; d++) {
          const int i2 = i + di[d];
          const int j2 = j + dj[d];
          if (i2 < 0 || j2 < 0 || i2 >= n || j2 >= m) continue;
          if (forest[i2][j2] == 0 || visited[i2][j2]) continue;
          q.emplace(i2, j2, dist + 1);
          visited[i2][j2] = true;
        }
      }

      if (q.empty()) return -1;
    }

    assert(false);
  }
};

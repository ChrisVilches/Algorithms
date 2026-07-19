#include <bits/stdc++.h>
using namespace std;

struct DisjointSets {
  DisjointSets(int n) : parent(n), rank(n, 0) { iota(parent.begin(), parent.end(), 0); }

  int find(const int u) {
    if (u != parent[u]) parent[u] = find(parent[u]);
    return parent[u];
  }

  void merge(int x, int y) {
    x = find(x), y = find(y);
    if (rank[x] > rank[y])
      parent[y] = x;
    else
      parent[x] = y;

    if (rank[x] == rank[y]) rank[y]++;
  }

 private:
  vector<int> parent, rank;
};

class Solution {
  int n;
  const int di[4]{-1, 1, 0, 0};
  const int dj[4]{0, 0, -1, 1};
  int cell_num(const int i, const int j) const { return (i * n) + j; }
  generator<pair<int, int>> walk(const int i, const int j) {
    for (int d = 0; d < 4; d++) {
      const int i2 = i + di[d];
      const int j2 = j + dj[d];
      if (i2 < 0 || j2 < 0 || i2 >= n || j2 >= n) continue;
      co_yield {i2, j2};
    }
  }

 public:
  int largestIsland(vector<vector<int>>& grid) {
    n = grid.size();
    DisjointSets ds(n * n);

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (grid[i][j] == 0) continue;
        for (const auto& [x, y] : walk(i, j)) {
          if (grid[x][y] == 0) continue;
          ds.merge(cell_num(i, j), cell_num(x, y));
        }
      }
    }

    vector<vector<int>> sizes(n, vector<int>(n, 0));
    vector<pair<int, int>> dfs_cells;

    const function<int(int, int)> dfs = [&](const int i, const int j) {
      if (grid[i][j] != 1) return 0;
      grid[i][j] = -1;
      dfs_cells.emplace_back(i, j);
      int res = 1;
      for (const auto& [x, y] : walk(i, j)) res += dfs(x, y);
      return res;
    };

    int ans = 0;

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (grid[i][j] != 1) continue;

        const int count = dfs(i, j);
        for (const auto& [x, y] : dfs_cells) sizes[x][y] = count;
        dfs_cells.clear();
        ans = max(ans, count);
      }
    }

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (grid[i][j] != 0) continue;

        set<pair<int, int>> components;

        for (const auto& [x, y] : walk(i, j)) {
          const int cell = cell_num(x, y);
          components.emplace(ds.find(cell), sizes[x][y]);
        }

        int total = 1;
        for (const auto& [_, s] : components) total += s;

        ans = max(ans, total);
      }
    }

    return ans;
  }
};

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
  const int di[4]{-1, 1, 0, 0};
  const int dj[4]{0, 0, -1, 1};
  vector<vector<int>> grid;
  int stable_group;
  bool visited[201][201];
  int n, m;
  DisjointSets ds = DisjointSets(201 * 201 + 1);

  int cell_num(const int i, const int j) const { return (i * m) + j; }

  void for_neighbors(const int i, const int j, const function<void(int, int)> fn) const {
    for (int d = 0; d < 4; d++) {
      const int i2 = i + di[d];
      const int j2 = j + dj[d];
      if (i2 < 0 || j2 < 0 || i2 >= n || j2 >= m) continue;
      if (grid[i2][j2] == 0) continue;
      fn(i2, j2);
    }
  }

  int dfs(const int i, const int j) {
    if (i == 0) return 0;
    if (visited[i][j]) return 0;
    visited[i][j] = true;

    int res = 0;

    for_neighbors(i, j, [&](const int i2, const int j2) { res += dfs(i2, j2); });

    return 1 + res;
  }

  void init_union_find() {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (grid[i][j] == 0) continue;
        if (i == 0) {
          ds.merge(cell_num(0, j), stable_group);
        }

        for_neighbors(i, j, [&](const int i2, const int j2) {
          ds.merge(cell_num(i, j), cell_num(i2, j2));
        });
      }
    }
  }

 public:
  vector<int> hitBricks(const vector<vector<int>>& input, vector<vector<int>>& hits) {
    memset(visited, 0, sizeof visited);
    this->grid = input;
    n = grid.size();
    m = grid.front().size();

    const pair<int, int> dummy_cell{n - 1, m};
    stable_group = cell_num(dummy_cell.first, dummy_cell.second);

    map<pair<int, int>, int> query_result;

    set<pair<int, int>> original_has_brick;
    for (const vector<int>& hit : hits) {
      const int i = hit.front();
      const int j = hit.back();
      if (grid[i][j] == 1) original_has_brick.emplace(i, j);

      grid[i][j] = 0;
    }

    init_union_find();

    for (auto it = hits.rbegin(); it != hits.rend(); it++) {
      const int i = it->front();
      const int j = it->back();

      if (!original_has_brick.count({i, j})) {
        continue;
      }

      bool will_become_stable = false;

      if (i == 0) {
        ds.merge(cell_num(i, j), stable_group);
        will_become_stable = true;
      }

      for_neighbors(i, j, [&](const int i2, const int j2) {
        if (ds.find(cell_num(i2, j2)) == ds.find(stable_group)) {
          will_become_stable = true;
        }
      });

      for_neighbors(i, j, [&](const int i2, const int j2) {
        if (will_become_stable && ds.find(cell_num(i2, j2)) != ds.find(stable_group)) {
          query_result[{i, j}] += dfs(i2, j2);
        }

        ds.merge(cell_num(i2, j2), cell_num(i, j));
      });

      grid[i][j] = 1;
    }

    vector<int> ans;

    for (const auto& hit : hits) {
      const pair<int, int> q{hit.front(), hit.back()};
      ans.emplace_back(query_result[q]);
    }

    return ans;
  }
};

#include <bits/stdc++.h>
using namespace std;

const int di[]{-1, 1, 0, 0};
const int dj[]{0, 0, -1, 1};

class Solution {
  int R, C;
  vector<vector<int>> height_map;
  bool visited[201][201];

  int bury(const int i, const int j) {
    queue<pair<int, int>> q({{i, j}});

    const int height = height_map[i][j];
    height_map[i][j] = -1;
    int container_height = INT_MAX;

    vector<pair<int, int>> cells{{i, j}};

    while (!q.empty()) {
      const auto [i, j] = q.front();
      q.pop();

      for (int d = 0; d < 4; d++) {
        const int i2 = i + di[d];
        const int j2 = j + dj[d];
        if (i2 < 0 || j2 < 0 || i2 >= R || j2 >= C) {
          container_height = height;
          break;
        }

        const int h = height_map[i2][j2];

        if (h == -1) continue;
        if (h != height) {
          container_height = max(height, min(container_height, h));
          continue;
        }

        height_map[i2][j2] = -1;
        cells.emplace_back(i2, j2);
        q.emplace(i2, j2);
      }
    }

    for (const auto& [i, j] : cells) {
      visited[i][j] = true;
      height_map[i][j] = container_height;
    }

    return cells.size() * (container_height - height);
  }

 public:
  int trapRainWater(vector<vector<int>>& height_map) {
    memset(visited, 0, sizeof visited);
    this->height_map = height_map;
    R = height_map.size();
    C = height_map.front().size();

    vector<tuple<int, int, int>> cells;

    for (int i = 0; i < R; i++) {
      for (int j = 0; j < C; j++) {
        cells.emplace_back(height_map[i][j], i, j);
      }
    }

    sort(cells.begin(), cells.end());

    int total = 0;

    for (const auto& [_, i, j] : cells) {
      if (visited[i][j]) continue;

      total += bury(i, j);
    }

    return total;
  }
};

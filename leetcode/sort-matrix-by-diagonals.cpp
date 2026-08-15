#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<vector<int>> sortMatrix(vector<vector<int>>& grid) {
    const int n = grid.size();
    priority_queue<int> pq;

    for (int i = 0; i < n - 1; i++) {
      const int m = n - i;

      for (int j = 0; j < m; j++) {
        pq.emplace(grid[i + j][j]);
      }

      for (int j = 0; j < m; j++) {
        grid[i + j][j] = pq.top();
        pq.pop();
      }
    }

    for (int i = 1; i < n - 1; i++) {
      const int m = n - i;

      for (int j = 0; j < m; j++) {
        pq.emplace(-grid[j][i + j]);
      }

      for (int j = 0; j < m; j++) {
        grid[j][i + j] = -pq.top();
        pq.pop();
      }
    }

    return grid;
  }
};

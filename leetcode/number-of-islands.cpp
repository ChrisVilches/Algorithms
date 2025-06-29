#include <bits/stdc++.h>
using namespace std;

class Solution {
  vector<vector<char>> grid;
  int n, m;

  void dfs(const int i, const int j) {
    if (i < 0 || j < 0 || i >= n || j >= m) return;
    if (grid[i][j] == '0') return;
    grid[i][j] = '0';
    dfs(i + 1, j);
    dfs(i - 1, j);
    dfs(i, j + 1);
    dfs(i, j - 1);
  }

 public:
  int numIslands(const vector<vector<char>>& input) {
    n = input.size();
    m = input.front().size();
    grid = input;
    int ans = 0;

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (grid[i][j] == '0') continue;
        dfs(i, j);
        ans++;
      }
    }

    return ans;
  }
};

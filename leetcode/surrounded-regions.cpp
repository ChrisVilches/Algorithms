#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  void solve(vector<vector<char>>& board) {
    const int n = board.size();
    const int m = board.front().size();

    const function<void(int, int, char, char)> dfs = [&](const int i, const int j,
                                                         const char from, const char to) {
      if (i < 0 || j < 0 || i == n || j == m) return;
      if (board[i][j] != from) return;
      board[i][j] = to;
      dfs(i + 1, j, from, to);
      dfs(i - 1, j, from, to);
      dfs(i, j + 1, from, to);
      dfs(i, j - 1, from, to);
    };

    for (int i = 0; i < n; i++) {
      dfs(i, 0, 'O', '-');
      dfs(i, m - 1, 'O', '-');
    }

    for (int i = 0; i < m; i++) {
      dfs(0, i, 'O', '-');
      dfs(n - 1, i, 'O', '-');
    }

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) dfs(i, j, 'O', 'X');
    }

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) dfs(i, j, '-', 'O');
    }
  }
};

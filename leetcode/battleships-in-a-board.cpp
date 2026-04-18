#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int countBattleships(vector<vector<char>>& board) {
    const int n = board.size();
    const int m = board.front().size();
    int ans = 0;

    const function<void(int, int)> dfs = [&](const int i, const int j) {
      if (i == n || j == m) return;
      if (board[i][j] == '.') return;
      board[i][j] = '.';
      dfs(i + 1, j);
      dfs(i, j + 1);
    };

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (board[i][j] == 'X') {
          ans++;
          dfs(i, j);
        }
      }
    }

    return ans;
  }
};
